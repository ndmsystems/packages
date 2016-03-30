/*
 * $Id: compat.h,v 1.44 2006/01/15 09:35:16 mchehab Exp $
 */

#ifndef _COMPAT_H
#define _COMPAT_H

#include "config.h"

/* In v2.6.19-rc6-118-g52bad64 struct work_struct was was changed to be only for
 * non-delayed work and struct delayed_work was created for delayed work.  This
 * will rename the structures.  Hopefully no one will decide to name something
 * delayed_work in the same context as something named work_struct.  */
#ifdef NEED_DELAYED_WORK
#define delayed_work work_struct
#define INIT_DELAYED_WORK(a,b,c)	INIT_WORK(a,b,c)
#endif

#define EXPERIMENTAL_TREE

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 35)
#define usb_buffer_alloc(dev, size, mem_flags, dma) usb_alloc_coherent(dev, size, mem_flags, dma)
#define usb_buffer_free(dev, size, addr, dma) usb_free_coherent(dev, size, addr, dma)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
#define	KERN_CONT	""
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 32)
#define ir_register_class(a) input_register_device(a)
#define ir_unregister_class(a) input_unregister_device(a)
#endif

/* To allow I2C compatibility code to work */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 24)
#include <linux/i2c-dev.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 30)
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <linux/err.h>
static inline void *memdup_user(const void __user *src, size_t len)
{
	void *p;

	/*
	 * Always use GFP_KERNEL, since copy_from_user() can sleep and
	 * cause pagefault, which makes it pointless to use GFP_NOFS
	 * or GFP_ATOMIC.
	 */
	p = kmalloc_track_caller(len, GFP_KERNEL);
	if (!p)
		return ERR_PTR(-ENOMEM);

	if (copy_from_user(p, src, len)) {
		kfree(p);
		return ERR_PTR(-EFAULT);
	}

	return p;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 29)
static inline int pci_msi_enabled(void)
{
#ifndef CONFIG_PCI_MSI
	return 0;
#else
	return 1;
#endif
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 26)
#ifdef CONFIG_PROC_FS
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/device.h>
#endif
#endif

#ifndef KEY_NUMERIC_0
#define KEY_NUMERIC_0           0x200   /* used by phones, remote controls, */
#define KEY_NUMERIC_1           0x201   /* and other keypads */
#define KEY_NUMERIC_2           0x202
#define KEY_NUMERIC_3           0x203
#define KEY_NUMERIC_4           0x204
#define KEY_NUMERIC_5           0x205
#define KEY_NUMERIC_6           0x206
#define KEY_NUMERIC_7           0x207
#define KEY_NUMERIC_8           0x208
#define KEY_NUMERIC_9           0x209
#define KEY_NUMERIC_STAR        0x20a
#define KEY_NUMERIC_POUND       0x20b
#endif

#ifndef DEFINE_PCI_DEVICE_TABLE
#define DEFINE_PCI_DEVICE_TABLE(_table) \
	const struct pci_device_id _table[] __devinitconst
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 34)
#define netdev_mc_count(dev) ((dev)->mc_count)
#define netdev_mc_empty(dev) (netdev_mc_count(dev) == 0)
#define netdev_for_each_mc_addr(mclist, dev) \
	for (mclist = dev->mc_list; mclist; mclist = mclist->next)
#endif

#ifndef KEY_CONTEXT_MENU
#define KEY_CONTEXT_MENU        0x1b6   /* GenDesc - system context menu */
#endif

#ifndef BIT_MASK
#define BIT_MASK(nr)            (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)            ((nr) / BITS_PER_LONG)
#endif

