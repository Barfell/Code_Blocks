#include<stdio.h>
#include<fcntl.h>     //for file operations


int main(void)
{
	char data_wr[5]="ABCDE";         //data to be written
	char data_rd[1];				 //data to be read
	
	int fhandle=open("/dev/mem_chr", O_RDWR);        //open file handle with both read & write permissions
	
	write(fhandle, data_wr, 5, NULL);              //write to file
	read(fhandle, data_rd, 1, NULL);			   //read from file
	
	printf("Value: %c\n" , data_rd[0]);        //display value read from file
	
	close(fhandle);                                //close file handle
	return 0;
}
