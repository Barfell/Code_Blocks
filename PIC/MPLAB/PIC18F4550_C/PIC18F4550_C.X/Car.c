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

/*
 * |--------------|
 * |M1          M2|
 * |     MD1      |
 * |              |
 * |     MCU      |
 * |          RF  |
 * |   MD2        |
 * |M3          M4|
 * |--------------|
 *
 * Commands:
 * 0x11->Forward
 * 0x22->Forward Right
 * 0x33->Forward Left
 * 0x44->Reverse
 * 0x55->Reverse Right
 * 0x66->Reverse Left
 * 0x77->Rotate Right
 */
#define M1_1 RC1
#define M1_2 RC2
#define M2_1 RA1
#define M2_2 RA2
#define M3_1 RD2
#define M3_2 RD3
#define M4_1 RD6
#define M4_2 RD7

unsigned char SPI_data=0x00;                 //received 8-bit command
void SPI_init(void);
void interrupt isr(void);
void SPI_isr(void);
void delay(unsigned char x);
void motor_control(unsigned char rx_data);
void main()
{
    //initialize motor pin modes
    ADCON1=0x0F;
    TRISA=0xF9;
    TRISC=0xF9;
    TRISD=0x33;
    TRISB|=0x03;
    //initialize interrupts
    IPEN=0;
    GIE=1;
    PEIE=1;
    SSPIF=0;
    SSPIE=1;
    //initialize motor pins
    M1_1=0;
    M1_2=0;
    M2_1=0;
    M2_2=0;
    M3_1=0;
    M3_2=0;
    M4_1=0;
    M4_2=0;
    SPI_init();
    while(1)
    {
        //control motors according to the command
        motor_control(SPI_data);
        //clear rx_data
        SPI_data=0;
    }
}
//SPI initialization function
void SPI_init(void)
{
    SMP=0;           //data sampled at middle of data output time
    CKE=0;           //reception occurs on rising edge
    CKP=0;           //idle state is the low state
    SSPCON1|=0x05;   //SPI Slave w/o SS'
    SSPEN=1;         //enable MSSP
    SSPIF=0;
}
//isr vector
void interrupt isr(void)
{
    asm("CALL _SPI_isr");
}
//isr for SPI
void SPI_isr(void)
{
    SPI_data=SSPBUF;
    SSPIF=0;
}
//motor control function
void motor_control(unsigned char rx_data)
{
    if(rx_data==0x11)             //forward
    {
        M1_1=1;
        M1_2=0;
        M2_1=1;
        M2_2=0;
        M3_1=1;
        M3_2=0;
        M4_1=1;
        M4_2=0;
    }
    else if(rx_data==0x22)         //forward right
    {
        M1_1=1;
        M1_2=0;
        M3_1=1;
        M3_2=0;
        //PWM
        M2_1=0;
        M4_1=0;
        delay(15);
        M2_1=1;
        M2_2=0;
        M4_1=1;
        M4_2=0;
        delay(5);
    }
    else if(rx_data==0x33)         //forward left
    {
        M2_1=1;
        M2_2=0;
        M4_1=1;
        M4_2=0;
        //PWM
        M1_1=0;
        M3_1=0;
        delay(15);
        M1_1=1;
        M1_2=0;
        M3_1=1;
        M3_2=0;
        delay(5);
    }
    else if(rx_data==0x44)         //reverse
    {
        M1_1=0;
        M1_2=1;
        M2_1=0;
        M2_2=1;
        M3_1=0;
        M3_2=1;
        M4_1=0;
        M4_2=1;
    }
    else if(rx_data==0x55)         //reverse right
    {
        M1_1=0;
        M1_2=1;
        M3_1=0;
        M3_2=1;
        //PWM
        M2_2=0;
        M4_2=0;
        delay(15);
        M2_1=0;
        M2_2=1;
        M4_1=0;
        M4_2=1;
        delay(5);
    }
    else if(rx_data==0x66)         //reverse left
    {
        M2_1=0;
        M2_2=1;
        M4_1=0;
        M4_2=1;
        //PWM
        M1_2=0;
        M3_2=0;
        delay(15);
        M1_1=0;
        M1_2=1;
        M3_1=0;
        M3_2=1;
        delay(5);
    }
    else if(rx_data==0x77)         //rotate right
    {
        M1_1=1;
        M1_2=0;
        M2_1=0;
        M2_2=1;
        M3_1=1;
        M3_2=0;
        M4_1=0;
        M4_2=1;
    }
    else                         //no command issued
    {
        M1_1=0;
        M1_2=0;
        M2_1=0;
        M2_2=0;
        M3_1=0;
        M3_2=0;
        M4_1=0;
        M4_2=0;
    }
}
//delay function
void delay(unsigned char x)
{
    unsigned char i, j;
    for(i=0; i<x; i++)
    {
        for(j=0; j<255; j++);
    }
}