#if LINUX_VERSION_CODE == KERNEL_VERSION(2,6,32)
#include <linux/ctype.h>
#undef _P
static inline char *skip_spaces(const char *str)
{
	while (isspace(*str))
		++str;
	return (char *)str;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define valtype	unsigned long
static inline int strict_strtoul(const char *cp, unsigned int base, valtype *res)
{
	char *tail;
	valtype val;
	size_t len;

	*res = 0;
	len = strlen(cp);
	if (len == 0)
		return -EINVAL;

	val = simple_strtoul(cp, &tail, base);
	if ((*tail == '\0') ||
		((len == (size_t)(tail - cp) + 1) && (*tail == '\n'))) {
		*res = val;
		return 0;
	}

	return -EINVAL;
}
#endif

#ifndef KEY_DASHBOARD
#define KEY_DASHBOARD           204     /* AL Dashboard */
#endif
/* To allow alsa code to work */
#ifdef NEED_SOUND_DRIVER_H
#include <sound/driver.h>
#endif

#ifdef NEED_SND_CARD_CREATE
#include <sound/core.h>
#endif

#ifdef NEED_ALGO_CONTROL
#include <linux/i2c.h>
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
#define time_is_after_eq_jiffies(a) (time_before_eq(jiffies, a))
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,23)
#define set_freezable()
#define cancel_delayed_work_sync cancel_rearming_delayed_work
#define DEFAULT_POLLMASK (POLLIN | POLLOUT | POLLRDNORM | POLLWRNORM)
#endif

#ifndef __pure
#  define __pure __attribute__((pure))
#endif

/* device_create/destroy added in 2.6.18 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
/* on older kernels, class_device_create will in turn be a compat macro */
# define device_create(a, b, c, d, e, f, g) class_device_create(a, NULL, c, b, d, e, f, g)
# define device_destroy(a, b) class_device_destroy(a, b)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
#define IRQF_SHARED		SA_SHIRQ
#define IRQF_DISABLED		SA_INTERRUPT
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
#define DIV_ROUND_UP(n, d) (((n) + (d) - 1) / (d))
#define PCIAGP_FAIL 0
#define vmalloc_32_user(a) vmalloc_32(a)
#endif

#ifndef DIV_ROUND_CLOSEST
#define DIV_ROUND_CLOSEST(x, divisor)(                  \
{                                                       \
	typeof(divisor) __divisor = divisor;            \
	(((x) + ((__divisor) / 2)) / (__divisor));      \
}                                                       \
)
#endif

#ifdef NEED_BOOL_TYPE
/* bool type and enum-based definition of true and false was added in 2.6.19 */
typedef int bool;
enum {
	false   = 0,
	true    = 1
};
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,22)
#define sony_pic_camera_command(a,b) sonypi_camera_command(a,b)

#define SONY_PIC_COMMAND_SETCAMERAAGC        SONYPI_COMMAND_SETCAMERAAGC
#define SONY_PIC_COMMAND_SETCAMERABRIGHTNESS SONYPI_COMMAND_SETCAMERABRIGHTNESS
#define SONY_PIC_COMMAND_SETCAMERACOLOR      SONYPI_COMMAND_SETCAMERACOLOR
#define SONY_PIC_COMMAND_SETCAMERACONTRAST   SONYPI_COMMAND_SETCAMERACONTRAST
#define SONY_PIC_COMMAND_SETCAMERAHUE        SONYPI_COMMAND_SETCAMERAHUE
#define SONY_PIC_COMMAND_SETCAMERAPICTURE    SONYPI_COMMAND_SETCAMERAPICTURE
#define SONY_PIC_COMMAND_SETCAMERASHARPNESS  SONYPI_COMMAND_SETCAMERASHARPNESS
#define SONY_PIC_COMMAND_SETCAMERA           SONYPI_COMMAND_SETCAMERA
#endif

/* pci_dev got a new revision field in 2.6.23-rc1 */
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,23) && defined(LINUX_PCI_H)
/* Just make it easier to subsitute pci_dev->revision with
 * v4l_compat_pci_rev(pci_dev).  It's too bad there isn't some kind of context
 * sensitive macro in C that could do this for us.  */
static inline u8 v4l_compat_pci_rev(struct pci_dev *pci)
{ u8 rev; pci_read_config_byte(pci, PCI_REVISION_ID, &rev); return rev; }
#endif

#if defined(COMPAT_PCM_TO_RATE_BIT) && defined(__SOUND_PCM_H)
/* New alsa core utility function */
static inline unsigned int snd_pcm_rate_to_rate_bit(unsigned int rate)
{
	static const unsigned int rates[] = { 5512, 8000, 11025, 16000, 22050,
		32000, 44100, 48000, 64000, 88200, 96000, 176400, 192000 };
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(rates); i++)
		if (rates[i] == rate)
			return 1u << i;
	return SNDRV_PCM_RATE_KNOT;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
