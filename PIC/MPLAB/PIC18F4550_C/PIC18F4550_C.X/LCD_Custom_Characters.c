// PIC18F4550 Configuration Bit Settings

#include <xc.h>

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

#define _XTAL_FREQ 8000000              //crystal frequency
//lcd pins
#define lcd_data PORTB
#define rs RC0
#define en RC1

void lcd_init(void);
void lcd_cmd_transmit(unsigned char m);
void lcd_data_transmit(unsigned char p);
void lcd_new_msg_first_line(void);
void lcd_new_msg_second_line(void);
void delay(unsigned long x);
/*
 * Displaying custom characters-
 * The Hitachi HD44780 controlled LCD has 3 memory locations of interest to us-
 * i)CGROM-> Character Graphics ROM. Has the 5x7 matrix pattern for all the standard ASCII characters. Cannot be written to.
 * When we ask for standard data to be displayed, the controller check for the pattern in the CGROM & sends it to the DDRAM
 * to display it.
 * ii)DDRAM-> Display Data RAM. Holds the 5x7 patterns for the characters currently being displayed on the screen.
 * iii)CGRAM-> Character Graphics RAM. Works the same way as CGROM but its contents can be modified. It is used to create &
 * display custom characters. The CGRAM is of 64 bytes; 8 bytes per pattern; for each pattern each byte corresponding to 1 row
 * in the 5x8 matrix (yes we have 8 rows but standard characters only use 7; custom characters can use all 8 if desired).
 * The CGRAM pattern address is from 0x40 to 0x47.
 *
 * Hence if we want to write the 1st row of the 5x8 matrix of the custom character, then we first go to the 0x00 CG RAM location.
 * To do this we have to send the lcd a command 0x40. Now we are ready to send data to CG RAM location 0x00. After sending the
 * whole pattern for location 0x00, the location pointer will increment automatically to 0x01 location. We can also control the
 * pointer address manually for sending command values from 0x40 to 0x47.
 *
 * The 5 LSBs of the byte sent for each row of the 5x8 matrix map to the corresponding pixels. For example-
 *            -***-             0x0E
 *            ** **             0x1B
 *            *---*             0x1B
 *            *---*             0x1B
 *            *---*             0x1B
 *            *---*             0x1B
 *            *---*             0x1B
 *            *****             0x1F
 *
 * Writing sequence-
 * -set CGRAM ADDRESS    lcd_cmd_transmit(0x40).
 * -send the byte 0   lcd_data_transmit(0x0E).
 * -send the byte 1   lcd_data_transmit(0x1B).
 * -send the byte 2   lcd_data_transmit(0x11).
 * -send the byte 3   lcd_data_transmit(0x11).
 * -send the byte 4   lcd_data_transmit(0x11).
 * -send the byte 5   lcd_data_transmit(0x11).
 * -send the byte 6   lcd_data_transmit(0x11).
 * -send the byte 7   lcd_data_transmit(0x1F).
 * -come back to DDRAM
 * -display data as shown
 */
void main()
{
    TRISC=0xFC;                  //lcd control pins
    TRISB=0x00;                  //lcd data bus
    lcd_init();
    while(1)
    {
        lcd_cmd_transmit(0x40);            //go to CGRAM location 0
        //send custom character data; CGRAM location increments by 1 automatically with each write
        lcd_data_transmit(0x0E);
        lcd_data_transmit(0x1B);
        lcd_data_transmit(0x11);
        lcd_data_transmit(0x11);
        lcd_data_transmit(0x11);
        lcd_data_transmit(0x11);
        lcd_data_transmit(0x11);
        lcd_data_transmit(0x1F);
        //the above code makes one custom character; we can make & store 7 more like this in the LCD at any given time
        //switch back to DDRAM
        lcd_cmd_transmit(0x80);
        lcd_cmd_transmit(0x06);
        //display custom character at location 0x40; sending 0x01 displays character at location 0x41 & so on
        lcd_data_transmit(0x00);
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
//lcd command transmit function
void lcd_cmd_transmit(unsigned char m)
{
    rs=0;             //command register selected
    lcd_data=m;
    //strobe en pin to latch data into the lcd
    en=1;
    delay(1);
    en=0;
}
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
    lcd_cmd_transmit(0x01);                 //clear display
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
	unsigned long m;
	for(m=0; m<x; m++)
	{
		__delay_ms(1);
	}
}
