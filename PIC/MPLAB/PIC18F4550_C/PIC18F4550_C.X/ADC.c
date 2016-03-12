#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include"libraries/adc.h"
#include<stdio.h>
#include"libraries/uart.h"

void interrupt isr(void);
void interrupt_init(void);

unsigned int adc_output=0;

void main()
{
    serial_init();            //initialize UART
    interrupt_init();         //initialize interrupts for UART RX
    adc_init();               //initlialize ADC
    while(1);
    {
        adc_output=adc_acquire(CHANNEL_0);         //get analog value from AN0
        //send value via UART
        printf("ADC: %d", adc_output);
        Delay_ms(1000);          //wait for a second
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
