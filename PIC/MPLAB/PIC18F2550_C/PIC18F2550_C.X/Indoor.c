
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

#define temp_sensor RA2
#define fan RC1
#define ldr RA3
#define light RC0
//lcd pins
#define lcd_data PORTB
#define rs RC7
#define en RC6

void sys_init(void);
void lcd_init(void);
void lcd_data_transmit(unsigned char p);
void lcd_cmd_transmit(unsigned char m);
void hex2ascii(unsigned char y);
void adc_init(void);
unsigned int adc_acquire(void);
void temp_acquire(void);
void temp_check(void);
void light_acquire(void);
void light_check(void);
void delay(unsigned int n);
unsigned char msb, lsb;                //ASCII values to be sent to display
union adc_data
{
    unsigned int data;
    unsigned char x[2];
}analog_ip;
void main()
{
    sys_init();
    while(1)
    {
        temp_acquire();                     //get temp data & act accordingly
        light_acquire();                    //get light data & act accordingly
        delay(2000);
    }
}
//Overall system initialize function
void sys_init(void)
{
    TRISA=0xFF;          //analog inputs
    TRISC=0x30;          //lcd control pins & lighting
    TRISB=0x00;          //LCD data bus
    lcd_init();       //initialize LCD
    adc_init();          //initialize ADC
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
//ADC initialize function
void adc_init(void)
{
    ADCON1=0x0C;           //AN0-AN2 are analog inputs
    ADFM=1;                //right justified result
    ACQT0=1;               //2*Tad acquisition time
    ADCS0=1;               //Tad=Fosc/8
    ADON=1;                //start ADC
    ADIF=0;                //A/D complete flag
}
//ADC DAQ function
unsigned int adc_acquire(void)
{
    GO=1;                      //start A/D conversion
    while(ADIF==0);            //check to see if A/D conversion is complete
    ADIF=0;
    return ADRES;                //get ADC output
}
//Hex to ASCII conversion function
void hex2ascii(unsigned char y)
{
    //get decimal value
    msb=y/10;
    lsb=y%10;
    //convert to ascii
    msb=0x30 | msb;
    lsb=0x30 | lsb;
}
//Get temperature function
void temp_acquire(void)
{
    unsigned char temp_msg[]={"  Temp: "};
    unsigned char temp_unit[]={"degC"};
    unsigned char i;
    unsigned int l;
    //select channel AN0
    CHS0=0;
    CHS1=0;
    CHS2=0;
    CHS3=0;
    l=adc_acquire();      //get data
    l=l*50;
    l=l/1023;
    l=l*10;
    analog_ip.data=l;                  //for sending to display
    //switch on fan if needed
    temp_check();
    hex2ascii(analog_ip.x[0]);             //convert to ASCII for display
    //send temperature values to display
    lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
    lcd_cmd_transmit(0x80);                //get to 1st line
    lcd_cmd_transmit(0x06);                //shift cursor right by 1 position
    for(i=0; i<8; i++)
    {
        lcd_data_transmit(temp_msg[i]);
    }
    lcd_data_transmit(msb);
    lcd_data_transmit(lsb);
    for(i=0; i<4; i++)
    {
        lcd_data_transmit(temp_unit[i]);
    }
}
//temp check function
void temp_check(void)
{
    if(analog_ip.data<0x1A)
    {
        fan=1;
    }
}
//get ldr data function
void light_acquire(void)
{
    //select channel AN1
    CHS0=1;
    CHS1=0;
    CHS2=0;
    CHS3=0;
    analog_ip.data=adc_acquire();      //get data
    //switch on light if needed
    light_check();
}
//light check function
void light_check(void)
{
    if(analog_ip.data<200)
    {
        light=1;
    }
}
//delay function
void delay(unsigned int n)
{
    unsigned int i;
    unsigned char j;
    for(i=0; i<n; i++)
    {
        for(j=0; j<255; j++);
    }
}