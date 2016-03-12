//SPI selectable master clock speeds
#define SLOW 2
#define MED 1
#define FAST 0

unsigned char flush_buffer;              //used to collect garbage data; required for the SPI library

//SPI master initialize function
void SPI_master_init(unsigned char mode_select, unsigned char clk_speed)
{
    TRISB&=0xFD;        //enable CLK pin, enable SDI pin
    TRISC&=0x7F;        //enable SDO pin
    //configure MSSP in required SPI mode
    switch(mode_select)                 
    {
        case 0x00:
            CKP=0;
            CKE=1;
            break;

        case 0x01:
            CKP=0;
            CKE=0;
            break;

        case 0x10:
            CKP=1;
            CKE=1;
            break;

        case 0x11:
            CKP=1;
            CKE=0;
            break;
    }
    //select SPI bus speed
    switch(clk_speed)
    {
        case SLOW:         //Fosc/64
            SSPCON1|=SLOW;
            break;

        case MED:          //Fosc/16
            SSPCON1|=MED;
            break;

        case FAST:         //Fosc/4
            SSPCON1|=FAST;
            break;
    }
    SSPEN=1;      //enable SPI
}
//SPI master write function
void SPI_master_write(unsigned char y)
{
    SSPIF=0;
    WCOL=0;
    flush_buffer=SSPBUF;              //ensure that all previously received data in SSPBUF is read to avoid setting of collision bit
    SSPBUF=y;
    while(SSPIF==0);    //wait till transmission is complete
}
//SPI master read function
unsigned char SPI_master_read(void)
{
    SSPIF=0;           //clear interrupt flag
    WCOL=0;            //clear write collision
    flush_buffer=SSPBUF;      //get previously received garbage values
    SSPBUF=0x00;          //garbage value to be sent
    while(SSPIF==0);    //wait till reception is complete
    return SSPBUF;        //get received data
}