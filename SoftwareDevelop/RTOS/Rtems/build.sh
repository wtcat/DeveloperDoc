#!/bin/sh

cd rtems

./bootstrap -c && ./bootstrap -H && ./bootstrap

cd ../build && rm -rf *

../rtems/configure --target=arm-rtems5 \
					--prefix=/home/wt/zynq/install \
					--disable-networking \
					--enable-posix \
					--enable-smp \
					--enable-cxx \
					--enable-rtemsbsp=xilinx_zynq_zedboard
#					--enable-rtemsbsp=xilinx_zynq_a9_qemu

