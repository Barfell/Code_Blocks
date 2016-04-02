#define ERR -1
#define LOW '0'
#define HIGH '1'
#define IN 50
#define OUT 51

//GPIO export function
char gpio_export(int gpio)
{
    char buff[5], result;
    int fdes=open("/sys/class/gpio/export", O_WRONLY);        //open file to export required gpio pin to userspace
    sprintf(buff, "%d", gpio); 								  //convert given number to string
    result=write(fdes, buff, strlen(buff), NULL);					  //write to file
    close(fdes);											  //close file
	return result;
}

//GPIO direction function
char gpio_direction(int gpio, char direction)
{
	char buff[35], result;
	sprintf(buff, "/sys/class/gpio/gpio%d/direction", gpio); 								  //convert given number to string
	int fdes=open(buff, O_WRONLY);        					  //open file to set gpio pin mode
	if(direction==IN)
	{
		result=write(fdes, "in", 2, NULL);				  //write to file
	}
	else if(direction==OUT)
	{
		result=write(fdes, "out", 3, NULL);				  //write to file
	}
    close(fdes);											  //close file
	return result;
}

//GPIO output set function
char gpio_set(int gpio, char gpio_val)
{
	char buff[31], result;
	sprintf(buff, "/sys/class/gpio/gpio%d/value", gpio); 								  //convert given number to string
	int fdes=open(buff, O_WRONLY);        					  //open file to set gpio pin value
	result=write(fdes, &gpio_val, 1, NULL);				  //write to file
    close(fdes);											  //close file
	return result;
}

//GPIO input read function
char gpio_read(int gpio, char* gpio_val)
{
	char buff[31], result;
	sprintf(buff, "/sys/class/gpio/gpio%d/value", gpio); 								  //convert given number to string
	int fdes=open(buff, O_RDONLY);        					  //open file to read gpio pin value
	result=read(fdes, gpio_val, 1, NULL);			   	  //read from file
    close(fdes);											  //close file
	return result;
}
