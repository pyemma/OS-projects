KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
	obj-m += py_wr.o
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	-rm *.ko
	-rm *.o
	-rm -f Mo*
	-rm *.mod.*

