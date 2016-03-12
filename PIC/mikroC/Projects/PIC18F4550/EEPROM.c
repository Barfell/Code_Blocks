void main(void)
{
     char rom_data[7];
     
     //setup UART
     UART1_Init(9600);      //setup UART for 9600bps comm
     UART1_Write_Text("mikroC EEPROM TEST\n");
     
     //write to EEPROM
     EEPROM_Write(0, '1');    //write data
     Delay_ms(20);            //needed to ensure correct write/read
     
     EEPROM_Write(1, '2');    //write data
     Delay_ms(20);            //needed to ensure correct write/read
     
     EEPROM_Write(2, '3');    //write data
     Delay_ms(20);            //needed to ensure correct write/read
     
     //Read from EEPROM
     IntToStr((int)EEPROM_Read(0), rom_data);      //read data
     UART1_Write_Text("EEPROM Data : ");
     UART1_Write_Text(rom_data);
     UART_Write('\n');
     Delay_ms(20);            //needed to ensure correct write/read
     
     IntToStr((int)EEPROM_Read(1), rom_data);      //read data
     UART1_Write_Text("EEPROM Data : ");
     UART1_Write_Text(rom_data);
     UART_Write('\n');
     Delay_ms(20);            //needed to ensure correct write/read
     
     IntToStr((int)EEPROM_Read(2), rom_data);      //read data
     UART1_Write_Text("EEPROM Data : ");
     UART1_Write_Text(rom_data);
     UART_Write('\n');
     Delay_ms(20);            //needed to ensure correct write/read
     
     while(1);
}