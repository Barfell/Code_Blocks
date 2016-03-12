void main()
{
     char adc_data[7];           //ADC output
     
     TRISA|=0xFF;     //ADC input on AN0
     TRISC|=0xC0;     //setup IO pins for UART
     UART1_Init(9600);      //setup UART for 9600bps comm
     ADC_Init();           //start ADC
     UART1_Write_Text("mikroC ADC TEST\n");

     while(1)
     {
             IntToStr((int)ADC_Get_Sample(0), adc_data);      //get ADC data
             
             //send data over UART
             UART1_Write_Text("AN0 : ");
             UART1_Write_Text(adc_data);
             UART_Write('\n');
             
             Delay_ms(1000);        //wait a bit
     }
}