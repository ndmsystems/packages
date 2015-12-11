#
# Copyright (C) 2015 NDM Systems, McMCC
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ympd
PKG_VERSION:=1.2.3
PKG_RELEASE:=1

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/notandy/ympd.git
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=4295d1587446872688fe7fa307e33fbc586bc9bc
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION)-$(PKG_SOURCE_VERSION).tar.gz

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/ympd
  SECTION:=sound
  CATEGORY:=Sound
  TITLE:=MPD web client
  URL:=http://www.ympd.org
  DEPENDS:= +libmpdclient
endef

define Package/ympd/description
  YMPD is a lightweight MPD (Music Player Daemon) web client that runs without a dedicated
  webserver or interpreters like PHP, NodeJS or Ruby. It's tuned for minimal resource usage
  and requires only very litte dependencies.
endef

CMAKE_OPTIONS += -DCMAKE_INSTALL_PREFIX:PATH=/opt/usr

define Package/ympd/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/default
	$(INSTALL_DIR) $(1)/etc/default/usb_services/sound

	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ympd $(1)/usr/sbin
	$(INSTALL_BIN) ./files/ympd.init $(1)/etc/init.d/S04ympd
	$(INSTALL_CONF) ./files/ympd.conf $(1)/etc/default/ympd
	ln -sfn ../../../init.d/S04ympd $(1)/etc/default/usb_services/sound/S04ympd
endef

define Package/ympd/conffiles
/opt/etc/default/ympd
endef

$(eval $(call BuildPackage,ympd))
