#include<stdio.h>
#include<string.h>   //for string fucntions
#include<fcntl.h>    //for file control functions
#include<errno.h>    //for error codes
#include "../../includes/gpio_sysfs.h"       //GPIO library

int main(void)
{
    gpio_export(17);							//export GPIO to userspace
    gpio_direction(17, OUT);				//set GPIO as output
    while(1)
    {
        gpio_set(17, '1');						//set GPIO high
        sleep(1);										//wait a second
        gpio_set(17, '0');						//set GPIO low
        sleep(1);										//wait a second
    }
	return 0;
}

