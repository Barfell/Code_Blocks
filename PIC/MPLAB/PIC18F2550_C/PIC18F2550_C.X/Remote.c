
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

#define forward RC6
#define forward_left RB2
#define backward_left RB3
#define forward_right RB5
#define backward_right RB6
#define backward RB4
#define rotate_right RB7

void button_press(void);
void SPI_init(void);
void SPI_transmit(unsigned char x);
unsigned char tx_data;
void main()
{
    //initialize button pins
    ADCON1=0x07;
    TRISB=0xFC;
    TRISC=0x7F;
    SPI_init();               //initialize MSSP for SPI comm
    while(1)
    {
        button_press();
        SPI_transmit(tx_data);
    }
}
//SPI initialization function
void SPI_init(void)
{
    SMP=0;           //data sampled at middle of data output time
    CKE=0;           //transmission occurs on rising edge
    CKP=0;           //idle state is the low state
    SSPCON1|=0x01;   //SPI Master with clock=Fosc/64
    SSPEN=1;         //enable MSSP
}
//buttom press function
void button_press(void)
{
    if((forward==0) && (forward_right==1) && (forward_left==1))
    {
        tx_data=0x11;
    }
    else if((forward==0) || (forward_right==0))
    {
        tx_data=0x22;
    }
    else if((forward==0) || (forward_left==0))
    {
        tx_data=0x33;
    }
    else if((backward==0) && (backward_left==1) && (backward_right==1))
    {
        tx_data=0x44;
    }
    else if((backward==0) || (backward_right==0))
    {
        tx_data=0x55;
    }
    else if((backward==0) || (backward_left==0))
    {
        tx_data=0x66;
    }
    else if(rotate_right==0)
    {
        tx_data=0x77;
    }
    else
    {
        tx_data=0x00;
    }
}
//SPI transmit function
void SPI_transmit(unsigned char x)
{
    SSPIF=0;
    unsigned char flush;            //to get dummy data from SSPBUF
    flush=SSPBUF;
    //send data
    SSPBUF=x;
    while(SSPIF==0);
}