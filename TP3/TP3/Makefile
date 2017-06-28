#
# Makefile for compiling a congestion control module. This has been
# tested with Linux version 2.6.26.
#

obj-m    := TP3.o


KDIR    := /lib/modules/$(shell uname -r)/build
PWD    := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f tcp-cct.mod.c tcp-cct.mod.o tcp-cct.ko tcp-cct.o
	rm -f modules.order Module.symvers
	rm -f .??*cmd
	rm -rf .tmp_versions
