//required header files
#include<linux/kernel.h>    //for printk()
#include<linux/init.h>      //for init and exit functions
#include<linux/module.h>    //for MODULE_ functions

//module initialization function
static int __init hello_init(void)         //static usage is optional
{
    printk(KERN_ALERT "Hello World!\n");                    //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    return 0;
}

//module de-initialization function
static void __exit hello_exit(void)        //static usage is optional
{
    printk(KERN_ALERT "Bye, Cruel World!\n");               //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
}

module_init(hello_init);                            //indicate to kernel that hello_init() is the module initialization function
module_exit(hello_exit);                            //indicate to kernel that hello_exit() is the module de-initialization function

//module attributes
MODULE_LICENSE("GPL");
MODULE_AUTHOR("UDAYAN PRABIR SINHA");
MODULE_DESCRIPTION("Hello World Module");
MODULE_VERSION("V1.1");
