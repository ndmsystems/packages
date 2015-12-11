#
# Copyright (C) 2007-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
PKG_NAME:=libubacktrace
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

LIBC_VERSION:=0.9.33-ndm-4

define Package/libubacktrace
  SECTION:=libs
  CATEGORY:=Base system
  VERSION:=$(LIBC_VERSION)-$(PKG_RELEASE)
  TITLE:=uClibc libubacktrace
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
	#nothing to do
endef

define Package/libubacktrace/install
	$(INSTALL_DIR) $(1)/lib
	find $(BUILD_DIR_TOOLCHAIN)/sysroot-* -name libubacktrace.so.0 -exec cp {} $(1)/lib/ \;
endef

$(eval $(call BuildPackage,libubacktrace))
