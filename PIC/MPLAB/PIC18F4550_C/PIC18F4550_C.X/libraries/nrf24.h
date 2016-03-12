//SPI commands
#define R_REGISTER 0x00
#define W_REGISTER 0x20
#define R_RX_PAYLOAD 0x61
#define W_TX_PAYLOAD 0xA0
#define FLUSH_TX 0xE1
#define FLUSH_RX 0xE2
#define REUSE_TX_PL 0xE3
#define NOP 0xFF

//nRF24L01+ register map
#define CONFIG 0x00
#define EN_AA 0x01
#define EN_RXADDR 0x02
#define SETUP_AW 0x03
#define SETUP_RETR 0x04
#define RF_CH 0x05
#define RF_SETUP 0x06
#define STATUS 0x07
#define OBSERVE_TX 0x08
#define CD 0x09
#define RX_ADDR_P0 0x0A
#define RX_ADDR_P1 0x0B
#define RX_ADDR_P2 0x0C
#define RX_ADDR_P3 0x0D
#define RX_ADDR_P4 0x0E
#define RX_ADDR_P5 0x0F
#define TX_ADDR 0x10
#define RX_PW_P0 0x11
#define RX_PW_P1 0x12
#define RX_PW_P2 0x13
#define RX_PW_P3 0x14
#define RX_PW_P4 0x15
#define RX_PW_P5 0x16
#define FIFO_STATUS 0x17
#define DYNPD 0x1C
#define FEATURE 0x1D

unsigned char status;                 //copy of status register in nRF24L01+
unsigned char tx_data[8]="TDXHAS15";     //data to be transmitted
unsigned char rx_data[8]={0, 0, 0, 0, 0, 0, 0, 0};         //data received

//nRF24L01+ register read function
unsigned char nrf24_read(unsigned char read_address)
{
    ss=0;
    unsigned char address, read_data;
    address=read_address | R_REGISTER;           //get required read command
    SPI_master_write(address);            //send read command
    read_data=SPI_master_read();         //get data
    ss=1;
    return read_data;
}
//nRF24L01+ register write function
void nrf24_write(unsigned char write_address, unsigned char write_data)
{
    ss=0;
    unsigned char address;
    address= write_address | W_REGISTER;    //get required write command
    SPI_master_write(address);            //send write command
    SPI_master_write(write_data);           //send data
    ss=1;
}
//nRF24L01+ initialize function
void nrf24_init(void)
{
    //RX payload set to 8 bytes
    nrf24_write(RX_PW_P0, 0x08);
    nrf24_write(CONFIG, 0x3B);            //mask TX_DS and MAX_RT interrupts, power-up the device in PRX mode

    //flush TX & RX FIFOs
    ss=0;
    SPI_master_write(FLUSH_TX);
    ss=1;
    Delay_ms(1);
    ss=0;
    SPI_master_write(FLUSH_RX);
    ss=1;

    nrf24_write(STATUS, 0x7E);            //clear interrupts
    nrf24_write(RF_SETUP, 0x26);          //communication speed=250kbps
}
//nRF24L01+ wireless transmit function
void nrf24_data_tx(void)
{
    Delay_ms(20);         //let the transmitter finish any work it is already doing
    //flush TX
    ss=0;
    SPI_master_write(FLUSH_TX);
    ss=1;
    Delay_ms(1);

    ss=0;
    SPI_master_write(W_TX_PAYLOAD);          //used to initiate transfer of data payload
    //send data for transmission
    SPI_master_write(tx_data[7]);
    SPI_master_write(tx_data[6]);
    SPI_master_write(tx_data[5]);
    SPI_master_write(tx_data[4]);
    SPI_master_write(tx_data[3]);
    SPI_master_write(tx_data[2]);
    SPI_master_write(tx_data[1]);
    SPI_master_write(tx_data[0]);
    ss=1;

    //initiate wireless transmission
    ce=0;
    Delay_ms(1);
    nrf24_write(CONFIG, 0x3A);
    Delay_ms(1);
    ce=1;
    Delay_ms(1);

    nrf24_write(CONFIG, 0x3B);             //put it back in RX mode
}
//nRF24L01+ wireless receive function
void nrf24_data_rx(void)
{
    ss=0;
    SPI_master_write(R_RX_PAYLOAD);       //used to initiate transfer of data payload
    //get received data
    rx_data[0]=SPI_master_read();
    rx_data[1]=SPI_master_read();
    rx_data[2]=SPI_master_read();
    rx_data[3]=SPI_master_read();
    rx_data[4]=SPI_master_read();
    rx_data[5]=SPI_master_read();
    rx_data[6]=SPI_master_read();
    rx_data[7]=SPI_master_read();
    ss=1;
    Delay_ms(1);

    //flush RX
    ss=0;
    SPI_master_write(FLUSH_RX);
    ss=1;
    Delay_ms(1);
    
    //clear interrupts
    nrf24_write(STATUS, 0x7E);
    INT2IF=0;
}