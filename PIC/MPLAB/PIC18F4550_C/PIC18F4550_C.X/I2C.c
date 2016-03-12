#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include"libraries/i2c.h"

void main()
{
    i2c_master_init();            //initialize I2C
    
    //send data to DAC
    i2c_start();                      //generate start condition
    i2c_write_stat=i2c_transmit(0xC0);         //DAC address=1100000
    i2c_write_stat=i2c_transmit(0x07);         //fast write command, normal power mode, DAC value=0x0FF
    i2c_write_stat=i2c_transmit(0xFF);
    i2c_stop();                       //generate stop condition
    //read data from DAC if needed
  
    while(1);
}