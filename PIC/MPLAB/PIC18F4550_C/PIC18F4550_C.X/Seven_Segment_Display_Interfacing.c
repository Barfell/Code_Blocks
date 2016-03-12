#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include"libraries/seven_seg.h"

void main()
{
    unsigned char i;
    TRISD=0x00;     //PORTD is used to control seven segment display
    while(1)
    {
        for(i=0; i<10; i++)
        {
            PORTD=seven_seg_com_cath(i, DECIMAL_ON);          //send value to seven segment display
            Delay_ms(1000);                                   //wait a second
        }
    }
}
