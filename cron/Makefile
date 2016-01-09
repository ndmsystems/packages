#
# Copyright (C) 2015 NDM Systems, McMCC
#

include $(TOPDIR)/rules.mk

PKG_NAME:=cron
PKG_RELEASE:=2

include $(INCLUDE_DIR)/package.mk

define Package/cron
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Cron utils for use crond from busybox
  DEPENDS:=+busybox
  URL:=http://www.busybox.net
  VERSION:=$(PKG_RELEASE)-keenopt
  PKGARCH:=all
endef

define Package/cron/description
	Cron utils for use crond from busybox.
endef

define Build/Prepare
endef

define Build/Compile
endef

define Package/cron/install
	$(INSTALL_DIR) $(1)/var/run
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/etc/ndm/time.d
	$(INSTALL_DIR) $(1)/etc/crontabs
	$(INSTALL_DIR) $(1)/etc/cron.minutely
	$(INSTALL_DIR) $(1)/etc/cron.hourly
	$(INSTALL_DIR) $(1)/etc/cron.daily
	$(INSTALL_DIR) $(1)/etc/cron.weekly
	$(INSTALL_DIR) $(1)/etc/cron.monthly
	$(INSTALL_CONF) ./files/root $(1)/etc/crontabs/
	$(INSTALL_BIN) ./files/crond.init $(1)/etc/init.d/S02crond
	ln -sfn ../../init.d/S02crond $(1)/etc/ndm/time.d/S02crond
endef

define Package/cron/conffiles
/etc/crontabs/root
endef

$(eval $(call BuildPackage,cron))
