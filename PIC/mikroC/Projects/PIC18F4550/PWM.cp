#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/PWM.c"
void main(void)
{
 unsigned short i;
 TRISC=0xFB;
 PWM1_Init(10000);
 PWM1_Start();
 while(1)
 {
 for(i=0; i<=255; i++)
 {
 PWM1_Set_Duty(i);
 Delay_ms(50);
 }
 }
}
