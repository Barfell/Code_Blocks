//delay milliseconds function
void Delay_ms(unsigned long x)
{
    unsigned long i;
    for(i=0; i<x; i++)
    {
        __delay_ms(1);
    }
}

//delay microseconds function
void Delay_us(unsigned long x)
{
    unsigned long i;
    for(i=0; i<x; i++)
    {
        __delay_us(1);
    }
}
