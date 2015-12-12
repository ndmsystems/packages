#
# Copyright (C) 2006-2014 OpenWrt.org
# Copyright (C) 2015 NDM Systems, McMCC
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mpc
PKG_VERSION:=0.27
PKG_RELEASE:=2

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=http://www.musicpd.org/download/mpc/0
PKG_MD5SUM:=d9430db9b9d7fb1eadbe4d13e8d97c66
PKG_LICENSE:=GPL-2.0+
PKG_LICENSE_FILES:=COPYING
PKG_MAINTAINER:=Ted Hess <thess@kitschensync.net>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/mpc
  SECTION:=sound
  CATEGORY:=Sound
  DEPENDS:=+libmpdclient $(ICONV_DEPENDS)
  TITLE:=Music Player Daemon Console Client
  URL:=http://www.musicpd.org/
endef

define Package/mpc/description
	MPD is a music player supporting flac, mp3 and ogg files.
	It is typically controlled over a network using one of it's many
	clients including mpc(console), gmpc(gnome), phpmp(php) etc.
	this is MPC
endef

CONFIGURE_VARS += \
	ac_cv_lib_intl_iconv=yes \
	ac_cv_func_iconv=yes

define Build/Compile
$(call Build/Compile/Default,\
		ICONV_LIBS="$(ICONV_PREFIX)/lib/libiconv.a" \
		CFLAGS="$(TARGET_CFLAGS) -DHAVE_ICONV -std=gnu99" \
		prefix="/opt/usr" \
		all \
)
endef

define Package/mpc/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/default/usb_services/sound
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/mpc $(1)/usr/bin/
	$(INSTALL_BIN) ./files/mpc.init $(1)/etc/init.d/S05mpc
	$(INSTALL_CONF) ./files/mpcconf.example $(1)/etc/default/mpc
	ln -sfn ../../../init.d/S05mpc $(1)/etc/default/usb_services/sound/S05mpc
endef

define Package/mpc/conffiles
/etc/default/mpc
endef

$(eval $(call BuildPackage,mpc))
