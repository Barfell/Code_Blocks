unsigned short write_stat=0;          //status of I2C write
unsigned char rtc_data[7];               //data received from I2C
char i, error;
char greet[]="mikroC I2C TEST\n";

void rtc_init(void);            //RTC initialize function

void main(void)
{
     error=Soft_UART_Init(&PORTD, 0, 1, 9600, 0);      //setup software UART for 9600bps comm
     for(i=0; i<17; i++)
     {
              Soft_UART_Write(greet[i]);
     }
     
     rtc_init();                   //initialize RTC
     Delay_ms(1);                  //wait a little
     
     while(1)
     {

             write_stat=I2C1_Start();                   //generate start condition
             //address the RTC, write mode
             write_stat=I2C1_Wr(0xD0);         //RTC address=1101000
             //address of the RTC register to get the data from
             write_stat=I2C1_Wr(0x00);         //RTC seconds register
             I2C1_Repeated_Start();                      //generate repeated start condition
             //address RTC to get data from it, read mode
             write_stat=I2C1_Wr(0xD1);         //RTC address=1101000

             //read data from RTC; we have to read 7 bytes of data
             for(i=0; i<7; i++)
             {
                  if(i<6)
                  {
                         rtc_data[i]=I2C1_Rd(1);     //read data from RTC and send acknowledge
                  }
                  else
                  {
                         rtc_data[i]=I2C1_Rd(0);     //read data from RTC and send no acknowledge
                  }
             }
             I2C1_Stop();                     //generate stop condition

             //send time info via UART
             for(i=0; i<7; i++)
             {
                      Soft_UART_Write(rtc_data[i]);
             }
             
             Delay_ms(1000);           //wait a bit
    }
}

//RTC initialize function
void rtc_init(void)
{
    I2C1_Init(100000);       //initialize I2C for 100kbps
    write_stat=I2C1_Start();                   //generate start condition
    //address the RTC, write mode
    write_stat=I2C1_Wr(0xD0);         //RTC address=1101000
    //address of the RTC register to be written to
    write_stat=I2C1_Wr(0x00);         //RTC seconds register
    //RTC oscillator is disabled by default; enable it & also set seconds value
    write_stat=I2C1_Wr(0x00);        //enable oscillator & seconds value
    //set minutes value
    write_stat=I2C1_Wr(0x59);         //minutes value
    //set hours value
    write_stat=I2C1_Wr(0x51);            //12-hour mode & hours value
    //set day of the week
    write_stat=I2C1_Wr(0x06);         //weekday
    //set date
    write_stat=I2C1_Wr(0x10);        //date
    //set month
    write_stat=I2C1_Wr(0x05);         //month
    //set year
    write_stat=I2C1_Wr(0x14);        //year
    //enable square wave output if required
    write_stat=I2C1_Wr(0x13);           //enable 32.768 kHz square wave
    I2C1_Stop();                     //generate stop condition
}