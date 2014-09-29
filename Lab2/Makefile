KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
obj-m +=list.o
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) mdoules

