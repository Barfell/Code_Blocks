#line 1 "D:/Mikroelektronika/Projects/PIC18F4550/USB2Serial.c"
#line 10 "D:/Mikroelektronika/Projects/PIC18F4550/USB2Serial.c"
unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

char cnt, i;
char kk;
char test_data[]="Program using USB HID bootloader-Hello World from PIC!! ";

void interrupt(){
 USB_Interrupt_Proc();
}

void main(void)
{
 ADCON1 |= 0x0F;
 CMCON |= 7;

 HID_Enable(&readbuff,&writebuff);
 UART1_Init(9600);
 UART1_Write_Text("mikroC USB-2-Serial Converter TEST\n");

 while(1)
 {
 do
 {
 cnt=HID_Read();
 }
 while((!cnt));

 for(i=0; i<cnt; i++)
 {
 UART1_Write(readbuff[i]);

 }






 }
}
