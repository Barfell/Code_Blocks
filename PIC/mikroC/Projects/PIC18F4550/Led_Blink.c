void main(void)
{
     TRISD=0xFE;
     
     while(1)
     {
             PORTD.B0=~PORTD.B0;
             Delay_ms(500);
     }
}