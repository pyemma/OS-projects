
KVER=$(shell uname -r)
KDIR=/lib/modules/$(KVER)/build
PWD=$(shell pwd)
obj-m +=list_all_pid.o 
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean


