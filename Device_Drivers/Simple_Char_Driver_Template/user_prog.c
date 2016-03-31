#include<stdio.h>
#include<fcntl.h>     //for file operations


int main(void)
{
	char buffer[1]={0};
	int fhandle=open("/dev/char_tmp", O_RDWR);        //open file handle with both read & write permissions
	
	write(fhandle, buffer, 1, NULL);               //write to file
	read(fhandle, buffer, 1, NULL);				  //read from file
	
	printf("Value: %d\n" , buffer[0]);        //display value of file
	
	close(fhandle);                                //close file handle
	return 0;
}
