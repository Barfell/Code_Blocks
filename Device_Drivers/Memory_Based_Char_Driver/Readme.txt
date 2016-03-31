#Run instructions (run as root)

1) create a char device
mknod -m 0666 /dev/mem_chr c 60 0

#creates a char device named mem_chr with major number=60 & minor number=0

2) load module
insmod ./Mem_Char.ko

3) check if the module loaded correctly
lsmod

4) run user program
./user_prog

#Instead of the userspace program, data can also be written/read using the shell directly.
#To write data:
echo -n "ABCDE" > /dev/mem_chr 

#To read data:
cat /dev/mem_chr   

5) finally remove module
rmmod Mem_Char

#if printk() statements do not get printed on the terminal, run demsg to check the kernel messages

#The driver accesses a memory location as if it were a device. 
#The user program accesses (reads and writes) data from that location.
#Even if we write multiple bytes to that location, the driver will always store the most recent byte.
#The previous bytes are discarded.
