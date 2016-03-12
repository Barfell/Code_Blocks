#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/SPI.c"


void main(void)
{
 ADCON1=0x0F;


 TRISB&=0xFB;
  PORTB.B2 =1;

 SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV64, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);


  PORTB.B2 =0;
 SPI1_Write(0x37);
 SPI1_Write(0xFF);
  PORTB.B2 =1;
 Delay_ms(1);



 while(1);
}
