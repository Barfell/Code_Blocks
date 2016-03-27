#Run instructions (run as root)

1) load modules
insmod ./Hello_World.ko

2) check if the modules loaded correctly
lsmod

3) finally remove modules
rmmod memory
rmmod Hello_World

#if printk() statements do not get printed on the terminal, run demsg to check the kernel messages
