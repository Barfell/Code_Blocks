//lcd command transmit function
void lcd_cmd_transmit(unsigned char m)
{
    rs=0;             //command register selected
    lcd_data=m;
    //strobe en pin to latch data into the lcd
    en=1;
    Delay_ms(1);
    en=0;
}
//lcd data transmit function
void lcd_data_transmit(unsigned char p)
{
    rs=1;                //data register selected
    lcd_data=p;
    //strobe en pin to latch data into the lcd
    en=1;
    Delay_ms(1);
    en=0;
}
//lcd data transmit function for printf()
void putch(unsigned char p)
{
    rs=1;                //data register selected
    lcd_data=p;
    //strobe en pin to latch data into the lcd
    en=1;
    Delay_ms(1);
    en=0;
}
//Command function before sending message to 1st line
void lcd_new_msg_first_line(void)
{
    lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
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
//LCD clear display function
void lcd_clear(void)
{
	lcd_cmd_transmit(0x38);                 //initialize 2 lines with 5*7 matrix
    lcd_cmd_transmit(0x01);                 //clear display
    lcd_cmd_transmit(0x80);                //get to 1st line
    lcd_cmd_transmit(0x06);                //shift cursor right by 1 position
}