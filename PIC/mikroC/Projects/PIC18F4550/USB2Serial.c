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

char cnt, i;
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
     UART1_Init(9600);      //setup UART for 9600bps comm
     UART1_Write_Text("mikroC USB-2-Serial Converter TEST\n");
     
     while(1)
     {
           do
           {
                   cnt=HID_Read();          //wait for getting input data from USB
           }
           while((!cnt));
           
           for(i=0; i<cnt; i++)
           {
                   UART1_Write(readbuff[i]);            //send data through UART

           }
     }
}