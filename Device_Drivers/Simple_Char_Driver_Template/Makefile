#if KERNELRELEASE is defined, we've been invoked from the kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := char_temp.o
#Otherwise we were called directly from the command-line; invoke the kernel build system.

else
	KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	#KERNELDIR can be used to compile for a different version of the kernel than the one currently running
	PWD := $(shell pwd)
    
default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif
