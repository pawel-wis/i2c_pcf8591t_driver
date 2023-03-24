obj-m += i2c_pcf8591t_driver.o

KERN_VER = $(shell uname -r)
PWD = $(shell pwd)
KO_NAME = i2c_pcf8591t_driver.ko

all: install
	echo Builded Device Tree PCF and Kernel module
install:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) modules
	sudo insmod $(KO_NAME)
uninstall:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) clean
	sudo rmmod i2c_pcf8591t_driver
build:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(KERN_VER)/build M=$(PWD) clean
