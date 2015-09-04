# 
# Copyright (C) 2015 NDM Systems, Inc.
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=ttywatch
PKG_VERSION:=0.14
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=http://www.danlj.org/mkj/ttywatch/

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

define Package/ttywatch
  SECTION:=utils
  CATEGORY:=Utilities
  DEPENDS:=+glib2 +libpopt
  TITLE:=ttywatch - port monitoring software
  URL:=http://www.danlj.org/mkj/ttywatch/
  MENU:=1
endef

define Package/ttywatch/description
 ttywatch was originally designed to log serial console output from 
 lots of Linux machines on a single monitor machine. It:
 - Handles log rotation correctly.
 - Can be configured in both a configuration file and 
   on the command line (mix-and-match command-line and config file). 
   The config file language is the same as the command-line language.
 - Supports arbitrary data logging methods via dynamically loaded modules.
 - Can optionally connect any monitored port to a network socket, and 
   it can support arbitrarily many telnet connections to each port. 
   The connections work together in "whiteboard" fashion; all output is 
   shown to every connection and input is accepted from all connections.
 - Can connect to network ports speaking the telnet protocol as well as 
   to serial ports; this allows ttywatch instances to be cascaded. 
endef

define Package/ttywatch/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ttywatch $(1)/usr/bin
endef

$(eval $(call BuildPackage,ttywatch))
