#
# Copyright (C) 2013-2015 NDM Systems, Inc. http://www.ndmsystems.com/
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package-defaults.mk

PKG_NAME:=dropbear
PKG_VERSION:=0.52
PKG_MD5SUM:=1c69ec674481d7745452f68f2ea5597e
PKG_LICENSE:=MIT

PKG_SOURCE_URL:=https://matt.ucc.asn.au/dropbear/releases/
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/dropbear
  NAME:=$(PKG_NAME)
  SECTION:=optware
  CATEGORY:=Optware
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

EXTRA_CFLAGS:=\
    -g3 -pipe -fPIC -std=c99 \
    -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 \
    -D_POSIX_C_SOURCE=199309L -D_XOPEN_SOURCE=600 -DDEBUG_TRACE\
    -ffunction-sections -fdata-sections \
    -Wall -Winit-self -Wswitch-enum -Wundef -Wunsafe-loop-optimizations \
    -Wmissing-field-initializers -Wnormalized=nfkc \
    -Wredundant-decls -Wstack-protector -ftabstop=4 -Wshadow \
    -Wpointer-arith

EXTRA_LDFLAGS:= -lpam

define Build/Configure
	$(call Build/Configure/Default)
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dropbear{,convert,key} $(1)/sbin/
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/dbclient $(1)/bin/
	$(INSTALL_DIR) $(1)/etc/default/
	$(INSTALL_BIN) ./files/dropbear $(1)/etc/default/dropbear
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_BIN) ./files/S51dropbear $(1)/etc/init.d/S51dropbear
endef

$(eval $(call BuildPackage,$(PKG_NAME)))
