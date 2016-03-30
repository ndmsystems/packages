#
# Makefile for the video capture/playback device drivers.
#
# EXTRA_CFLAGS += -DCONFIG_VIDEO_V4L1_COMPAT -DCONFIG_COMPAT -DCONFIG_VIDEO_V4L2_COMMON

videodev-objs	:=	v4l2-dev.o v4l2-ioctl.o v4l2-device.o v4l2-fh.o \
			v4l2-event.o v4l2-int-device.o v4l2-common.o v4l1-compat.o v4l2-compat-ioctl32.o
uvcvideo-objs  := uvc/uvc_driver.o uvc/uvc_queue.o uvc/uvc_v4l2.o uvc/uvc_video.o uvc/uvc_ctrl.o \
			uvc/uvc_status.o uvc/uvc_isight.o

# UVC/V4L2 core modules

obj-m += videodev.o uvcvideo.o
