
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=uvcvideo
PKG_RELEASE:=1
PKG_LICENSE:=GPL

include $(INCLUDE_DIR)/package.mk

define KernelPackage/video-core-kold
  SUBMENU:=Video Support old kernel
  DEPENDS:=@LINUX_2_6_22||USB_SUPPORT
  TITLE:=Video drivers V4L for old kernel
  FILES:=$(PKG_BUILD_DIR)/src/videodev.$(LINUX_KMOD_SUFFIX)
endef

define KernelPackage/video/Depends
  SUBMENU:=Video Support old kernel
  DEPENDS+=kmod-video-core $(1)
endef

define KernelPackage/video-uvc-kold
$(call KernelPackage/video/Depends,@USB_SUPPORT +kmod-usb-core)
  SUBMENU:=Video Support old kernel
  DEPENDS:=+kmod-video-core-kold
  TITLE:=Video drivers for UVC USB web-cameras old kernel
  FILES:=$(PKG_BUILD_DIR)/src/uvcvideo.$(LINUX_KMOD_SUFFIX)
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
