//BCLIF must be checked manually in multi-master buses; functions may also need to be modified a bit
unsigned char i2c_write_stat=-1;          //status of I2C write

//I2C initialize function
void i2c_master_init(void)
{
    TRISB|=0x03;              //initialize I2C pins as input
    SMP=1;             //disable slew rate control for 100kbps mode
    SSPCON1=0x28;      //enable MSSP in master mode
    SSPADD=49;      //100kbps, try 39 if this doesn't work
}
//I2C start condition generate function
void i2c_start(void)
{
    //initiate start condition
    SSPIF=0;
    WCOL=0;
    BCLIF=0;
    SEN=1;
    while(SSPIF==0);         //wait till start condition is complete
    SSPIF=0;               //reset interrupt flag
}
//I2C repeated start condition generate function
void i2c_repeated_start(void)
{
    //initiate repeated start condition
    SSPIF=0;
    WCOL=0;
    BCLIF=0;
    RSEN=1;
    while(SSPIF==0);         //wait till repeated start condition is complete
    SSPIF=0;               //reset interrupt flag
}
//I2C transmit function
unsigned char i2c_transmit(unsigned char m)
{
    WCOL=0;
    SSPIF=0;
    BCLIF=0;
    SSPBUF=m;              //start transmission
    while(SSPIF==0);         //wait till transmission is complete
    if(ACKSTAT==0)            //acknowledge received
    {
        return 0;
    }
    else                    //acknowledge not received
    {
        return 1;
    }
}
//I2C receive function
unsigned char i2c_receive(void)
{
    WCOL=0;
    SSPIF=0;
    RCEN=1;              //start reception
    while(SSPIF==0);         //wait till reception is complete
    unsigned char a=SSPBUF;            //get data
    return a;
}
//I2C acknowledge condition generate function
void i2c_ack(unsigned char x)
{
	/*
	* x=='Y' -> send acknowledge
	* else don't send acknowledge
	*/
	
    //set acknowledge data bit
    if(x=='Y')           //acknowledge
    {
        ACKDT=0;
    }
    else
    {
        ACKDT=1;         //not acknowledge
    }
    //initiate acknowledge condition
    SSPIF=0;
    BCLIF=0;
    WCOL=0;
    ACKEN=1;
    while(SSPIF==0);         //wait till acknowledge transmission is complete
    SSPIF=0;               //reset interrupt flag
}
//I2C stop condition generate function
void i2c_stop(void)
{
    //initiate stop condition
    SSPIF=0;
    WCOL=0;
    BCLIF=0;
    PEN=1;
    while(SSPIF==0);         //wait till stop condition is complete
    SSPIF=0;               //reset interrupt flag
}