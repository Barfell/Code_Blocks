                    void main(void)
{
     unsigned short i;
     TRISC=0xFB;       //RC2 is output
     PWM1_Init(10000);    //10kHz PWM
     PWM1_Start();              //start PWM
     while(1)
     {
             for(i=255; i>=0; i--)
             {
                      PWM1_Set_Duty(i);
                      Delay_ms(50);
             }
     }
}