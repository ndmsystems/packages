#!/bin/sh

[ -r /etc/passwd ] || exit 0
[ -r /etc/group ] || exit 0

if ! grep -q '^tmp:' /etc/group; then
( echo -n 'tmp:*:65533:'
  grep '^[^#: ]*:' /etc/passwd | \
    grep ':\/opt\/home' | \
    sed 's/:.*//' | \
    tr '\n' ',' | \
    sed 's/,$//'
  echo ) >> /etc/group
fi

if ! grep -q '^audio:' /etc/group; then
( echo -n 'audio:*:65532:'
  grep '^[^#: ]*:' /etc/passwd | \
    grep ':\/opt\/home' | \
    sed 's/:.*//' | \
    tr '\n' ',' | \
    sed 's/,$//'
  echo ) >> /etc/group
fi

if ! grep -q '^video:' /etc/group; then
( echo -n 'video:*:65531:'
  grep '^[^#: ]*:' /etc/passwd | \
    grep ':\/opt\/home' | \
    sed 's/:.*//' | \
    tr '\n' ',' | \
    sed 's/,$//'
  echo ) >> /etc/group
fi

chgrp tmp /opt/tmp
