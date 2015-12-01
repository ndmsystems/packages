#
# Copyright (C) 2007-2012 OpenWrt.org
# Copyright (C) 2010 Vertical Communications
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk
include $(INCLUDE_DIR)/version.mk

PKG_NAME:=base-files
PKG_RELEASE:=120

PKG_FILE_DEPENDS:=$(PLATFORM_DIR)/ $(GENERIC_PLATFORM_DIR)/base-files/
PKG_BUILD_DEPENDS:=opkg/host

include $(INCLUDE_DIR)/package.mk

ifneq ($(DUMP),1)
  TARGET:=-$(BOARD)
  ifneq ($(wildcard $(PLATFORM_DIR)/base-files-$(PROFILE) $(PLATFORM_SUBDIR)/base-files-$(PROFILE)),)
    TARGET:=$(TARGET)-$(PROFILE)
  endif
endif

define Package/base-files
  SECTION:=base
  CATEGORY:=Base system
  DEPENDS:=+libc
  TITLE:=Base filesystem for OpenWrt
  URL:=http://openwrt.org/
  VERSION:=$(PKG_RELEASE)-$(REVISION)
  PKGARCH:=all
endef

# define Package/base-files/conffiles
# /etc/inittab
# /etc/group
# /etc/passwd
# /etc/profile
# /etc/shells
# /etc/sysctl.conf
# $(call $(TARGET)/conffiles)
# endef

define Package/base-files/description
 This package contains a base filesystem and system scripts for OpenWrt.
endef

define Build/Prepare
	if [ -d $(PKG_BUILD_DIR) ]; then \
		rm -rf $(PKG_BUILD_DIR); \
	fi
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default

endef
Build/Compile = $(Build/Compile/Default)

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
	mkdir -p $(1)/var
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

ifneq ($(DUMP),1)
  -include $(PLATFORM_DIR)/base-files.mk
endif

$(eval $(call BuildPackage,base-files))
