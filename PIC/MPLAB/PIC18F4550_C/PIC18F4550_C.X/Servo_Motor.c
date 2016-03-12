#include"libraries/stdconfig.h"
#include"libraries/delay.h"

//variables required for the servo library
unsigned char iteration_count=0;            //must be intialized to 0
unsigned char no_of_servos=1;          //no of servos being used
#include"libraries/servo.h"

void interrupt_init(void);
void interrupt isr_h(void);
void interrupt low_priority isr_l(void);

void main()
{
    servo_init(no_of_servos);    //initialize servo control
    interrupt_init();            //initialize interrupts
    unsigned char i;
    while(1)
    {
        //move from 0deg to 180deg in 20deg steps
        for(i=0; i<181; i+=20)
        {
            servo_move(i, 1);
            Delay_ms(1000);
        }
    }
}

//interrupt initialize function
void interrupt_init(void)
{
    IPEN=1;             //enable interrupt priority
    GIEH=1;             //enable high priority interrupts
    GIEL=1;             //enable low priority interrupts
    TMR0IF=0;             //clear interrupt flag
    TMR0IE=1;             //enable timer 0 interrupt
    TMR0IP=0;             //low priority interrupt on timer 0
    TMR3IF=0;             //clear interrupt flag
    TMR3IE=1;             //enable timer 3 interrupt
    TMR3IP=1;             //high priority interrupt on timer 3
}
//high priority ISR function
void interrupt isr_h(void)
{
    timer3_isr();
}
//low priority ISR function
void interrupt low_priority isr_l(void)
{
    timer0_isr();
}