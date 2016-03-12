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

#include<stdio.h>

#define _XTAL_FREQ 20000000            //crystal frequency

//ADC channels
#define CHANNEL_0 0x00
#define CHANNEL_1 0x04
#define CHANNEL_2 0x08
#define CHANNEL_3 0x0C
#define CHANNEL_4 0x10
#define CHANNEL_5 0x14
#define CHANNEL_6 0x18
#define CHANNEL_7 0x1C
#define CHANNEL_8 0x20
#define CHANNEL_9 0x24
#define CHANNEL_10 0x28
#define CHANNEL_11 0x2C
#define CHANNEL_12 0x30

void serial_init(void);
void adc_init(void);
unsigned int adc_acquire(unsigned char channel);
void putch(unsigned char m);
void timer0_init(void);
void interrupt_init(void);
void interrupt isr(void);
void timer0_isr(void);
void gas_sense(void);
void delay(unsigned long x);

unsigned char gas_sensor_ready=0;          //indicates end of 10 minutes required by the sensor

void main()
{
    serial_init();       //initialize UART
    adc_init();           //initialize ADC
    timer0_init();     //initialize timer0
    interrupt_init();      //initialize interrupt
    while(1)
    {
        gas_sense();              //get data from gas sensor
        delay(1000);              //wait a second
    }
}
//timer0 initialize function
void timer0_init(void)
{
    //clear timer registers
    TMR0H=0;
    TMR0L=0;
    T0CON=0x07;        //timer0 configured in 16-bit mode, 1:256 prescaler
    TMR0ON=1;          //enable timer0
}
//interrupt initialize function
void interrupt_init(void)
{
    IPEN=1;             //enable interrupt priority
    GIEH=1;             //enable high priority interrupts
    GIEL=1;             //enable low priority interrupts
    TMR0IE=1;             //enable timer0 interrupt
    TMR0IF=0;             //clear interrupt flag
}
//UART initialize function
void serial_init(void)
{
    TRISC|=0xC0;            //setup UART pins
    BRG16=0;                //8 bit BRG
    SPBRG=31;             //9600 bps
    SYNC=0;                 //async transmission
    BRGH=0;
//    RX9=0;                  //8-bit data reception
//    CREN=1;                 //enable RX
    SPEN=1;                 //enable UART
}
//ADC initialize function
void adc_init(void)
{
    TRISA=0xFF;                   //RA0 is input
    ADCS1=1;                      //clock=F/32
    ACQT0=1;                      //acquisition time=clock*2
    ADFM=1;                       //right justified
    ADIF=0;                       //clear A/D complete interrupt flag
    ADON=1;                       //enable ADC module
}
//ISR vector function
void interrupt isr(void)
{
    asm("CALL _timer0_isr");
}
//timer0 ISR function
void timer0_isr(void)
{
    static unsigned char ten_minute_count=0;         //counter to keep track of timer overflow
    /*
     * for each timer overflow we get a delay of 3.36seconds approx.
     * 3.36*180=605seconds approx.
     */
    ten_minute_count++;      //increment counter
    if(ten_minute_count==180)
    {
        TMR0ON=0;     //disable timer0
        gas_sensor_ready=1;          //give end of 10 minute indication
    }
    TMR0IF=0;        //clear interrupt flag
}
//ADC DAQ function
unsigned int adc_acquire(unsigned char channel)
{
    //set to desired channel for analog DAQ
    ADCON0&=0x03;
    ADCON0|=channel;
    //perform A/D conversion now
    GO=1;                      //start A/D conversion
    while(ADIF==0);            //check to see if A/D conversion is complete
    ADIF=0;                    //clear interrupt flag
    return ADRES;                //get ADC output
}
//UART transmit function; required for printf()
void putch(unsigned char m)
{
    TXREG=m;
    TXEN=1;
    while(TRMT==0);
}
//combustible gas sensor data acquire function
void gas_sense(void)
{
    if(gas_sensor_ready==1)          //sensor is ready to transmit reliable data
    {
        float gas_data=adc_acquire(CHANNEL_0);     //get data
        gas_data=gas_data*50;
        gas_data=gas_data/1023;
        gas_data=gas_data*200;
        unsigned int gas_output=gas_data;
        printf("Gas concentration (ppm): %d\n", gas_output);
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
