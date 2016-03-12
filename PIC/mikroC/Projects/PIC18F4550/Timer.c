void main(void)
{
     TRISD=0xFE;        //RD0 is output
     T0CON.B6=1;          //timer configured in 8-bit mode
     T0CON.B5=0;            //clock source is internal clock
     T0CON.B7=1;          //enable timer 0
     
     while(1)
     {
             INTCON.B2=0;                //clear overflow
             TMR0L=0xE0;                 //load timer register
             PORTD.B0=~PORTD.B0;
             while(TMR0IF==0);           //check for overflow
    }
}