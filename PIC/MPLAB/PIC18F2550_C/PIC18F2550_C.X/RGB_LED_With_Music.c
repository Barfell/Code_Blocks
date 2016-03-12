
// PIC18F2550 Configuration Bit Settings

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
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
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

//crystal frequency
#define _XTAL_FREQ 8000000

//RGB color pins
#define RED RB2
#define GREEN RB0
#define BLUE RB1

void sys_init(void);
void adc_init(void);
int adc_acquire(void);
void color_mixer(void);
void delay(unsigned long x);
unsigned int music_volume;
void main()
{
    sys_init();
    while(1)
    {
        music_volume=adc_acquire();             //get value from ADC
        color_mixer();              //mix RGB colors according to value received
    }
}
//system initialize function
void sys_init(void)
{
    TRISB=0x00;
    music_volume=0;         //initialize music value
    adc_init();               //initlialize ADC
    //initialize RGB LED
    RED=0;
    BLUE=0;
    GREEN=0;
}
//ADC initialize function
void adc_init(void)
{
    ADON=1;                       //enable ADC module
    TRISA=0xFF;                   //PORTA is input
    ADCS0=1;                      //clock=F/8
    ACQT0=1;                      //acquisition time=t*2
    ADFM=1;                       //right justified
    ADIF=0;                       //A/D complete flag
    //Music output on AN0
    CHS0=0;
    CHS1=0;
    CHS2=0;
    CHS3=0;
}
//ADC DAQ function
int adc_acquire(void)
{
    GO=1;                      //start A/D conversion
    while(ADIF==0);            //check to see if A/D conversion is complete
    ADIF=0;
    return ADRES;                //get ADC output
}
//color mixer function
void color_mixer(void)
{
    if(music_volume>=0 && music_volume<=170)
    {
        BLUE=1;
        RED=0;
        GREEN=0;
        delay(100);
    }
    else if(music_volume>=171 && music_volume<=341)
    {
        GREEN=1;
        BLUE=1;
        RED=0;
        delay(100);
    }
    else if(music_volume>=341 && music_volume<=511)
    {
        GREEN=1;
        BLUE=1;
        RED=0;
        delay(100);
    }
    else if(music_volume>=512 && music_volume<=682)
    {
        GREEN=1;
        BLUE=0;
        RED=0;
        delay(100);
    }
    else if(music_volume>=683 && music_volume<=853)
    {
        RED=1;
        BLUE=0;
        GREEN=1;
        delay(100);
    }
    else if(music_volume>=853 && music_volume<=1023)
    {
        RED=1;
        BLUE=0;
        GREEN=0;
        delay(100);
    }
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