# define task_pid_nr(current) ((current)->pid)

# define sg_init_table(a,b)
# define sg_page(p) (sg->page)
# define sg_set_page(sglist,pg,sz,off)					\
do {									\
	struct scatterlist *p=sglist;					\
	p->page   = pg;							\
	p->length = sz;							\
	p->offset = off;						\
} while (0)

#define pr_err(fmt, arg...) \
	printk(KERN_ERR fmt, ##arg)
#endif

#ifndef BIT_MASK
# define BIT_MASK(nr)            (1UL << ((nr) % BITS_PER_LONG))
# define BIT_WORD(nr)            ((nr) / BITS_PER_LONG)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,24)
#define i2c_verify_client(dev)	\
	((dev->bus == &i2c_bus_type) ? to_i2c_client(dev) : NULL)
#elif LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
#define i2c_verify_client(dev) \
	((dev->bus && 0 == strcmp(dev->bus->name, "i2c")) ? to_i2c_client(dev) : NULL)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 31)
/* Construct an I2C_CLIENT_END-terminated array of i2c addresses */
#define I2C_ADDRS(addr, addrs...) \
	((const unsigned short []){ addr, ## addrs, I2C_CLIENT_END })
#endif

#ifndef USB_DEVICE_AND_INTERFACE_INFO
# define USB_DEVICE_AND_INTERFACE_INFO(vend,prod,cl,sc,pr) \
	.match_flags = USB_DEVICE_ID_MATCH_INT_INFO \
		| USB_DEVICE_ID_MATCH_DEVICE, \
	.idVendor = (vend), .idProduct = (prod), \
	.bInterfaceClass = (cl), \
	.bInterfaceSubClass = (sc), .bInterfaceProtocol = (pr)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 26)
#define get_unaligned_be16(a)					\
	be16_to_cpu(get_unaligned((unsigned short *)(a)))
#define put_unaligned_be16(r, a)				\
	put_unaligned(cpu_to_be16(r), ((unsigned short *)(a)))
#define get_unaligned_le16(a)					\
	le16_to_cpu(get_unaligned((unsigned short *)(a)))
#define put_unaligned_le16(r, a)				\
	put_unaligned(cpu_to_le16(r), ((unsigned short *)(a)))
#define get_unaligned_be32(a)					\
	be32_to_cpu(get_unaligned((u32 *)(a)))
#define put_unaligned_be32(r, a)				\
	put_unaligned(cpu_to_be32(r), ((u32 *)(a)))
#define get_unaligned_le32(a)					\
	le32_to_cpu(get_unaligned((u32 *)(a)))
#define put_unaligned_le32(r, a)				\
	put_unaligned(cpu_to_le32(r), ((u32 *)(a)))
#define get_unaligned_le64(a)					\
	le64_to_cpu(get_unaligned((u64 *)(a)))
#define put_unaligned_le64(r, a)				\
	put_unaligned(cpu_to_le64(r), ((u64 *)(a)))
#endif

#ifdef NEED_PROC_CREATE
#ifdef CONFIG_PROC_FS
static inline struct proc_dir_entry *proc_create(const char *a,
	mode_t b, struct proc_dir_entry *c, const struct file_operations *d)
{
	struct proc_dir_entry *e;

	e = create_proc_entry(a, b, c);
	if (e) {
		e->owner = THIS_MODULE;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17)
		e->proc_fops = d;
#else
		e->proc_fops = (struct file_operations *)d;
#endif
	}
	return e;
}
#endif
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 26)
#ifdef CONFIG_PROC_FS
static inline struct proc_dir_entry *proc_create_data(const char *a,
	mode_t b, struct proc_dir_entry *c, const struct file_operations *d,
	void *f)
{
	struct proc_dir_entry *e;

	e = create_proc_entry(a, b, c);
	if (e) {
		e->owner = THIS_MODULE;
#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 17)
		e->proc_fops = d;
#else
		e->proc_fops = (struct file_operations *)d;
#endif
		e->data = f;
	}
	return e;
}
#endif
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 17)
#define hweight64(x)  generic_hweight64(x)
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
typedef unsigned long uintptr_t;
#endif

