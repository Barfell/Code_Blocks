#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/Interrupt.c"
void t0_isr(void);

void main(void)
{
 TRISD=0xFE;
 T0CON.B6=1;
 T0CON.B5=0;
 TMR0L=0xE0;
 T0CON.B7=1;
 RCON.B7=1;
 INTCON2.B2=1;
 INTCON=0xE0;

 while(1);
}


void interrupt(void)
{
 t0_isr();
}


void t0_isr(void)
{
 T0CON.B7=0;
 INTCON.B1=0;
 PORTD.B0=~PORTD.B0;
 TMR0L=0xE0;
 T0CON.B7=1;
}
