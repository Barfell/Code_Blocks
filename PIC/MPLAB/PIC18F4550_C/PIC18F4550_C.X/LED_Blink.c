#include"libraries/stdconfig.h"
#include"libraries/delay.h"

void main()
{
    TRISD=0xFE;                 //RD0 is output
    while(1)
    {
        //toggle RD0 every 1s
        RD0=1;
        Delay_ms(250);
        RD0=0;
        Delay_ms(250);
    }
}
