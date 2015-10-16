#!/bin/sh

home=/opt/home

[ -z "$user" ] && exit 0       # $user is undefined

if mkdir -p $home/$user; then
    chmod 0755 $home
    chmod 0700 $home/$user
    chown -R $user.$user $home/$user
fi
