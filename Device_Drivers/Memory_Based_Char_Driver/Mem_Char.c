//required header files
#include<linux/kernel.h>    //for printk()
#include<linux/init.h>      //for init and exit functions
#include<linux/module.h>    //for MODULE_ functions
#include<linux/fs.h>        //for file_operations struct
#include <linux/slab.h> 	//for dynamic memory allocation
#include <asm/uaccess.h>    //for copy_from/to_user

#define MAJ_NO 60        //major number

//function prototypes
static int mem_char_open(struct inode *inode, struct file *filep);
static int mem_char_close(struct inode *inode, struct file *filep);
ssize_t mem_char_read(struct file *filep, char *buf, size_t count, loff_t *f_pos);
ssize_t mem_char_write(struct file *filep, char *buf, size_t count, loff_t *f_pos);
static void __exit mem_char_exit(void);
static int __init mem_char_init(void);

char *mem_buff;				//buffer to store data

//associate standard file open, close, read & write operations to the ones implemented in the driver
struct file_operations mem_char_fops= 
{
  read: mem_char_read,
  write: mem_char_write,
  open: mem_char_open,
  release: mem_char_close
};

/*************Initialization & De-initialization*************/
//module initialization function
static int __init mem_char_init(void)         //static usage is optional
{
	//Registering device
  	if((register_chrdev(MAJ_NO, "mem_chr", &mem_char_fops))<0)        //failed to register
  	{
    	printk(KERN_ALERT "Char Driver Registration Failed!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    	return -1;
  	}
  	else                                                 //successfully registered
  	{
    	printk(KERN_ALERT "Char Driver Initialized!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    }
    
    //Allocating memory for the buffer
  	mem_buff=kmalloc(1, GFP_KERNEL); 
  	if (!mem_buff)        //memory allocation failed
  	{ 
  		unregister_chrdev(MAJ_NO, "mem_chr"); 
  		printk(KERN_ALERT "Memory Allocation Failed!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
  		printk(KERN_ALERT "Char Driver De-initialized!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
    	return -1; 
  	} 
  	memset(mem_buff, 0, 1);         //clear buffer

  	return 0;
}

//module de-initialization function
static void __exit mem_char_exit(void)        //static usage is optional
{
	//Freeing buffer memory
  	if(mem_buff) 
  	{
    	kfree(mem_buff);
  	}
	unregister_chrdev(MAJ_NO, "mem_chr");          //unregister device with the mentioned major number & name
    printk(KERN_ALERT "Char Driver De-initialized!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
}

module_init(mem_char_init);                            //indicate to kernel that hello_init() is the module initialization function
module_exit(mem_char_exit);                            //indicate to kernel that hello_exit() is the module de-initialization function

/***********************File Operations**********************/
//file open function
static int mem_char_open(struct inode *inode, struct file *filep)
{
	printk(KERN_ALERT "Char Driver Device Opened!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 0;
}

//file close function
static int mem_char_close(struct inode *inode, struct file *filep)
{
	printk(KERN_ALERT "Char Driver Device Closed!\n");  //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	return 0;
}

//file read function
ssize_t mem_char_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "Char Driver Device Read!\n");    //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	copy_to_user(buf, mem_buff, 1);                  //transfer data to user space
	return 1;
}

//file write function
ssize_t mem_char_write(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
	printk(KERN_ALERT "Char Driver Device Written!\n"); //printk() is equivalent of printf() in kernel space, print at priority KERN_ALERT
	copy_from_user(mem_buff, buf+count-1, 1);		   //transfer data to kernel space
	//only one character is stored here
	//if more than one character is sent, the last one is stored
	return 1;
}

/**********************Module Attributes*********************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("UDAYAN PRABIR SINHA");
MODULE_DESCRIPTION("Memory-Based Char Driver Module");
MODULE_VERSION("V1.1");

