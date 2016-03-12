/*
* Go Mikroelektronika\mikroC PRO for PIC\Examples\Other\USB HID Bootloader\Projects\PIC18F
* Open the USB HID Bootloader project and compile it
* Upload the .hex file using PICkit
* Now compile this file. Include the USBdsc.c file from Mikroelektronika\mikroC PRO from PIC\Tools\HID Terminal while compiling
* Now upload this .hex file using the USB HID Bootloader tool
* Test it out using HID Terminal
*/

unsigned char readbuff[64] absolute 0x500;   // Buffers should be in USB RAM, please consult datasheet
unsigned char writebuff[64] absolute 0x540;

char cnt;
char kk;
char test_data[]="Program using USB HID bootloader-Hello World from PIC!! ";

void interrupt(){
   USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
}

void main(void)
{
     ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
     CMCON  |= 7;                            // Disable comparators

     HID_Enable(&readbuff,&writebuff);       // Enable HID communication

     while(1)
     {
           while(!HID_Read());         //wait for getting input data from USB

           //write to USB write buffer
           for(cnt=0;cnt<64;cnt++)
           {
                writebuff[cnt]=test_data[cnt];
           }

           while(!HID_Write(&writebuff,64));      //send data over USB
     }
}