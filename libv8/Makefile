##############################################
# OpenWrt Makefile for Z-Way
##############################################
#
# Copyright (C) 2015 Z-Wave.Me
#

include $(TOPDIR)/rules.mk

# Name and release number of this package
PKG_NAME:=libv8
PKG_VERSION:=38d2d515ddeace8ea4719938f86edf316d29b576
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.gz
PKG_SOURCE_URL:=https://github.com/v8/v8
PKG_SOURCE_SUBDIR:=$(PKG_NAME)-$(PKG_VERSION)
PKG_SOURCE_VERSION:=$(PKG_VERSION)
PKG_SOURCE_PROTO:=git

PKG_BUILD_PARALLEL:=1

include $(INCLUDE_DIR)/package.mk

export GYP_DEFINES=linux_use_bundled_binutils=0 linux_use_debug_fission=0 clang=0 werror= component=shared_library
export GYPFLAGS=-Dv8_use_mips_abi_hardfloat=false -Dv8_can_use_fpu_instructions=false -Dtarget_cxx_is_biarch=0 -Dhost_cxx_is_biarch=0
export V8_ARGS=library=shared i18nsupport=off $(ARCH).release
export CFLAGS=-ffat-lto-objects
export V8_TARGET_ARCH=$(ARCH)

# send all variable to submake

# Specify package information for this program.
# The variables defined here should be self explanatory.
define Package/libv8
	SECTION:=libs
	CATEGORY:=Libraries
	TITLE:=Google v8 JavaScript engine
	URL:=http://code.google.com/p/v8/
	MAINTAINER:=Google
	DEPENDS+= +libpthread +librt
endef

define Package/libv8/description
	Google v8 JavaScript engine allows to run ECMA-5 JavaScript code.
endef

define Build/Prepare
	$(call Build/Prepare/Default)
	$(MAKE) -C $(PKG_BUILD_DIR) dependencies
endef

define Build/Compile
	CXX=$(TARGET_CXX) LD=$(TARGET_CXX) LINK=$(TARGET_CXX) \
	$(MAKE) -C $(PKG_BUILD_DIR) $(V8_ARGS)
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_BUILD_DIR)/out/$(ARCH).release/lib.target/* $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/include/* $(1)/usr/include/
endef

# The $(1) variable represents the root directory on the router running
# OpenWrt. The $(INSTALL_DIR) variable contains a command to prepare the install
# directory if it does not already exist.  Likewise $(INSTALL_BIN) contains the
# command to copy the binary file from its current location (in our case the build
# directory) to the install directory.
define Package/libv8/install
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_BUILD_DIR)/out/$(ARCH).release/lib.target/* $(1)/usr/lib/
endef

# This line executes the necessary commands to compile our program.
# The above define directives specify all the information needed, but this
# line calls BuildPackage which in turn actually uses this information to
# build a package.
$(eval $(call BuildPackage,libv8))

