#include"libraries/stdconfig.h"
#include"libraries/delay.h"

//timer values for servo angle control
union servo1
{
    unsigned char srv1[2];
    unsigned int srv1_16;
}servo_1;

void timer_init(void);
void interrupt_init(void);
void interrupt isr(void);
void interrupt low_priority isr_l(void);
void timer0_isr(void);
void timer3_isr(void);
void servo_move(unsigned char angle);

void main()
{
    timer_init();              //initialize timers
    TRISD=0xFE;           //RD0 is output
    interrupt_init();            //initialize interrupts
    unsigned char i;
    while(1)
    {
        //move from 0deg to 180deg in 10deg steps
        for(i=0; i<181; i+=10)
        {
            servo_move(i);
            Delay_ms(1000);
        }
    }
}
//servo motor control function
void servo_move(unsigned char angle)
{
    servo_1.srv1_16=60536-(27.77*angle);
    //start timer
    TMR3ON=1;
    TMR0ON=1;
}
//timer initialize function
void timer_init(void)
{
    //timer 0
    T08BIT=0;          //timer used in 16-bit mode
    T0CS=0;            //use as timer
    PSA=1;             //prescaler not used
    //initialize timer 0 registers
    TMR0H=0xFF;
    TMR0L=0xFF;
    TMR0ON=0;           //timer 0 is off for now
    //timer 3
    T3CON|=0x80;           //RD16=1; timer registers accessed together
    //1:8 prescaler
    T3CKPS0=1;
    T3CKPS1=1;
    TMR3CS=0;         //use as timer
    TMR3ON=0;        //timer 3 is off for now
    //initialize timer 3 registers
    TMR3H=0xCF;
    TMR3L=0x2C;
    //initialize servo angle values to 0deg
    servo_1.srv1_16=0xFFFF;
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
void interrupt isr(void)
{
    timer3_isr();
}
//low priority ISR function
void interrupt low_priority isr_l(void)
{
    timer0_isr();
}
//timer 0 ISR
void timer0_isr(void)
{
    static unsigned char state=0;
    TMR0IF=0;           //clear interrupt flag
    if(state==0)          //pulse is about to be given
    {
        TMR0H=servo_1.srv1[1];
        TMR0L=servo_1.srv1[0];
        RD0=1;
        TMR0ON=1;             //start timer again
        state=1;
    }
    else if(state==1)          //pulse is already given
    {
        RD0=0;
        TMR0ON=0;        //stop timer
        state=0;
    }
}
//timer 3 ISR
void timer3_isr(void)
{
    TMR3ON=0;           //turn off timer
    TMR3IF=0;           //clear interrupt flag
    //reload timer registers
    TMR3H=0xCF;
    TMR3L=0x2C;
    TMR0H=0xFF;
    TMR0L=0xFF;
    //turn on timers
    TMR3ON=1;
    TMR0ON=1;
}