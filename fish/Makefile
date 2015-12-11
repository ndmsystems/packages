#
# Copyright (C) 2015 NDM Systems, McMCC
#

include $(TOPDIR)/rules.mk

PKG_NAME:=fish
PKG_VERSION:=1.23.1
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_MD5SUM:=ead6b7c6cdb21f35a3d4aa1d5fa596f1
PKG_SOURCE_URL:=http://pkgs.fedoraproject.org/repo/pkgs/fish/$(PKG_SOURCE)/$(PKG_MD5SUM)/
PKG_LICENSE:=GPL-2.0
PKG_LICENSE_FILES:=COPYING
PKG_MAINTAINER:=Axel Liljencrantz <axel@liljencrantz.se>

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

define Package/fish
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Fish shell
  DEPENDS:=+libubacktrace +libncurses
  URL:=http://fishshell.com/
endef

define Package/fish/description
	Fish is a smart and user-friendly command line
	shell for OS X, Linux, and the rest of the family.
endef

TARGET_CFLAGS += -std=gnu99
CONFIGURE_ARGS += \
	--prefix=/opt \
	--sysconfdir=/opt/etc \
	--datadir=/opt/usr/share \
	--bindir=/opt/bin \
	--localedir=/opt/usr/share/locale

define Package/fish/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fish $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fishd $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fish_pager $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/fish_indent $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mimedb $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/set_color $(1)/bin
	$(INSTALL_CONF) ./files/config.fish $(1)/etc
endef

define Package/fish/postinst
#!/opt/bin/ash
if [ -f /opt/etc/shells ]; then
	grep "/opt/bin/fish" /opt/etc/shells || echo "/opt/bin/fish" >> /opt/etc/shells
fi
endef

define Package/fish/conffiles
/opt/etc/config.fish
endef

$(eval $(call BuildPackage,fish))
