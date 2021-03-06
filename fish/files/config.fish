#
# Init file for fish
#
# etc/config.fish, generated from etc/config.fish.in by the Makefile. DO NOT MANUALLY EDIT THIS FILE!

#
# Some things should only be done for login terminals
#

if status --is-login

	#
	# Set some value for LANG if nothing was set before, and this is a
	# login shell.
	#

	if not set -q LANG >/dev/null
		set -gx LANG en_US.UTF-8
	end

	# Check for i18n information in
	# /opt/etc/sysconfig/i18n

	if test -f /opt/etc/sysconfig/i18n
		eval (cat /opt/etc/sysconfig/i18n |sed -ne 's/^\([a-zA-Z]*\)=\(.*\)$/set -gx \1 \2;/p')
	end

	#
	# Put linux consoles in unicode mode.
	#

	if expr "$LANG" : ".*\.[Uu][Tt][Ff].*" >/dev/null
		if test "$TERM" = linux
			if which unicode_start >/dev/null
				unicode_start
			end
		end
	end
end

#
# There are variables that contain colons that are not arrays. This 
# reverts them back to regular strings.
#

for i in DISPLAY
	if set -q $i
		set -- $i (printf ":%s" $$i|cut -c 2-)
	end
end

#
# Load additional initialization files
#

if test -d include
	for i in include/*.fish
		. $i
	end
end

