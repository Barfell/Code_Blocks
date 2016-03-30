#Run instructions (run as root)

1) load module
insmod ./Hello_World.ko

2) check if the module loaded correctly
lsmod

3) finally remove module
rmmod Hello_World

#if printk() statements do not get printed on the terminal, run demsg to check the kernel messages
