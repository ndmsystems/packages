# 
# Copyright (C) 2016 Keenopt.ru
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
# $Id$

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=alsa-driver
PKG_VERSION:=1.0.25
PKG_RELEASE:=1

PKG_SOURCE:=$(PKG_NAME)-$(PKG_VERSION).tar.bz2
PKG_SOURCE_URL:=ftp://ftp.alsa-project.org/pub/driver/
PKG_MD5SUM:=ac56465c262ced60b5eb2d6492d7a923
AUDIO_MENU:=Sound Support

include $(INCLUDE_DIR)/package.mk

define KernelPackage/sound-core-kold
  SUBMENU:=$(AUDIO_MENU)
  DEPENDS:=@USB_SUPPORT @LINUX_2_6_22
  TITLE:=Advanced Linux Sound Architecture
  PROVIDES:=kmod-sound-core
  FILES:= $(foreach mod,$(shell cat ./files/30-sound-core), \
	$(PKG_BUILD_DIR)/modules/$(mod).$(LINUX_KMOD_SUFFIX))
  FILES+=$(LINUX_DIR)/sound/soundcore.$(LINUX_KMOD_SUFFIX)
  KCONFIG:= \
	CONFIG_SOUND \
	CONFIG_SND \
	CONFIG_SND_HWDEP \
	CONFIG_SND_RAWMIDI \
	CONFIG_SND_TIMER \
	CONFIG_SND_PCM \
	CONFIG_SND_SEQUENCER \
	CONFIG_SND_VIRMIDI \
	CONFIG_SND_SEQ_DUMMY \
	CONFIG_SND_SEQUENCER_OSS=y \
	CONFIG_HOSTAUDIO \
	CONFIG_SND_PCM_OSS \
	CONFIG_SND_MIXER_OSS \
	CONFIG_SOUND_OSS_CORE_PRECLAIM=y
  AUTOLOAD=$(call AutoLoad,30,$(shell cat ./files/30-sound-core))
endef

define KernelPackage/audio/Depends
  SUBMENU:=$(AUDIO_MENU)
  DEPENDS+=kmod-sound-core-kold $(1)
endef

define KernelPackage/usb-audio-kold
$(call KernelPackage/audio/Depends,@LINUX_2_6_22||USB_SUPPORT +kmod-usb-core)
  SUBMENU:=$(AUDIO_MENU)
  TITLE:=USB Linux Sound drivers
  PROVIDES:=kmod-usb-audio
  FILES:= $(foreach mod,$(shell cat ./files/60-usb-audio), \
	$(PKG_BUILD_DIR)/modules/$(mod).$(LINUX_KMOD_SUFFIX))
  AUTOLOAD=$(call AutoLoad,60,$(shell cat ./files/60-usb-audio))
endef

ifeq ($(KERNEL),2.4)
  ifeq ($(LINUX_KARCH),i386)
    KERNEL_C_OPTS:= -Os -mpreferred-stack-boundary=2 -march=i486 -fno-unit-at-a-time
  endif
  ifeq ($(LINUX_KARCH),mips)
    KERNEL_C_OPTS:= -Os -G 0 -mlong-calls -mno-abicalls -fno-pic -finline-limit=100000 -mabi=32 -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2 -Wa,-mips32r2 -Wa,--trap
  endif
  ifeq ($(LINUX_KARCH),mipsel)
    KERNEL_C_OPTS:= -Os -G 0 -mlong-calls -mno-abicalls -fno-pic -finline-limit=100000 -mabi=32 -march=mips32r2 -Wa,-32 -Wa,-march=mips32r2 -Wa,-mips32r2 -Wa,--trap
  endif
endif

ifeq ($(LINUX_KARCH),i386)
  KERNEL_C_INCS:= -I$(LINUX_DIR)/include/asm-i386/mach-generic -I$(LINUX_DIR)/include/asm-i386/mach-default
endif
ifeq ($(LINUX_KARCH),mips)
  KERNEL_C_INCS:= -I$(LINUX_DIR)/include/asm-mips/mach-generic
endif
ifeq ($(LINUX_KARCH),mipsel)
  KERNEL_C_INCS:= -I$(LINUX_DIR)/include/asm-mips/mach-generic
endif

CONFIGURE_VARS:= \
	CFLAGS="$(KERNEL_C_INCS)"

CONFIGURE_ARGS:= \
	--with-build="$(LINUX_DIR)" \
	--with-kernel="$(LINUX_DIR)" \
	--with-cross="$(KERNEL_CROSS)" \
	--with-redhat=no \
	--with-suse=no \
	--with-oss=yes \
	--with-isapnp=no \
	--with-sequencer=yes \
	--with-cards=usb-audio

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		ARCH="$(LINUX_KARCH)" \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		CC="$(KERNEL_CC)" \
		CPP="$(KERNEL_CC) -E" \
		c_opts="$(KERNEL_C_OPTS)" \
		CP="$(CP)" \
		all
endef

$(eval $(call KernelPackage,sound-core-kold))
$(eval $(call KernelPackage,usb-audio-kold))
