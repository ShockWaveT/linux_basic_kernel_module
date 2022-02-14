obj-m := main.o
ARCH=arm
CROSS_COMPILE=/home/arunc/projects/arun/tool_chain/gcc-arm-none-eabi-10.3-2021.10-x86_64-linux/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-
KERN_DIR =/home/arunc/projects/arun/linux_source/beaglebone_4.19/linux-4.19
HOST_KERN_DIR = /lib/modules/$(shell uname -r)/build/

#the -C switch is to trigger the top level Makefile.
#This makefile will actually be used by the top level makefile to build the module.
#This local makefile will not be directly used by kbuild system.

all:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) modules
	
clean:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) clean
	
help:
	make ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) -C $(KERN_DIR) M=$(PWD) help
	
host:
	make -C $(HOST_KERN_DIR) M=$(PWD) modules
	
	
