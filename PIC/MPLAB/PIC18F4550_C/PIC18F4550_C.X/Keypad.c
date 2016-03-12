#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include<stdio.h>
#include"libraries/uart.h"

//rows
#define r1 RA4
#define r2 RA5
#define r3 RE0
#define r4 RE1
//columns
#define c1 RA0
#define c2 RA1
#define c3 RA2
#define c4 RA3

#include"libraries/keypad_4x4.h"

void interrupt isr(void);
void interrupt_init(void);

unsigned char key;
void main()
{
    //rows are output & columns are input
    ADCON1|=0x0F;
    TRISA=0x0F;
    TRISE&=0xFC;

    serial_init();            //initialize UART
    interrupt_init();         //initialize interrupts for UART RX
    while(1)
    {
        key=keyscan();                //scan & get key pressed
        if(key!=0)
        {
            printf("Key: %c\n", key);
            key=0;
            Delay_ms(200);
        }
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
