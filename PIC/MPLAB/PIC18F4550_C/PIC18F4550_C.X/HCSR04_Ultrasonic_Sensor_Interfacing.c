#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include<stdio.h>
#include"libraries/uart.h"

#define echo RB1
#define trigger RB0

void interrupt isr(void);
void interrupt_init(void);
void timer0_init(void);
void ultrasonic_sense(void);

void main()
{
    TRISB=0xFE;         //initialize echo and trigger pins
    serial_init();            //initialize UART
    timer0_init();           //initialize timer
    interrupt_init();         //initialize interrupts for UART RX
    while(1)
    {
        ultrasonic_sense();                //get distance measurement
        Delay_ms(1000);                       //wait a sec
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
//timer0 initialize function
void timer0_init(void)
{
    T0CON=0x11;            //16-bit timer, 1:4 prescaler
    TMR0H=0;
    TMR0L=0;
    TMR0IF=0;        //clear interrupt flag
}
//ultrasonic sensor DAQ function
void ultrasonic_sense(void)
{
    static unsigned int dist;
    //give trigger signal
    trigger=1;
    Delay_us(10);
    trigger=0;

    while(echo==0);            //wait for echo
    TMR0ON=1;               //start timer
    while(echo==1);               //wait for echo to finish
    TMR0ON=0;               //stop timer
    //calc distance
    dist=((TMR0H<<8) | TMR0L);
    dist=(dist-(0.1*dist))/58;
    if(dist>=2 && dist<=400)        //check whether the result is valid or not
    {
        printf("Distance: %d cm\n", dist);
    }
    else
    {
        printf("Out of range");
    }
    //clear timer registers & interrupt flag
    TMR0H=0;
    TMR0L=0;
    TMR0IF=0;
}
