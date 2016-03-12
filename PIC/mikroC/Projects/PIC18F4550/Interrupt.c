void t0_isr(void);            //timer 0 ISR

void main(void)
{
     TRISD=0xFE;        //RD0 is output
     T0CON.B6=1;          //timer configured in 8-bit mode
     T0CON.B5=0;            //clock source is internal clock
     TMR0L=0xE0;            //load timer register
     T0CON.B7=1;          //enable timer 0
     RCON.B7=1;           //enable interrupt priority
     INTCON2.B2=1;        //timer 0 interrupt is of high priority
     INTCON=0xE0;         //enable high and low priority interrupts, enable timer 0 interrupt, clear timer 0 interrupt flag
     
     while(1);
}

//ISR high priority
void interrupt(void)
{
     t0_isr();     //call timer 0 ISR
}

//timer 0 ISR
void t0_isr(void)
{
     T0CON.B7=0;        //turn off timer
     INTCON.B1=0;           //clear interrupt flag
     PORTD.B0=~PORTD.B0;          //toggle RD0
     TMR0L=0xE0;            //load timer register
     T0CON.B7=1;        //turn  on timer
}