#!/bin/sh

cd rtems-libbsd

waf configure --prefix=/home/wt/zynq/install  \
		--buildset=buildset/default.ini \
		--optimization=0 \
		--rtems-bsps=arm/xilinx_zynq_zedboard

waf && waf install
