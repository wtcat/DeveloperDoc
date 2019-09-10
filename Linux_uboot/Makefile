
ifneq ($(KERNELRELEASE),)

obj-m := globmem.o
obj-m += loadcpu1.o
obj-m += xlnx_button.o

else

PWD  := $(shell pwd)
KDIR := /home/wt/work/linux/xilinx/linux-digilent-digilent-v3.6


all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf-

clean:
	rm -rf *.o *.ko *.order *.symvers *.mod.c

endif
