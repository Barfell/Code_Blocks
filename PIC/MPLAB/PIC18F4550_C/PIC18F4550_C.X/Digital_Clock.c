
// PIC18F4550 Configuration Bit Settings

#include <htc.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = OFF         // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

#define _XTAL_FREQ 20000000
//lcd pins
#define lcd_data PORTD
#define rs RC2
#define en RC1

#include<plib.h>

void lcd_init(void);
void lcd_cmd_transmit(unsigned char m);
void lcd_data_transmit(unsigned char p);
void lcd_new_msg_first_line(void);
void lcd_new_msg_second_line(void);
void delay(unsigned long x);
void rtc_init(void);
void display_rtc_data(void);
unsigned char write_stat=-1;          //status of I2C write
unsigned char rtc_data[7]=0;               //data received from I2C
unsigned char flush_data;              //garbage data from I2C
void main()
{
    TRISC=0xF9;                  //lcd control pins
    TRISD=0x00;                  //lcd data bus
    lcd_init();                //initialize LCD
    rtc_init();               //initialize RTC
    while(1)
    {
        StartI2C();                      //generate start condition
        //address the RTC, write mode
        write_stat=WriteI2C(0xD0);         //RTC address=1101000
        //address of the RTC register to get the data from
        write_stat=WriteI2C(0x00);         //RTC seconds register
        RestartI2C();                      //generate repeated start condition
        //address RTC to get data from it, read mode
        write_stat=WriteI2C(0xD1);         //RTC address=1101000
        //read data from RTC; we have to read 7 bytes of data
        for(unsigned char i=0; i<7; i++)
        {
            rtc_data[i]=ReadI2C();
            if(i!=6)
            {
                AckI2C();               //tell slave to keep sending data
            }
            else
            {
                NotAckI2C();          //tell slave to stop sending data
            }
        }
        StopI2C();                 //finish comm
        //display time info
        display_rtc_data();
    }
}
//LCD initialize function
void lcd_init(void)
{
    en=0;
    lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
    lcd_cmd_transmit(0x0C);                 //display on cursor off
    lcd_cmd_transmit(0x01);                 //clear display
    lcd_cmd_transmit(0x80);                //get to 1st line
    lcd_cmd_transmit(0x06);                //shift cursor right by 1 position
}
//LCD command transmit function
void lcd_cmd_transmit(unsigned char m)
{
    rs=0;             //command register selected
    lcd_data=m;
    //strobe en pin to latch data into the lcd
    en=1;
    delay(1);
    en=0;
}
//LCD data transmit function
void lcd_data_transmit(unsigned char p)
{
    rs=1;                //data register selected
    lcd_data=p;
    //strobe en pin to latch data into the lcd
    en=1;
    delay(1);
    en=0;
}
//Command function before sending message to 1st line
void lcd_new_msg_first_line(void)
{
    lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
    lcd_cmd_transmit(0x80);                //get to 1st line
    lcd_cmd_transmit(0x06);                //shift cursor right by 1 position
}
//Command function to continue sending message to 2nd line
void lcd_new_msg_second_line(void)
{
    lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
    lcd_cmd_transmit(0xC0);                //get to 2nd line
    lcd_cmd_transmit(0x06);                 //shift cursor right by 1 position
}
//delay function
void delay(unsigned long x)
{
	unsigned long i;
	for(i=0; i<x; i++)
	{
		__delay_ms(1);
	}
}
//RTC initialize function
void rtc_init(void)
{
    TRISB|=0x03;              //initialize SDA & SCL pins as input initially
    OpenI2C(MASTER, SLEW_OFF);           //master mode, slew rate control not needed for 100kbps
    SSPADD=39;            //100 kbps approx.
    IdleI2C();                             //wait till bus is idle
    StartI2C();                   //generate start condition
    //address the RTC, write mode
    write_stat=WriteI2C(0xD0);         //RTC address=1101000
    //address of the RTC register to be written to
    write_stat=WriteI2C(0x00);         //RTC seconds register
    //RTC oscillator is disabled by default; enable it & also set seconds value
    write_stat=WriteI2C(0x00);        //enable oscillator & seconds value
    //set minutes value
    write_stat=WriteI2C(0x59);         //minutes value
    //set hours value
    write_stat=WriteI2C(0x51);            //12-hour mode & hours value
    //set day of the week
    write_stat=WriteI2C(0x06);         //weekday
    //set date
    write_stat=WriteI2C(0x10);        //date
    //set month
    write_stat=WriteI2C(0x05);         //month
    //set year
    write_stat=WriteI2C(0x14);        //year
    //enable square wave output if required
    write_stat=WriteI2C(0x13);           //enable 32.768 kHz square wave
    StopI2C();                     //finish RTC initial setup
}
//RTC data display function
void display_rtc_data(void)
{
    unsigned char seconds[2], minutes[2], hours[2], date[2], year[2], week_day[3], month[3];
    unsigned char am_pm_indicator;
    //get seconds data in a nice format
    seconds[1]=rtc_data[0] & 0x0F;            //lower nibble
    seconds[1]=seconds[1] | 0x30;            //get it in ASCII
    seconds[0]=rtc_data[0] & 0xF0;            //upper nibble
    seconds[0]=seconds[0] & 0x70;
    seconds[0]=seconds[0]>>4;
    seconds[0]=seconds[0] | 0x30;            //get it in ASCII
    //get minutes data in a nice format
    minutes[1]=rtc_data[1] & 0x0F;            //lower nibble
    minutes[1]=minutes[1] | 0x30;            //get it in ASCII
    minutes[0]=rtc_data[1] & 0xF0;            //upper nibble
    minutes[0]=minutes[0]>>4;
    minutes[0]=minutes[0] | 0x30;            //get it in ASCII
    //get hours data in a nice format
    hours[1]=rtc_data[2] & 0x0F;            //lower nibble
    hours[1]=hours[1] | 0x30;            //get it in ASCII
    hours[0]=rtc_data[2] & 0x10;            //upper nibble
    am_pm_indicator=rtc_data[2] & 0x20;        //AM-PM info
    am_pm_indicator=am_pm_indicator>>5;
    hours[0]=hours[0]>>4;
    hours[0]=hours[0] | 0x30;            //get it in ASCII
    //get weekday data in a nice format
    /*
     * 1=Sunday
     * 2=Monday
     * 3=Tuesday
     * 4=Wednesday
     * 5=Thursday
     * 6=Friday
     * 7=Saturday
     */
    switch(rtc_data[3])
    {
        case 1:
            week_day[2]='N';
            week_day[1]='U';
            week_day[0]='S';
            break;

        case 2:
            week_day[2]='N';
            week_day[1]='O';
            week_day[0]='M';
            break;

        case 3:
            week_day[2]='E';
            week_day[1]='U';
            week_day[0]='T';
            break;

        case 4:
            week_day[2]='D';
            week_day[1]='E';
            week_day[0]='W';
            break;

        case 5:
            week_day[2]='U';
            week_day[1]='H';
            week_day[0]='T';
            break;

        case 6:
            week_day[2]='I';
            week_day[1]='R';
            week_day[0]='F';
            break;

        case 7:
            week_day[2]='T';
            week_day[1]='A';
            week_day[0]='S';
            break;
    }
    //get date data in a nice format
    date[1]=rtc_data[4] & 0x0F;            //lower nibble
    date[1]=date[1] | 0x30;            //get it in ASCII
    date[0]=rtc_data[4] & 0xF0;            //upper nibble
    date[0]=date[0]>>4;
    date[0]=date[0] | 0x30;            //get it in ASCII
    //get month data in a nice format
    /*
     * 1=January
     * 2=February
     * 3=March
     * 4=April
     * 5=May
     * 6=June
     * 7=July
     * 8=August
     * 9=September
     * 10=October
     * 11=November
     * 12=December
     */
    switch(rtc_data[5])
    {
        case 0x01:
            month[2]='N';
            month[1]='A';
            month[0]='J';
            break;

        case 0x02:
            month[2]='B';
            month[1]='E';
            month[0]='F';
            break;

        case 0x03:
            month[2]='R';
            month[1]='A';
            month[0]='M';
            break;

        case 0x04:
            month[2]='R';
            month[1]='P';
            month[0]='A';
            break;

        case 0x05:
            month[2]='Y';
            month[1]='A';
            month[0]='M';
            break;

        case 0x06:
            month[2]='N';
            month[1]='U';
            month[0]='J';
            break;

        case 0x07:
            month[2]='L';
            month[1]='U';
            month[0]='J';
            break;

        case 0x08:
            month[2]='G';
            month[1]='U';
            month[0]='A';
            break;

        case 0x09:
            month[2]='P';
            month[1]='E';
            month[0]='S';
            break;

        case 0x10:
            month[2]='T';
            month[1]='C';
            month[0]='O';
            break;

        case 0x11:
            month[2]='V';
            month[1]='O';
            month[0]='N';
            break;

        case 0x12:
            month[2]='C';
            month[1]='E';
            month[0]='D';
            break;
    }
    //get year data in a nice format
    year[1]=rtc_data[6] & 0x0F;            //lower nibble
    year[1]=year[1] | 0x30;            //get it in ASCII
    year[0]=rtc_data[6] & 0xF0;            //upper nibble
    year[0]=year[0]>>4;
    year[0]=year[0] | 0x30;            //get it in ASCII
    //display everything
    lcd_new_msg_first_line();
    for(unsigned char i=0; i<3; i++)
    {
        lcd_data_transmit(' ');
    }
    //show hours
    for(unsigned char i=0; i<2; i++)
    {
        lcd_data_transmit(hours[i]);
    }
    lcd_data_transmit(':');
    //show minutes
    for(unsigned char i=0; i<2; i++)
    {
        lcd_data_transmit(minutes[i]);
    }
    lcd_data_transmit(':');
    //show seconds
    for(unsigned char i=0; i<2; i++)
    {
        lcd_data_transmit(seconds[i]);
    }
    //indicate AM-PM info
    if(am_pm_indicator==0)
    {
        lcd_data_transmit('A');
        lcd_data_transmit('M');
    }
    else
    {
        lcd_data_transmit('P');
        lcd_data_transmit('M');
    }
    lcd_new_msg_second_line();
    //show weekday
    for(unsigned char i=0; i<3; i++)
    {
        lcd_data_transmit(week_day[i]);
    }
    lcd_data_transmit(' ');
    //show month
    for(unsigned char i=0; i<3; i++)
    {
        lcd_data_transmit(month[i]);
    }
    lcd_data_transmit(' ');
    //show date
    for(unsigned char i=0; i<2; i++)
    {
        lcd_data_transmit(date[i]);
    }
    lcd_data_transmit(',');
    lcd_data_transmit(' ');
    //show year
    lcd_data_transmit('2');
    lcd_data_transmit('0');
    for(unsigned char i=0; i<2; i++)
    {
        lcd_data_transmit(year[i]);
    }
}