#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/I2C.c"
unsigned short write_stat=0;
unsigned char rtc_data[7];
char i, error;
char greet[]="mikroC I2C TEST\n";

void rtc_init(void);

void main(void)
{
 error=Soft_UART_Init(&PORTD, 0, 1, 9600, 0);
 for(i=0; i<17; i++)
 {
 Soft_UART_Write(greet[i]);
 }

 rtc_init();
 Delay_ms(1);

 while(1)
 {

 write_stat=I2C1_Start();

 write_stat=I2C1_Wr(0xD0);

 write_stat=I2C1_Wr(0x00);
 I2C1_Repeated_Start();

 write_stat=I2C1_Wr(0xD1);


 for(i=0; i<7; i++)
 {
 if(i<6)
 {
 rtc_data[i]=I2C1_Rd(1);
 }
 else
 {
 rtc_data[i]=I2C1_Rd(0);
 }
 }
 I2C1_Stop();


 for(i=0; i<7; i++)
 {
 Soft_UART_Write(rtc_data[i]);
 }

 Delay_ms(1000);
 }
}


void rtc_init(void)
{
 I2C1_Init(100000);
 write_stat=I2C1_Start();

 write_stat=I2C1_Wr(0xD0);

 write_stat=I2C1_Wr(0x00);

 write_stat=I2C1_Wr(0x00);

 write_stat=I2C1_Wr(0x59);

 write_stat=I2C1_Wr(0x51);

 write_stat=I2C1_Wr(0x06);

 write_stat=I2C1_Wr(0x10);

 write_stat=I2C1_Wr(0x05);

 write_stat=I2C1_Wr(0x14);

 write_stat=I2C1_Wr(0x13);
 I2C1_Stop();
}