#ifdef NEED_IS_SINGULAR
static inline int list_is_singular(const struct list_head *head)
{
	return !list_empty(head) && (head->next == head->prev);
}
#endif

#ifdef NEED_CLAMP
#define clamp( x, l, h )        max_t( __typeof__( x ),		\
				      ( l ),			\
				      min_t( __typeof__( x ),	\
					     ( h ),        	\
					     ( x ) ) )
#define clamp_val(val, min, max) ({		\
	typeof(val) __val = (val);		\
	typeof(val) __min = (min);		\
	typeof(val) __max = (max);		\
	__val = __val < __min ? __min : __val;	\
	__val > __max ? __max : __val; })
#endif

#ifdef NEED_ALGO_CONTROL
static inline int dummy_algo_control(struct i2c_adapter *adapter,
			     unsigned int cmd, unsigned long arg)
{
	return 0;
}
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 26)
#define div64_u64(a,b) div64_64(a,b)

#define dev_name(dev)	((dev)->bus_id)

#define dev_set_name(dev, fmt, arg...) ({	\
	snprintf((dev)->bus_id, sizeof((dev)->bus_id), fmt , ## arg); \
	0;					\
})
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 27)
#define current_uid() (current->uid)
#endif

#ifndef WARN
#define WARN(condition, format...) ({					\
	int __ret_warn_on = !!(condition);				\
	if (unlikely(__ret_warn_on))					\
		printk(KERN_WARNING format);				\
	unlikely(__ret_warn_on);					\
})
#endif

#ifdef NEED_SND_BUG_ON
#define snd_BUG_ON(cond)	WARN((cond), "BUG? (%s)\n", __stringify(cond))
#endif

#ifdef NEED_BITOPS
#define BIT(x)  (1UL<<((x)%BITS_PER_LONG))
#endif

#ifndef PCI_DEVICE_ID_MARVELL_88ALP01_CCIC
#define PCI_DEVICE_ID_MARVELL_88ALP01_CCIC     0x4102
#endif

#ifdef __LINUX_USB_H
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 19)
/*
 * usb_endpoint_* functions
 *
 * Included in Linux 2.6.19
 * Backported to 2.6.18 in Red Hat Enterprise Linux 5.2
 */

#ifdef RHEL_RELEASE_CODE
#if RHEL_RELEASE_CODE >= RHEL_RELEASE_VERSION(5, 2)
#define RHEL_HAS_USB_ENDPOINT
#endif
#endif

#ifndef RHEL_HAS_USB_ENDPOINT
static inline int
usb_endpoint_dir_in(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN;
}

static inline int
usb_endpoint_xfer_int(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_INT;
}

static inline int
usb_endpoint_xfer_isoc(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_ISOC;
}

static inline int
usb_endpoint_xfer_bulk(const struct usb_endpoint_descriptor *epd)
{
	return (epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_BULK;
}

static inline int
usb_endpoint_is_int_in(const struct usb_endpoint_descriptor *epd)
{
	return usb_endpoint_xfer_int(epd) && usb_endpoint_dir_in(epd);
}

static inline int usb_endpoint_dir_out(
				const struct usb_endpoint_descriptor *epd)
{
	return ((epd->bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_OUT);
}

static inline int usb_endpoint_is_bulk_in(
				const struct usb_endpoint_descriptor *epd)
{
	return (usb_endpoint_xfer_bulk(epd) && usb_endpoint_dir_in(epd));
}

static inline int usb_endpoint_is_bulk_out(
				const struct usb_endpoint_descriptor *epd)
{
	return (usb_endpoint_xfer_bulk(epd) && usb_endpoint_dir_out(epd));
}

static inline int usb_endpoint_is_int_out(
				const struct usb_endpoint_descriptor *epd)
{
	return (usb_endpoint_xfer_int(epd) && usb_endpoint_dir_out(epd));
}

static inline int usb_endpoint_is_isoc_in(
				const struct usb_endpoint_descriptor *epd)
{
	return (usb_endpoint_xfer_isoc(epd) && usb_endpoint_dir_in(epd));
}

static inline int usb_endpoint_is_isoc_out(
				const struct usb_endpoint_descriptor *epd)
{
	return (usb_endpoint_xfer_isoc(epd) && usb_endpoint_dir_out(epd));
}
#endif /* RHEL_HAS_USB_ENDPOINT */
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 21)
#ifndef RHEL_HAS_USB_ENDPOINT
static inline int usb_endpoint_xfer_control(
				const struct usb_endpoint_descriptor *epd)
{
	return ((epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) ==
		USB_ENDPOINT_XFER_CONTROL);
}
#endif /* RHEL_HAS_USB_ENDPOINT */
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 24)
static inline int usb_endpoint_num(const struct usb_endpoint_descriptor *epd)
{
	return epd->bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
}
#endif

