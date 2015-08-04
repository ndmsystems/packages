#
# Copyright (C) 2013-2015 NDM Systems, Inc. http://www.ndmsystems.com/
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package-defaults.mk

PKG_NAME:=pam_ndm
PKG_VERSION:=1.0.2
PKG_MD5SUM:=5e75940b1fea433b51a93ddac1bf69ce
PKG_LICENSE:=NDM

PKG_SOURCE_PROTO:=git
PKG_SOURCE_URL:=https://github.com/ndmsystems/$(PKG_NAME)
PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/ndm-build.mk

define Package/pam_ndm
  NAME:=$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=PAM authentication module for libndm
  DEPENDS:=+libndm +libpam
endef

EXTRA_CFLAGS:=\
    -g3 -pipe -fPIC -std=c99 \
    -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 \
    -D_POSIX_C_SOURCE=199309L -D_XOPEN_SOURCE=600 \
	-D__TARGET_REALM__= $(call StringMacro,CONFIG_TARGET_REALM) \
    -ffunction-sections -fdata-sections \
    -Wall -Winit-self -Wswitch-enum -Wundef -Wunsafe-loop-optimizations \
    -Wmissing-field-initializers -Wnormalized=nfkc \
    -Wredundant-decls -Wstack-protector -ftabstop=4 -Wshadow \
    -Wpointer-arith 

EXTRA_LDFLAGS:=-shared -lndm -lpam

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/lib/security
	$(CP) $(PKG_BUILD_DIR)/pam_ndm.so $(1)/lib/security/pam_ndm.so
	$(INSTALL_DIR) $(1)/etc/pam.d
	rm -rf $(1)/etc/pam.d/*
	$(INSTALL_DATA) ./files/* $(1)/etc/pam.d/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))

