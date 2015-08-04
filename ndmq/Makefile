#
# Copyright (C) 2015 NDM Systems, Inc. http://www.ndmsystems.com/
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ndmq
PKG_VERSION:=1.0.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/ndmsystems/$(PKG_NAME)
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_PROTO:=git

include $(INCLUDE_DIR)/package.mk

define Package/ndmq
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=NDM Query utility
  URL:=
  DEPENDS:=+libndm
endef

EXTRA_CFLAGS :=\
	-std=c99 \
	-D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 \
	-D_POSIX_C_SOURCE=200112L -DNDEBUG \
	-ffunction-sections -fdata-sections \
	-Wall -Winit-self -Wswitch-enum -Wundef  \
	-Wmissing-field-initializers -Wnormalized=nfkc \
	-Wredundant-decls -Wstack-protector -ftabstop=4 -Wshadow \
	-Wpointer-arith

define Build/Compile
    $(MAKE) -C $(PKG_BUILD_DIR) \
        $(TARGET_CONFIGURE_OPTS) CC="$(TARGET_CC)" CFLAGS="$(TARGET_CFLAGS)" \
        LDLIBS="-lndm"
endef

define Package/${PKG_NAME}/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/${PKG_NAME} $(1)/bin/
endef

$(eval $(call BuildPackage,ndmq))

