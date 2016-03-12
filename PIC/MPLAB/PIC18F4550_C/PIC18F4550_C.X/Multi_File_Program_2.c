#include <htc.h>

#define _XTAL_FREQ 20000000

//delay function
void delay(unsigned long x)
{
    unsigned long i;
    for(i=0; i<x; i++)
    {
        __delay_ms(1);
    }
}
