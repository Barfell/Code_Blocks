#include"libraries/stdconfig.h"
#include"libraries/eeprom.h"

unsigned char y;
void main()
{
    eeprom_init();            //initialize eeprom

    //write data to eeprom
    eeprom_wr(0, '1');
    eeprom_wr(1, '2');
    eeprom_wr(2, '3');
    eeprom_wr(3, '4');
    
    y=eeprom_rd(0);             //read data from eeprom
    while(1);
}
