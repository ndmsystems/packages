#
# Copyright (C) 2007-2012 OpenWrt.org
# Copyright (C) 2010 Vertical Communications
# Copyright (C) 2015 NDM Systems, McMCC
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=base-files
PKG_RELEASE:=123

include $(INCLUDE_DIR)/package.mk

define Package/base-files
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+libc
  TITLE:=Base filesystem for OpenWrt
  URL:=http://openwrt.org/
  VERSION:=$(PKG_RELEASE)-keenopt
  PKGARCH:=all
endef

define Package/base-files/description
 This package contains a base filesystem and system scripts for OpenWrt.
endef

define Build/Prepare
	[ -d $(PKG_BUILD_DIR) ] && rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile
	[ -d $(PKG_BUILD_DIR) ] && rm -rf $(PKG_BUILD_DIR)
	mkdir -p $(PKG_BUILD_DIR)
endef

define Package/base-files/install
	$(CP) ./files/* $(1)/
	if [ -d $(GENERIC_PLATFORM_DIR)/base-files/. ]; then \
		$(CP) $(GENERIC_PLATFORM_DIR)/base-files/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/base-files/. ]; then \
		$(CP) $(PLATFORM_DIR)/base-files/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/base-files_gpl/. ]; then \
		$(CP) $(PLATFORM_DIR)/base-files_gpl/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/base-files-$(PROFILE)/. ]; then \
		$(CP) $(PLATFORM_DIR)/base-files-$(PROFILE)/* $(1)/; \
	fi
	if [ -d $(PLATFORM_DIR)/$(PROFILE)/base-files/. ]; then \
		$(CP) $(PLATFORM_DIR)/$(PROFILE)/base-files/* $(1)/; \
	fi
	$(if $(filter-out $(PLATFORM_DIR),$(PLATFORM_SUBDIR)), \
		if [ -d $(PLATFORM_SUBDIR)/base-files/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/base-files/* $(1)/; \
		fi; \
		if [ -d $(PLATFORM_SUBDIR)/base-files_gpl/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/base-files_gpl/* $(1)/; \
		fi; \
		if [ -d $(PLATFORM_SUBDIR)/base-files-$(PROFILE)/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/base-files-$(PROFILE)/* $(1)/; \
		fi; \
		if [ -d $(PLATFORM_SUBDIR)/$(PROFILE)/base-files/. ]; then \
			$(CP) $(PLATFORM_SUBDIR)/$(PROFILE)/base-files/* $(1)/; \
		fi \
	)

	mkdir -p $(1)/dev
	$(if $(LIB_SUFFIX),-ln -s lib $(1)/lib$(LIB_SUFFIX))
	mkdir -p $(1)/proc
	mkdir -p $(1)/tmp
	mkdir -p $(1)/usr/lib
	$(if $(LIB_SUFFIX),-ln -s lib $(1)/usr/lib$(LIB_SUFFIX))
	mkdir -p $(1)/usr/bin
	mkdir -p $(1)/sys
	mkdir -p $(1)/root
	mkdir -p $(1)/var/cache
	mkdir -p $(1)/var/lock
	mkdir -p $(1)/var/run
	mkdir -p $(1)/var/lib
	mkdir -p $(1)/etc
	ln -sfn /tmp/hosts $(1)/etc/hosts
	ln -sfn /tmp/passwd $(1)/etc/passwd
	ln -sfn /tmp/group $(1)/etc/group
	ln -sfn /tmp/TZ $(1)/etc/TZ
	ln -sfn /tmp/resolv.conf $(1)/etc/resolv.conf
	ln -sfn /opt/lib/functions.sh $(1)/etc/functions.sh
	
	chmod 1777 $(1)/tmp
	$(INSTALL_DIR) $(1)/flash
	ln -sf $(CONFIG_TARGET_KERNEL_PATH) $(1)/flash/kernel-image
	ln -sf $(CONFIG_TARGET_ROOTFS_PATH) $(1)/flash/rootfs-image
	ln -sf $(CONFIG_TARGET_FLASH_PATH) $(1)/flash/startup-config
	$(call Package/base-files/install-target,$(1))
endef

define Package/base-files/conffiles
/etc/profile
/etc/shells
/etc/sysctl.conf
/usr/share/udhcpc/default.script
endef

$(eval $(call BuildPackage,base-files))
