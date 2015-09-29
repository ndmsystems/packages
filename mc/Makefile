#
# Copyright (C) 2006-2015 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mc
PKG_VERSION:=4.8.14
PKG_RELEASE:=2
PKG_MAINTAINER:=Dirk Brenken <dibdot@gmail.com>
PKG_LICENSE:=GPL-3.0+

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.xz
PKG_SOURCE_URL:=http://ftp.midnight-commander.org/
PKG_MD5SUM:=fbdaddb9edcf8925dcf3231331a8720b

PKG_BUILD_PARALLEL:=1
PKG_FIXUP:=autoreconf

PKG_CONFIG_DEPENDS := \
	CONFIG_PACKAGE_MC \
	CONFIG_MC_DIFFVIEWER \
	CONFIG_MC_EDITOR \
	CONFIG_MC_SUBSHELL \
	CONFIG_MC_LARGEFILE \
	CONFIG_MC_BACKGROUND \
	CONFIG_MC_CHARSET \
	CONFIG_MC_VFS

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/nls.mk

export MC_TMPDIR=/opt/tmp

define Package/mc
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+glib2 +libncurses +libmount +MC_VFS:libssh2 $(LIBRPC_DEPENDS) $(ICONV_DEPENDS)
  TITLE:=Midnight Commander - a powerful visual file manager
  URL:=http://www.midnight-commander.org/
  MENU:=1
endef

define Package/mc/config
	source "$(SOURCE)/Config.in"
endef

define Package/mc/description
 GNU Midnight Commander is a visual file manager,
 licensed under GNU General Public License and therefore qualifies as Free Software.
 It's a feature rich full-screen text mode application that allows you to copy,
 move and delete files and whole directory trees, search for files
 and run commands in the subshell. Internal viewer and editor are included.
endef

CONFIGURE_ARGS += \
	--disable-doxygen-doc \
	--with-screen=ncurses \
	--without-gpm-mouse \
	--without-x \
	--prefix=/opt/usr \
	--exec-prefix=/opt/usr \
	--sysconfdir=/opt/etc \
	--libdir=/opt/usr/lib \
	--bindir=/opt/usr/bin \
	--sbindir=/opt/usr/sbin \
	--libexecdir=/opt/usr/lib \
	--datadir=/opt/usr/share \
	--localstatedir=/opt/var \

CONFIGURE_VARS += \
	ac_cv_search_addwstr=no \

ifeq ($(CONFIG_MC_DIFFVIEWER),)
CONFIGURE_ARGS += \
	--without-diff-viewer
endif

ifeq ($(CONFIG_MC_EDITOR),)
CONFIGURE_ARGS += \
	--without-internal-edit
endif

ifeq ($(CONFIG_MC_SUBSHELL),)
CONFIGURE_ARGS += \
	--without-subshell
endif

ifeq ($(CONFIG_MC_LARGEFILE),)
CONFIGURE_ARGS += \
	--disable-largefile
endif

ifeq ($(CONFIG_MC_BACKGROUND),)
CONFIGURE_ARGS += \
	--disable-background
endif

ifeq ($(CONFIG_MC_CHARSET),)
CONFIGURE_ARGS += \
	--disable-charset
endif

ifeq ($(CONFIG_MC_VFS),)
CONFIGURE_ARGS += \
	--disable-vfs
endif

define Package/mc/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/mc
	$(INSTALL_DIR) $(1)/usr/lib/mc
	$(INSTALL_DIR) $(1)/usr/share/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/consaver/cons.saver $(1)/usr/lib/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/mc $(1)/usr/bin
ifeq ($(CONFIG_MC_DIFFVIEWER),y)
	ln -sf mc $(1)/usr/bin/mcdiff
endif
ifeq ($(CONFIG_MC_EDITOR),y)
	ln -sf mc $(1)/usr/bin/mcedit
endif
	$(INSTALL_DIR) $(1)/usr/lib/mc/ext.d
	$(INSTALL_DIR) $(1)/usr/lib/mc/extfs.d
	$(INSTALL_DIR) $(1)/usr/lib/mc/fish
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/misc/ext.d/*.sh $(1)/usr/lib/mc/ext.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/vfs/extfs/helpers/* $(1)/usr/lib/mc/extfs.d
	rm -f $(1)/usr/lib/mc/extfs.d/M* $(1)/usr/lib/mc/extfs.d/*.in
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/src/vfs/fish/helpers/* $(1)/usr/lib/mc/fish
	rm -f $(1)/usr/lib/mc/fish/M*
	$(INSTALL_DIR) $(1)/usr/share/mc/bin
	$(INSTALL_DIR) $(1)/usr/share/mc/skins
	$(INSTALL_DIR) $(1)/usr/share/mc/syntax
	$(INSTALL_DIR) $(1)/usr/share/mc/help
	$(INSTALL_DIR) $(1)/usr/share/mc/hints
	$(INSTALL_DIR) $(1)/usr/share/mc/examples/macros.d
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/skins/*.ini $(1)/usr/share/mc/skins
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/syntax/*yntax $(1)/usr/share/mc/syntax
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/hlp/mc.hlp $(1)/usr/share/mc/help
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/doc/hints/mc.hint $(1)/usr/share/mc/hints
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mc.charsets $(1)/usr/share/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mc.lib $(1)/usr/share/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/misc/macros.d/*.sh $(1)/usr/share/mc/examples/macros.d
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/contrib/mc.sh $(1)/usr/lib/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/contrib/mc.csh $(1)/usr/lib/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/contrib/mc-wrapper.sh $(1)/usr/lib/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/contrib/mc-wrapper.csh $(1)/usr/lib/mc
	ln -sf ../../../lib/mc/mc.csh $(1)/usr/share/mc/bin/mc.csh
	ln -sf ../../../lib/mc/mc.sh $(1)/usr/share/mc/bin/mc.sh
	ln -sf ../../../lib/mc/mc-wrapper.csh $(1)/usr/share/mc/bin/mc-wrapper.csh
	ln -sf ../../../lib/mc/mc-wrapper.sh $(1)/usr/share/mc/bin/mc-wrapper.sh
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mc.menu $(1)/etc/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mc.menu.sr $(1)/etc/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mc.ext $(1)/etc/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/mcedit.menu $(1)/etc/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/*.keymap $(1)/etc/mc
	$(INSTALL_DATA) $(PKG_BUILD_DIR)/misc/filehighlight.ini $(1)/etc/mc
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/misc/edit.indent.rc $(1)/etc/mc
	$(INSTALL_BIN) ./files/edit.spell.rc $(1)/etc/mc
	$(INSTALL_DATA) ./files/*.ini $(1)/etc/mc
	$(INSTALL_DATA) ./files/mc.keymap.default $(1)/etc/mc
	$(INSTALL_DATA) ./files/mc.keymap.emacs $(1)/etc/mc
endef

$(eval $(call BuildPackage,mc))
