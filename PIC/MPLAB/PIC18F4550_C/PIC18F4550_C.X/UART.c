#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include<stdio.h>
#include"libraries/uart.h"

void interrupt isr(void);
void interrupt_init(void);

void main()
{
    serial_init();            //initialize UART
    interrupt_init();         //initialize interrupts for UART RX
    while(1)
    {
        serial_transmit('5');            //tranmit data via UART
        Delay_ms(1000);                       //wait a sec
        //add code to take action based on data from UART RX
    }
}
//interrupt initialize function
void interrupt_init(void)
{
    IPEN=1;             //enable interrupt priority
    GIEH=1;             //enable high priority interrupts
    GIEL=1;             //enable low priority interrupts
    RCIE=1;             //enable UART RX interrupt
    RCIF=0;             //clear interrupt flag
}
//ISR function
void interrupt isr(void)
{
    serial_receive();
}
