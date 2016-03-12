//eeprom initialize function
void eeprom_init(void)
{
    //access eeprom
    EEPGD=0;
    CFGS=0;
}
//eeprom write function
void eeprom_wr(unsigned char address, unsigned char data)
{
    EEADR=address;                //address to write to
    EEDATA=data;               //data to be written
    WREN=1;                 //allow write cycles
    //give write sequence
    EECON2=0x55;
    EECON2=0xAA;
    WR=1;              //enable write operation
    while(WR==1);      //wait till write operation is complete
}
//eeprom read function
unsigned char eeprom_rd(unsigned char address)
{
    EEADR=address;        //location from which data is to be read
    RD=1;           //read data
    return EEDATA;
}