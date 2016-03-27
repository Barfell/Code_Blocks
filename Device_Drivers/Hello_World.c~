#include<linux/init.h>
#include<linux/module.h>

//module attributes
MODULE_LICENSE("GPL v3");
MODULE_AUTHOR("UDAYAN PRABIR SINHA");
MODULE_DESCRIPTION("Hello World Module");

//module initialization function
static int hello_init(void)
{
    printk(KERN_ALERT "Hello World!\n");                    //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    return 0;
}

//module de-initialization function
static void hello_exit(void)
{
    printk(KERN_ALERT "Bye, Cruel World!\n");               //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
}

module_init(hello_init);                            //indicate to kernel that hello_init() is the module initialization function
module_exit(hello_exit);                            //indicate to kernel that hello_exit() is the module de-initialization function
