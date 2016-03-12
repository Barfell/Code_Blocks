#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/UART.c"
void main()
{
 char buffer[10];

 UART1_Init(9600);
 UART1_Write_Text("mikroC UART TEST\n");

 while(1)
 {
 if(UART1_Data_Ready())
 {
 UART1_Read_Text(buffer, "\n", 255);
 if(UART1_Tx_Idle())
 {
 UART1_Write_Text(buffer);
 }
 }
 }
}
