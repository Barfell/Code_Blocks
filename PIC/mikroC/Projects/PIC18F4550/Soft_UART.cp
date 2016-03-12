#line 1 "D:/Mikroelektronika/Projects/PIC18F4550/Soft_UART.c"
void main(void)
{
 char text[]="mikroC UART TEST\n";
 char i, error;

 error=Soft_UART_Init(&PORTD, 0, 1, 9600, 0);

 while(1)
 {
 for(i=0; i<18; i++)
 {
 Soft_UART_Write(text[i]);
 }
 Delay_ms(1000);
 }
}
