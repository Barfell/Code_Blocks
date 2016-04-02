#include<stdio.h>
#include<string.h>   //for string fucntions
#include<fcntl.h>    //for file control functions
#include<errno.h>    //for error codes
#include "../../includes/gpio_sysfs.h"       //GPIO library

int main(void)
{
	char state;
    gpio_export(17);						//export GPIO to userspace
    gpio_direction(17, IN);				//set GPIO as input
    gpio_read(17, &state);				//read value at GPIO
    printf("GPIO Pin State: %c\n", state);			//display value at GPIO
	return 0;
}

