#
# Copyright (C) 2009-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ccid
PKG_VERSION:=1.4.21
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=https://alioth.debian.org/frs/download.php/file/4148
PKG_MD5SUM:=d1c3d5b447510cd507d1ecc09ac41b04
PKG_MAINTAINER:=Daniel Golle <daniel@makrotopia.org>
PKG_LICENSE:=LGPL-2.1+
PKG_LICENSE_FILES:=COPYING

PKG_FIXUP:=libtool
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk

define Package/ccid
  SECTION:=libs
  CATEGORY:=Libraries
  DEPENDS:=+libusb-1.0 +libpcsclite
  TITLE:=Generic USB CCID smart card reader driver
  URL:=http://pcsclite.alioth.debian.org/ccid.html
endef

define Package/ccid/description
  Generic USB CCID (Chip/Smart Card Interface Devices) driver and ICCD
  (Integrated Circuit(s) Card Devices).
endef

TARGET_CFLAGS += $(FPIC)

TARGET_LDFLAGS += "-lpthread"

CONFIGURE_ARGS += \
	--enable-embedded \
	--enable-twinserial \
	--enable-usbdropdir=/opt/usr/lib/pcsc/drivers \
	--enable-ccidtwindir=/opt/usr/lib/pcsc/drivers/serial \
	--enable-serialconfdir=/opt/etc/reader.conf.d

define Package/ccid/install
	$(INSTALL_DIR) $(1)/usr/lib/pcsc
	$(INSTALL_DIR) $(1)/etc/reader.conf.d
	$(CP) $(PKG_INSTALL_DIR)/opt/usr/lib/pcsc/drivers $(1)/usr/lib/pcsc/
	$(CP) $(PKG_INSTALL_DIR)/opt/etc/reader.conf.d/* $(1)/etc/reader.conf.d/
endef

$(eval $(call BuildPackage,ccid))
