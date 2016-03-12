#line 1 "D:/Mikroelektronika/Projects/PIC18F4550/USB_HID.c"
unsigned char readbuff[64] absolute 0x500;
unsigned char writebuff[64] absolute 0x540;

char cnt;
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

 while(1)
 {
 while(!HID_Read());


 for(cnt=0;cnt<64;cnt++)
 {
 writebuff[cnt]=test_data[cnt];
 }

 while(!HID_Write(&writebuff,64));
 }
}
