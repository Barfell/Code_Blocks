#line 1 "D:/Mikroelektronika/mikroC PRO for PIC/Projects/PIC18F4550/EEPROM.c"
void main(void)
{
 char rom_data[7];


 UART1_Init(9600);
 UART1_Write_Text("mikroC EEPROM TEST\n");


 EEPROM_Write(0, '1');
 Delay_ms(20);

 EEPROM_Write(1, '2');
 Delay_ms(20);

 EEPROM_Write(2, '3');
 Delay_ms(20);


 IntToStr((int)EEPROM_Read(0), rom_data);
 UART1_Write_Text("EEPROM Data : ");
 UART1_Write_Text(rom_data);
 UART_Write('\n');
 Delay_ms(20);

 IntToStr((int)EEPROM_Read(1), rom_data);
 UART1_Write_Text("EEPROM Data : ");
 UART1_Write_Text(rom_data);
 UART_Write('\n');
 Delay_ms(20);

 IntToStr((int)EEPROM_Read(2), rom_data);
 UART1_Write_Text("EEPROM Data : ");
 UART1_Write_Text(rom_data);
 UART_Write('\n');
 Delay_ms(20);

 while(1);
}
