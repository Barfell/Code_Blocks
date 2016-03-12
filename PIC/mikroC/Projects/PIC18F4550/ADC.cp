#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/ADC.c"
void main()
{
 char adc_data[7];

 TRISA|=0xFF;
 TRISC|=0xC0;
 UART1_Init(9600);
 ADC_Init();
 UART1_Write_Text("mikroC ADC TEST\n");

 while(1)
 {
 IntToStr((int)ADC_Get_Sample(0), adc_data);


 UART1_Write_Text("AN0 : ");
 UART1_Write_Text(adc_data);
 UART_Write('\n');

 Delay_ms(1000);
 }
}
