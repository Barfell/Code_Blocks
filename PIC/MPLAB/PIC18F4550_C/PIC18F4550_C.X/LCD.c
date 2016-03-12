#include"libraries/stdconfig.h"
#include"libraries/delay.h"
#include<stdio.h>

//lcd pins; required for the library
#define lcd_data PORTD
#define rs RC2
#define en RC1

#include"libraries/lcd_16x2.h"

void main()
{
    TRISC=0xF9;                  //lcd control pins
    TRISD=0x00;                  //lcd data bus
    lcd_init();                  //initialize LCD

    //display stuff on LCD
    printf("    MPLAB-X");
    lcd_new_msg_second_line();
    printf("    PIC MCU");
    while(1);
}
