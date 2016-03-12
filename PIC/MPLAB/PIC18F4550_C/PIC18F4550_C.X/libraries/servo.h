//timer values for servo angle control
union servo1
{
    unsigned char srv1[2];
    unsigned int srv1_16;
}servo_1;

union servo2
{
    unsigned char srv2[2];
    unsigned int srv2_16;
}servo_2;

union servo3
{
    unsigned char srv3[2];
    unsigned int srv3_16;
}servo_3;

union servo4
{
    unsigned char srv4[2];
    unsigned int srv4_16;
}servo_4;

union servo5
{
    unsigned char srv5[2];
    unsigned int srv5_16;
}servo_5;

union servo6
{
    unsigned char srv6[2];
    unsigned int srv6_16;
}servo_6;

union servo7
{
    unsigned char srv7[2];
    unsigned int srv7_16;
}servo_7;

union servo8
{
    unsigned char srv8[2];
    unsigned int srv8_16;
}servo_8;

//timer initialize function
void timer_init(void)
{
    //timer 0
    T08BIT=0;          //timer used in 16-bit mode
    T0CS=0;            //use as timer
    PSA=1;             //prescaler not used
    //initialize timer 0 registers
    TMR0H=0xFF;
    TMR0L=0xFF;
    TMR0ON=0;           //timer 0 is off for now
    //timer 3
    T3CON|=0x80;           //RD16=1; timer registers accessed together
    //1:8 prescaler
    T3CKPS0=1;
    T3CKPS1=1;
    TMR3CS=0;         //use as timer
    TMR3ON=0;        //timer 3 is off for now
    //initialize timer 3 registers
    TMR3H=0xCF;
    TMR3L=0x2C;
    //initialize servo angle values to 0deg
    servo_1.srv1_16=0xFFFF;
    servo_2.srv2_16=0xFFFF;
    servo_3.srv3_16=0xFFFF;
    servo_4.srv4_16=0xFFFF;
    servo_5.srv5_16=0xFFFF;
    servo_6.srv6_16=0xFFFF;
    servo_7.srv7_16=0xFFFF;
    servo_8.srv8_16=0xFFFF;
}
//servo motor control initialize function
void servo_init(unsigned char number_of_servos)
{
    timer_init();         //initialize timers
    //PORTD used for servo motor control
    switch(number_of_servos)
    {
        case 1:
            TRISD=0xFE;        //1 servo motor is used
            break;

        case 2:
            TRISD=0xFC;        //2 servos motors are used
            break;

        case 3:
            TRISD=0xF8;        //3 servos motors are used
            break;

        case 4:
            TRISD=0xF0;        //4 servos motors are used
            break;

        case 5:
            TRISD=0xE0;        //5 servo motor is used
            break;

        case 6:
            TRISD=0xC0;        //6 servos motors are used
            break;

        case 7:
            TRISD=0x80;        //7 servos motors are used
            break;

        case 8:
            TRISD=0x00;        //8 servos motors are used
            break;
    }
}
//servo motor control function
void servo_move(unsigned char angle, unsigned char servo_number)
{
    switch(servo_number)
    {
        case 1:
            servo_1.srv1_16=60536-(28*angle);
            break;

        case 2:
            servo_2.srv2_16=60536-(28*angle);
            break;

        case 3:
            servo_3.srv3_16=60536-(28*angle);
            break;

        case 4:
            servo_4.srv4_16=60536-(28*angle);
            break;

        case 5:
            servo_5.srv5_16=60536-(28*angle);
            break;

        case 6:
            servo_6.srv6_16=60536-(28*angle);
            break;

        case 7:
            servo_7.srv7_16=60536-(28*angle);
            break;

        case 8:
            servo_8.srv8_16=60536-(28*angle);
            break;
    }
    //start timer
    TMR3ON=1;
    TMR0ON=1;
}
//timer 0 ISR
void timer0_isr(void)
{
    TMR0ON=0;           //turn off timer
    TMR0IF=0;           //clear interrupt flag
    if(iteration_count<no_of_servos)              //signals need to be sent to servo motors
    {
        switch(iteration_count)
        {
            case 0:
                TMR0H=servo_1.srv1[1];
                TMR0L=servo_1.srv1[0];
                iteration_count++;
                RD0=1;
                break;

            case 1:
                RD0=0;
                TMR0H=servo_2.srv2[1];
                TMR0L=servo_2.srv2[0];
                iteration_count++;
                RD1=1;
                break;

            case 2:
                RD1=0;
                TMR0H=servo_3.srv3[1];
                TMR0L=servo_3.srv3[0];
                iteration_count++;
                RD2=1;
                break;

            case 3:
                RD2=0;
                TMR0H=servo_4.srv4[1];
                TMR0L=servo_4.srv4[0];
                iteration_count++;
                RD3=1;
                break;

            case 4:
                RD3=0;
                TMR0H=servo_5.srv5[1];
                TMR0L=servo_5.srv5[0];
                iteration_count++;
                RD4=1;
                break;

            case 5:
                RD4=0;
                TMR0H=servo_6.srv6[1];
                TMR0L=servo_6.srv6[0];
                iteration_count++;
                RD5=1;
                break;

            case 6:
                RD5=0;
                TMR0H=servo_7.srv7[1];
                TMR0L=servo_7.srv7[0];
                iteration_count++;
                RD6=1;
                break;

            case 7:
                RD6=0;
                TMR0H=servo_8.srv8[1];
                TMR0L=servo_8.srv8[0];
                iteration_count++;
                RD7=1;
                break;
        }
        TMR0ON=1;             //start timer again
    }
    else                                                     //all servos motors have been serviced
    {
        switch(no_of_servos)
        {
            case 1:
                RD0=0;
                break;

            case 2:
                RD1=0;
                break;

            case 3:
                RD2=0;
                break;

            case 4:
                RD3=0;
                break;

            case 5:
                RD4=0;
                break;

            case 6:
                RD5=0;
                break;

            case 7:
                RD6=0;
                break;

            case 8:
                RD7=0;
                break;
        }
    }
}
//timer 3 ISR
void timer3_isr(void)
{
    TMR3ON=0;           //turn off timer
    TMR3IF=0;           //clear interrupt flag
    //restart process
    iteration_count=0;       
    //reload timer registers
    TMR3H=0xCF;
    TMR3L=0x2C;
    TMR0H=0xFF;
    TMR0L=0xFF;
    //turn on timers
    TMR3ON=1;
    TMR0ON=1;
}