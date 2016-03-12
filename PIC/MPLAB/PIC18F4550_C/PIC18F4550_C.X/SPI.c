#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include"libraries/spi.h"

#define ss RB2         //slave select pin
#define ldac RB3       //DAC latch pin

void main()
{
    SPI_master_init(0x00, SLOW);            //initialize MSSP module for SPI communication
    TRISB&=0xF3;          //ss & ldac pin are output
    ss=1;
    ldac=1;
    while(1)
    {
        //send data for D/A conversion
        ss=0;
        SPI_master_write(0x37);
        SPI_master_write(0xFF);
        ss=1;
        Delay_ms(1);
        //latch data in DAC for processing
        ldac=0;
        Delay_ms(1);
        ldac=1;
        Delay_ms(1000);           //wait a second
        //write code to read data from SPI bus if needed
    }
}
