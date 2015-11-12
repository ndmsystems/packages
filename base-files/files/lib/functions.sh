#!/opt/bin/sh
# Copyright (C) 2015 NDM Systems, McMCC

INITD="/opt/etc/init.d"

export LANG=C

load_modules() {
	[ -d /opt/etc/modules.d ] && {
		cd /opt/etc/modules.d
		for a in `cat $1`; do
			insmod /opt/lib/modules/2.6.36/$a.ko 2> /dev/null
		done
	}
}

unload_modules() {
	[ -d /opt/etc/modules.d ] && {
		cd /opt/etc/modules.d
			for a in `cat $1 | sed '1!G;h;$!d'`; do
			rmmod $a 2> /dev/null
		done
	}
}

load_opt_modules() {
	[ -d /opt/etc/modules.d ] && {
		for a in `ls /opt/etc/modules.d`; do
			echo "Load modules: $a"
			load_modules $a
		done
	}
}

unload_opt_modules() {
	[ -d /opt/etc/modules.d ] && {
		for a in `ls /opt/etc/modules.d | sed '1!G;h;$!d'`; do
			echo "Unload modules: $a"
			unload_modules $a
		done
	}
}


apps_start() {
	for prog in `ls $INITD`; do
		$INITD/$prog start
	done
}

apps_stop() {
	for prog in `ls $INITD`; do
		$INITD/$prog stop
	done
}
