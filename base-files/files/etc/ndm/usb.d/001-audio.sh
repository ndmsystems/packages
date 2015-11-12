#!/opt/bin/sh
# Copyright (C) 2015 NDM Systems, McMCC

export TZ=`cat /etc/TZ | tail -n 1`

SERV_DIR=/opt/etc/default/usb_services/$usb_subsystem

start() {
	if [ -d $SERV_DIR ]; then
		for service in `ls $SERV_DIR`; do
			/opt/etc/init.d/$service stop
			sleep 1
			/opt/etc/init.d/$service start
		done
	fi
}

stop() {
	if [ -d $SERV_DIR ]; then
		for service in `ls $SERV_DIR`; do
			/opt/etc/init.d/$service stop
		done
	fi
}

services() {
	if [ "$1" = "$usb_devname" ]; then
		sleep 1
		if [ -d /sys/$usb_devpath ]; then
			start
		else
			stop
		fi
	fi
}

case "$usb_subsystem" in
	sound)
		services audio
		;;
esac

exit 0
