#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/Timer.c"
void main(void)
{
 TRISD=0xFE;
 T0CON.B6=1;
 T0CON.B5=0;
 T0CON.B7=1;


 while(1)
 {
 INTCON.B2=0;
 TMR0L=0xE0;
 PORTD.B0=~PORTD.B0;
 while(TMR0IF==0);
 }
}
