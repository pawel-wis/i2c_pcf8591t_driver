obj-m += i2c_pcf8591t_driver.o

KERN_VER = $(shell uname -r)
PWD = $(shell pwd)
KO_NAME = i2c_pcf8591t_driver.ko

all: module
	echo Builded Device Tree PCF and Kernel module
module:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) modules
	sudo insmod $(KO_NAME)
clean:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) clean
	sudo rmmod i2c_pcf8591t_driver
