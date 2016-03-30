#ifndef __CONFIG_COMPAT_H__
#define __CONFIG_COMPAT_H__

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33)
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif


#define NEED_SOUND_DRIVER_H 1

#define COMPAT_SND_CTL_BOOLEAN_MONO 1

#define COMPAT_PCM_TO_RATE_BIT 1

#define NEED_IS_SINGULAR 1

#define NEED_CLAMP 1

#define NEED_PROC_CREATE 1

#define NEED_ALGO_CONTROL 1

#define NEED_USB_ENDPOINT_TYPE 1

#define NEED_PCI_IOREMAP_BAR 1

#define NEED_SND_CARD_CREATE

#define NEED_POLL_SCHEDULE 1

#define NEED_SND_BUG_ON 1

#define NEED_BITOPS 1

#endif
