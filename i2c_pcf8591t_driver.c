/*

* Copyright (C) 2023, Pawel Wisniewski

*/

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/proc_fs.h>

#define MODULE_NAME "PCF8591T_DRIVER"
#define SLAVE_DEVICE_NAME (PCF8591T)
#define DEVICE_ADDR 0x48
#define I2C_BUS_NUM 1
#define AIN1 0x40

// Credits
MODULE_AUTHOR("Pawel Wisniewski");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("I2C driver for PCF8591T AC/DC conventer.");
MODULE_VERSION("0.3");

typedef unsigned char u8;

// I2C Configuration for i2c_transfer call
static struct i2c_adapter *pcf8591t_adapter;

static u8 get_value_from_pcf(struct i2c_adapter *adap) {
	struct i2c_msg msgs[2];
	u8 ret = 0;
	u8 outbuf[] = {AIN1, 0};
	msgs[0].addr = DEVICE_ADDR;
	msgs[0].flags = 0;
	msgs[0].len = sizeof(outbuf);
	msgs[0].buf = outbuf;

	msgs[1].addr = DEVICE_ADDR;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = sizeof(ret);
	msgs[1].buf = &ret;

	i2c_transfer(adap, msgs, 2);
	printk("[%s] Insinde read val: %d\n", MODULE_NAME, ret);

	return ret;
}

//proc_fs mount
static struct proc_dir_entry *entry_file;

static ssize_t proc_fs_read(struct file *file, char __user *user_buffer, size_t count, loff_t *offset) {
 	u8 output = get_value_from_pcf(pcf8591t_adapter);
//	char* output = "Test_v\n";
	ssize_t bytes_readed = simple_read_from_buffer(user_buffer, count, offset, &output, sizeof(output));
    printk("[%s] Bytes readed: %d || Output value: %d\n", MODULE_NAME, bytes_readed, output);
	return bytes_readed;
}

static const struct proc_ops fops = {
	.proc_read = proc_fs_read,
};




static int __init pcf_driver_init(void) {
	printk("[%s]: Init called\n", MODULE_NAME);
	pcf8591t_adapter = i2c_get_adapter(I2C_BUS_NUM);
	if(pcf8591t_adapter == NULL) {
		printk(KERN_ALERT "[%s]: Can't create i2c adapter!\n", MODULE_NAME);
		return -1;
	}
	entry_file = proc_create("pcf8591t", 0444, NULL, &fops);
	printk("[%s]: Init succes\n", MODULE_NAME);
	return 0;
}

static void __exit pcf_driver_exit(void) {
	proc_remove(entry_file);
	printk("[%s]: Exit called\n", MODULE_NAME);
}

module_init(pcf_driver_init);
module_exit(pcf_driver_exit);

