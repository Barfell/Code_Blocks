#define ss PORTB.B2

void main(void)
{
     ADCON1=0x0F;              //all pins are digital IO
     
     //ss pin is output
     TRISB&=0xFB;
     ss=1;

     SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV64, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);   //initialize SPI in 00 mode
     
     //send data for D/A conversion
     ss=0;
     SPI1_Write(0x37);
     SPI1_Write(0xFF);
     ss=1;
     Delay_ms(1);

     //write code to read data from SPI bus if needed
     
     while(1);
}