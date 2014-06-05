ifneq ($(KERNELRELEASE),)

obj-m := helloworld.o
else

PWD := $(shell pwd)
KVER ?= $(shell uname -r)
KDIR := /lib/modules/$(KVER)/build
all:
        $(MAKE) -C $(KDIR) M=$(PWD) modules
clean:
        rm -rf *.cmd *.o *.mod.c *.ko *.mod.o *.ko.unsigned  modules.order  Module.symvers                                                                              
endif
