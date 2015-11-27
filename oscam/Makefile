#
# Copyright (C) 2015 NDM Systems, McMCC
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk

PKG_NAME:=oscam
PKG_RELEASE:=2

PKG_SOURCE_URL:=http://www.streamboard.tv/svn/oscam/trunk
PKG_REV:=$(shell svn info ${PKG_SOURCE_URL} | sed -ne's/^Last Changed Rev: //p')
PKG_VER:=$(shell svn info ${PKG_SOURCE_URL} | grep -oE [0-9]{4}-[0-9]{2}-[0-9]{2})
PKG_VERSION:=$(PKG_VER)-$(PKG_REV)

PKG_SOURCE_PROTO:=svn
PKG_SOURCE_VERSION:=$(PKG_REV)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE:=$(PKG_SOURCE_SUBDIR).tar.bz2
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)-$(PKG_VERSION)

include $(INCLUDE_DIR)/package.mk

define Package/oscam
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Open Source Conditional Access Module
  URL:=http://www.streamboard.tv/oscam/wiki/BuildingOscam
  DEPENDS:=+libopenssl +libpcsclite +libusb-1.0 +ccid +pcscd
endef

define Package/list-smargo
  $(call Package/oscam)
  TITLE:=Smargo reader support
  DEPENDS:=oscam
endef


MAKE_FLAGS += USE_LIBUSB=1 USE_PCSC=1 USE_LIBCRYPTO=1 USE_SSL=1

ifneq ($(CONFIG_PACKAGE_list-smargo),)
	MAKE_FLAGS += LIST_SMARGO_BIN=Distribution/list-smargo
endif

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) $(TARGET_CONFIGURE_OPTS) CC="$(TARGET_CC)" \
		LDFLAGS="$(TARGET_CFLAGS) -L $(STAGING_DIR)/lib/ -L $(STAGING_DIR)/usr/lib/" \
		CFLAGS="$(TARGET_CFLAGS) -I $(STAGING_DIR)/usr/include/ -I $(STAGING_DIR)/include/" \
		OSCAM_BIN="Distribution/oscam" $(MAKE_FLAGS) SVN_REV=$(PKG_REV)
endef

define Package/oscam/conffiles
	/opt/etc/oscam/oscam.conf
	/opt/etc/oscam/oscam.server
	/opt/etc/oscam/oscam.user
endef

define Package/oscam/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/Distribution/oscam $(1)/usr/bin/oscam
	$(INSTALL_DIR) $(1)/etc/oscam
	$(INSTALL_CONF) ./files/oscam.conf $(1)/etc/oscam/
	$(INSTALL_CONF) ./files/oscam.server $(1)/etc/oscam/
	$(INSTALL_CONF) ./files/oscam.user $(1)/etc/oscam/
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/oscam.init $(1)/etc/init.d/S11oscam
endef

define Package/list-smargo/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/Distribution/list-smargo $(1)/usr/bin/list-smargo
endef

$(eval $(call BuildPackage,oscam))
$(eval $(call BuildPackage,list-smargo))
