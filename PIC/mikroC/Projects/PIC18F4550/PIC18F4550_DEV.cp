#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/PIC18F4550_DEV.c"
void main(void)
{
 TRISD=0xFE;
 while(1)
 {
 PORTD.B0=~PORTD.B0;
 Delay_ms(500);
 }
}
