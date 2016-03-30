/*
 * v4l2-i2c-drv.h - contains I2C handling code that's identical for
 *		    all V4L2 I2C drivers. Use this header if the
 *		    I2C driver is only used by drivers converted
 *		    to the bus-based I2C API.
 *
 * Copyright (C) 2007 Hans Verkuil <hverkuil@xs4all.nl>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* NOTE: the full version of this header is in the v4l-dvb repository
 * and allows v4l i2c drivers to be compiled on pre-2.6.26 kernels.
 * The version of this header as it appears in the kernel is a stripped
 * version (without all the backwards compatibility stuff) and so it
 * looks a bit odd.
 *
 * If you look at the full version then you will understand the reason
 * for introducing this header since you really don't want to have all
 * the tricky backwards compatibility code in each and every i2c driver.
 *
 * If the i2c driver will never be compiled for pre-2.6.26 kernels, then
 * DO NOT USE this header! Just write it as a regular i2c driver.
 */

#ifndef __V4L2_I2C_DRV_H__
#define __V4L2_I2C_DRV_H__

#include "v4l2-common.h"

struct v4l2_i2c_driver_data {
	const char * const name;
	int (*command)(struct i2c_client *client, unsigned int cmd, void *arg);
	int (*probe)(struct i2c_client *client, const struct i2c_device_id *id);
	int (*remove)(struct i2c_client *client);
	int (*suspend)(struct i2c_client *client, pm_message_t state);
	int (*resume)(struct i2c_client *client);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 26)
	int (*legacy_probe)(struct i2c_adapter *adapter);
	int legacy_class;
#else
	const struct i2c_device_id *id_table;
#endif
};

static struct v4l2_i2c_driver_data v4l2_i2c_data;
static struct i2c_driver v4l2_i2c_driver;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 26)

/* Bus-based I2C implementation for kernels >= 2.6.26 */

static int __init v4l2_i2c_drv_init(void)
{
	v4l2_i2c_driver.driver.name = v4l2_i2c_data.name;
	v4l2_i2c_driver.command = v4l2_i2c_data.command;
	v4l2_i2c_driver.probe = v4l2_i2c_data.probe;
	v4l2_i2c_driver.remove = v4l2_i2c_data.remove;
	v4l2_i2c_driver.suspend = v4l2_i2c_data.suspend;
	v4l2_i2c_driver.resume = v4l2_i2c_data.resume;
	v4l2_i2c_driver.id_table = v4l2_i2c_data.id_table;
	return i2c_add_driver(&v4l2_i2c_driver);
}

#else

#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 25)
static struct i2c_client_address_data addr_data;
#else
static const struct i2c_client_address_data addr_data;
#endif

/* Bus-based I2C API is not present, add legacy code */

static int v4l2_i2c_drv_attach_legacy(struct i2c_adapter *adapter, int address, int kind)
{
	return v4l2_i2c_attach(adapter, address, &v4l2_i2c_driver,
			v4l2_i2c_data.name, v4l2_i2c_data.probe);
}

static int v4l2_i2c_drv_probe_legacy(struct i2c_adapter *adapter)
{
	if (v4l2_i2c_data.legacy_probe) {
		if (v4l2_i2c_data.legacy_probe(adapter))
			return i2c_probe(adapter, &addr_data, v4l2_i2c_drv_attach_legacy);
		return 0;
	}
	if (adapter->class & v4l2_i2c_data.legacy_class)
		return i2c_probe(adapter, &addr_data, v4l2_i2c_drv_attach_legacy);
	return 0;
}

static int v4l2_i2c_drv_detach_legacy(struct i2c_client *client)
{
	int err;

	if (v4l2_i2c_data.remove)
		v4l2_i2c_data.remove(client);

	err = i2c_detach_client(client);
	if (err)
		return err;
	kfree(client);
	return 0;
}

#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 20)
static int v4l2_i2c_drv_suspend_helper(struct i2c_client *client, pm_message_t state)
#else
static int v4l2_i2c_drv_suspend_helper(struct device * dev, pm_message_t state)
#endif
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 20)
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);
#endif
	return v4l2_i2c_data.suspend ? v4l2_i2c_data.suspend(client, state) : 0;
}

#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 20)
static int v4l2_i2c_drv_resume_helper(struct i2c_client *client)
#else
static int v4l2_i2c_drv_resume_helper(struct device * dev)
#endif
{
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 20)
	struct i2c_client *client = container_of(dev, struct i2c_client, dev);
#endif
	return v4l2_i2c_data.resume ? v4l2_i2c_data.resume(client) : 0;
}

/* ----------------------------------------------------------------------- */

static struct i2c_driver v4l2_i2c_driver = {
	.driver = {
		.owner = THIS_MODULE,
#if LINUX_VERSION_CODE <= KERNEL_VERSION(2, 6, 20)
		.suspend = v4l2_i2c_drv_suspend_helper,
		.resume  = v4l2_i2c_drv_resume_helper,
#endif
	},
	.attach_adapter = v4l2_i2c_drv_probe_legacy,
	.detach_client = v4l2_i2c_drv_detach_legacy,
#if LINUX_VERSION_CODE > KERNEL_VERSION(2, 6, 20)
	.suspend = v4l2_i2c_drv_suspend_helper,
	.resume  = v4l2_i2c_drv_resume_helper,
#endif
};

/* ----------------------------------------------------------------------- */

static int __init v4l2_i2c_drv_init(void)
{
	if (v4l2_i2c_data.legacy_class == 0)
		v4l2_i2c_data.legacy_class = I2C_CLASS_TV_ANALOG;

	v4l2_i2c_driver.driver.name = v4l2_i2c_data.name;
	v4l2_i2c_driver.command = v4l2_i2c_data.command;
	return i2c_add_driver(&v4l2_i2c_driver);
}

/* End legacy code */

#endif

static void __exit v4l2_i2c_drv_cleanup(void)
{
	i2c_del_driver(&v4l2_i2c_driver);
}

module_init(v4l2_i2c_drv_init);
module_exit(v4l2_i2c_drv_cleanup);

#endif /* __V4L2_I2C_DRV_H__ */