#ifdef NEED_USB_ENDPOINT_TYPE
static inline int usb_endpoint_type(const struct usb_endpoint_descriptor *epd)
{
	return epd->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK;
}
#endif
#endif /* __LINUX_USB_H */

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 22)
/*
 * Linked list API
 */
#define list_first_entry(ptr, type, member) \
	list_entry((ptr)->next, type, member)

/*
 * uninitialized_var() macro
 */
#define uninitialized_var(x) x = x
#endif

#ifdef NEED_NETDEV_PRIV
#define netdev_priv(dev)	((dev)->priv)
#endif

#ifdef NEED_PCI_IOREMAP_BAR
#define pci_ioremap_bar(pdev, bar) \
	 ioremap_nocache(pci_resource_start(pdev, bar),	\
			 pci_resource_len(pdev, bar))
#endif

#ifdef NEED_POLL_SCHEDULE
#define  poll_schedule(pwq, task)			\
	do {						\
		set_current_state(task);		\
		schedule();				\
		set_current_state(TASK_RUNNING);	\
	} while (0)
#endif

#ifdef NEED_SND_CARD_CREATE
static inline int snd_card_create(int idx, const char *id,
			      struct module *module, int extra_size,
			      struct snd_card **card)
{
	*card = snd_card_new(idx, id, module, extra_size);

	if (*card == NULL)
		return -ENOMEM;
	return 0;
}
#endif

/* This macro was added in commit v2.6.23-5792-g34c6538 */
#ifndef DMA_BIT_MASK
#define DMA_BIT_MASK(n)	(((n) == 64) ? ~0ULL : ((1ULL<<(n))-1))
#endif

/* __fls() was added for generic code in 2.6.29, existed for just 64-bit arches
 * since 2.6.26 (v2.6.25-5228-g56a6b1e), and was x86-64 only before then.  We
 * only want this compat code when __fls doesn't exist, which 2.6.29 or later,
 * non x86-64, and non 64-bit that's 2.6.26 or later. */
#if !(LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 29) || \
	defined(__x86_64__) || \
	(BITS_PER_LONG == 64 && LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 26)))
/* This define will prevent breakage if __fls was already defined. */
#undef __fls
#define __fls v4l_compat_fls
static inline unsigned long v4l_compat_fls(unsigned long x)
{
	return fls(x) - 1;
}
#endif

/*
 * Compatibility code for hrtimer API
 * This will make hrtimer usable for kernels 2.6.22 and later.
 * For earlier kernels, not all required functions are exported
 * so there's nothing we can do.
 */

#ifdef _LINUX_HRTIMER_H
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 25) && \
	LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 22)
/* Forward a hrtimer so it expires after the hrtimer's current now */
static inline unsigned long hrtimer_forward_now(struct hrtimer *timer,
						ktime_t interval)
{
	return hrtimer_forward(timer, timer->base->get_time(), interval);
}
#endif
#endif /* _LINUX_HRTIMER_H */

#ifndef PCI_VDEVICE
#define PCI_VDEVICE(vendor, device)             \
	PCI_VENDOR_ID_##vendor, (device),       \
	PCI_ANY_ID, PCI_ANY_ID, 0, 0
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 25)
#define __devinitconst
#endif

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 22)
#define strncasecmp(a, b, c) strnicmp(a, b, c)
#define strcasecmp(a, b) strnicmp(a, b, sizeof(a))
#endif


#endif /*  _COMPAT_H */
