#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include<stdio.h>
#include"libraries/uart.h"
#include"libraries/i2c.h"

void rtc_init(void);

unsigned char rtc_data[7]=0;               //data received from I2C
void main()
{
    serial_init();                //initialize UART
    i2c_master_init();            //initialize I2C
    rtc_init();                   //initialize RTC
    while(1)
    {
        i2c_start();                      //generate start condition
        //address the RTC, write mode
        i2c_write_stat=i2c_transmit(0xD0);         //RTC address=1101000
        //address of the RTC register to get the data from
        i2c_write_stat=i2c_transmit(0x00);         //RTC seconds register
        i2c_repeated_start();                      //generate repeated start condition
        //address RTC to get data from it, read mode
        i2c_write_stat=i2c_transmit(0xD1);         //RTC address=1101000
        //read data from RTC; we have to read 7 bytes of data
        for(unsigned char i=0; i<7; i++)
        {
            rtc_data[i]=i2c_receive();
            if(i!=6)
            {
                i2c_ack('Y');               //tell slave to keep sending data
            }
            else
            {
                i2c_ack('N');          //tell slave to stop sending data
            }
        }
        i2c_stop();                 //generate stop condition
        //send time info via UART
        for(unsigned char i=0; i<7; i++)
        {
            serial_transmit(rtc_data[i]);
        }
        Delay_ms(1000);
    }
}
//RTC initialize function
void rtc_init(void)
{
    i2c_start();                   //generate start condition
    //address the RTC, write mode
    i2c_write_stat=i2c_transmit(0xD0);         //RTC address=1101000
    //address of the RTC register to be written to
    i2c_write_stat=i2c_transmit(0x00);         //RTC seconds register
    //RTC oscillator is disabled by default; enable it & also set seconds value
    i2c_write_stat=i2c_transmit(0x00);        //enable oscillator & seconds value
    //set minutes value
    i2c_write_stat=i2c_transmit(0x59);         //minutes value
    //set hours value
    i2c_write_stat=i2c_transmit(0x51);            //12-hour mode & hours value
    //set day of the week
    i2c_write_stat=i2c_transmit(0x06);         //weekday
    //set date
    i2c_write_stat=i2c_transmit(0x10);        //date
    //set month
    i2c_write_stat=i2c_transmit(0x05);         //month
    //set year
    i2c_write_stat=i2c_transmit(0x14);        //year
    //enable square wave output if required
    i2c_write_stat=i2c_transmit(0x13);           //enable 32.768 kHz square wave
    i2c_stop();                     //generate stop condition
}