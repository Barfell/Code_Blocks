//ADC channels
#define CHANNEL_0 0x00
#define CHANNEL_1 0x04
#define CHANNEL_2 0x08
#define CHANNEL_3 0x0C
#define CHANNEL_4 0x10
#define CHANNEL_5 0x14
#define CHANNEL_6 0x18
#define CHANNEL_7 0x1C
#define CHANNEL_8 0x20
#define CHANNEL_9 0x24
#define CHANNEL_10 0x28
#define CHANNEL_11 0x2C
#define CHANNEL_12 0x30

//ADC initialize function
void adc_init(void)
{
    TRISA=0xFF;                   //RA0 is input
    ADCS1=1;                      //clock=F/32
    ACQT0=1;                      //acquisition time=clock*2
    ADFM=1;                       //right justified
    ADIF=0;                       //clear A/D complete interrupt flag
    ADON=1;                       //enable ADC module
}
//ADC DAQ function
unsigned int adc_acquire(unsigned char channel)
{
    //set to desired channel for analog DAQ
    ADCON0&=0x03;
    ADCON0|=channel;
    //perform A/D conversion now
    GO=1;                      //start A/D conversion
    while(ADIF==0);            //check to see if A/D conversion is complete
    ADIF=0;                    //clear interrupt flag
    return ADRES;                //get ADC output
}
