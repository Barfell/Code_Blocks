#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include"libraries/spi.h"

//required for the nRF24L01+ library
#define ss RB4         //slave select pin
#define ce RB3         //activate signal for nRF24L01+
#define new_data !RB2   //IRQ pin on nRF24L01+

#include"libraries/nrf24.h"

void interrupt_init(void);
void interrupt isr(void);
void main()
{
    TRISB&=0xE7;                            //ss & ce are output, RB2 is input
    ss=1;
    ce=1;
    interrupt_init();
    SPI_master_init(0x00, SLOW);          //initialize MSSP module for SPI communication
    nrf24_init();          //initialize nRF24L01+
    while(1)
    {
        nrf24_data_tx();             //send some data
        Delay_ms(1000);              //wait a second
        //write code to deal with received data
    }
}
//Interrupt initialize function
void interrupt_init(void)
{
    IPEN=1;       //enable priority of interrupts
    //enable interrupts
    GIEH=1;
    GIEL=1;
    INTEDG2=0;        //INT2 on falling edge
    INT2IE=1;     //enable INT2
    INT2IF=0;         //clear interrupt flag
}
//ISR function
void interrupt isr(void)
{
    nrf24_data_rx();       //get received data
}
