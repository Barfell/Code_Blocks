#Run instructions (run as root)

1) create a char device
mknod -m 0666 /dev/char_tmp c 60 0

#creates a char device named char_tmp with major number=60 & minor number=0

2) load module
insmod ./char_temp.ko

3) check if the module loaded correctly
lsmod

4) run user program
./user_prog

5) finally remove module
rmmod char_temp

#if printk() statements do not get printed on the terminal, run demsg to check the kernel messages
