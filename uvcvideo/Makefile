
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=uvcvideo
PKG_RELEASE:=1
PKG_LICENSE:=GPL
VIDEO_MENU:=Video Support

include $(INCLUDE_DIR)/package.mk

define KernelPackage/video-core-kold
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS:=@LINUX_2_6_22 @USB_SUPPORT
  TITLE:=Video drivers V4L
  PROVIDES:=kmod-video-core
  KCONFIG:= \
	CONFIG_MEDIA_SUPPORT=m \
	CONFIG_VIDEO_DEV \
	CONFIG_VIDEO_V4L1=y \
	CONFIG_VIDEO_ALLOW_V4L1=y \
	CONFIG_VIDEO_CAPTURE_DRIVERS=n \
	CONFIG_V4L_USB_DRIVERS=y
  FILES:=$(PKG_BUILD_DIR)/src/videodev.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoLoad,60,videodev)
endef

define KernelPackage/video/Depends
  SUBMENU:=$(VIDEO_MENU)
  DEPENDS+=kmod-video-core-kold $(1)
endef

define KernelPackage/video-uvc-kold
$(call KernelPackage/video/Depends,@LINUX_2_6_22 @USB_SUPPORT +kmod-usb-core)
  SUBMENU:=$(VIDEO_MENU)
  TITLE:=Video drivers for UVC USB web-cameras
  PROVIDES:=kmod-video-uvc
  FILES:=$(PKG_BUILD_DIR)/src/uvcvideo.$(LINUX_KMOD_SUFFIX)
  AUTOLOAD:=$(call AutoLoad,90,uvcvideo)
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)/src
	$(CP) ./src/* $(PKG_BUILD_DIR)/src
endef

define Build/Compile
	$(MAKE) $(JOBS) -C "$(LINUX_DIR)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)/src" \
		EXTRA_CFLAGS="$(BOARD_CONFIGURE_OPTS) -DCONFIG_COMPAT -DCONFIG_VIDEO_V4L1_COMPAT -DCONFIG_VIDEO_V4L2_COMMON $(BUILDFLAGS)" \
		modules
endef

$(eval $(call KernelPackage,video-core-kold))
$(eval $(call KernelPackage,video-uvc-kold))
