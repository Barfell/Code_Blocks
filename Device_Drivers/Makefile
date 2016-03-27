obj-m := Hello_World.o

all:
	make -C /usr/src/linux-headers-4.2.0-30-generic M=`pwd` modules

clean:
	make -C /usr/src/linux-headers-4.2.0-30-generic M=`pwd` clean
