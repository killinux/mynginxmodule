ifneq ($(KERNELRELEASE),)

obj-m := helloworld.o
else

PWD := $(shell pwd)
KVER ?= $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build
all:
	$(MAKE) -C $(KDIR) M=$(PWD) moudules
clean:
	rm -rf *.cmd *.o *.mod.c *.ko *.mod.o
endif
