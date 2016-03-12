unsigned char rx_data;             //to store received data

//UART initialize function
void serial_init(void)
{
    TRISC|=0xC0;            //setup UART pins
    BRG16=0;                //8 bit BRG
    SPBRG=31;             //9600 bps
    SYNC=0;                 //async transmission
    BRGH=0;
    RX9=0;                  //8-bit data reception
    CREN=1;                 //enable RX
    SPEN=1;                 //enable UART
}
//UART transmit function
void serial_transmit(unsigned char m)
{
    TXREG=m;                      //load register with data
    TXEN=1;                       //initiate transmission
    while(TRMT==0);               //wait till data is sent
}
//UART transmit function for printf()
void putch(unsigned char m)
{
    TXREG=m;                      //load register with data
    TXEN=1;                       //initiate transmission
    while(TRMT==0);               //wait till data is sent
}
//UART RX function
void serial_receive(void)
{
    rx_data=RCREG;
    if(OERR==1)                 //overrun error
    {
        //reset RX
        CREN=0;
        asm("NOP");
        CREN=1;
    }
}
