#
# Copyright (C) 2013-2015 NDM Systems, Inc. http://www.ndmsystems.com/
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package-defaults.mk

PKG_NAME:=dropbear
PKG_VERSION:=2015.68
PKG_MD5SUM:=7664ac10f7cc2301c530eb80c756fc5d
PKG_RELEASE:=1
PKG_LICENSE:=MIT

PKG_SOURCE_URL:=https://dropbear.nl/mirror/releases
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dropbear
  NAME:=$(PKG_NAME)
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Lightweight SSH sever and client
  DEPENDS:=+libpam +pam_ndm
endef

CONFIGURE_ARGS += \
    --enable-pam \
    --disable-lastlog \
    --disable-utmp \
    --disable-utmpx \
    --disable-wtmp \
    --disable-wtmpx \
    --disable-loginfunc \
    --disable-pututline \
    --disable-pututxline \
    --disable-zlib

EXTRA_LDFLAGS:= -lpam

define Build/Configure
	$(call Build/Configure/Default)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbear{,convert,key} $(1)/sbin/
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dbclient $(1)/bin/
	ln -sf dbclient $(1)/bin/ssh
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/scp $(1)/bin/
	$(INSTALL_DIR) $(1)/etc/default/
	$(INSTALL_BIN) ./files/dropbear $(1)/etc/default/dropbear
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/S51dropbear $(1)/etc/init.d/S01dropbear
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
