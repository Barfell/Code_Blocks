#define DECIMAL_OFF 0
#define DECIMAL_ON 1

/*
 *                        _ _ _ _
 *                           1
 *                       |       |
 *                       |       |
 *                      6|       |2
 *                       |       |
 *                        _ _ _ _
 *                           7
 *                       |       |
 *                       |       |
 *                     5 |       |3
 *                       |       |
 *                        _ _ _ _   **8
 *                           4
 */
 
//common cathode seven segment display function
unsigned char seven_seg_com_cath(unsigned char number, unsigned char decimal_select)
{
    if(decimal_select==DECIMAL_ON)         //turn on decimal
    {
        switch(number)
        {
            case 0:
                return 0xBF;

            case 1:
                return 0x86;

            case 2:
                return 0xDB;

            case 3:
                return 0xCF;

            case 4:
                return 0xE6;

            case 5:
                return 0xED;

            case 6:
                return 0xFD;

            case 7:
                return 0xA7;

            case 8:
                return 0xFF;

            case 9:
                return 0xEF;
        }
    }
    else if(decimal_select==DECIMAL_OFF)        //turn off decimal
    {
        switch(number)
        {
            case 0:
                return 0x3F;

            case 1:
                return 0x06;

            case 2:
                return 0x5B;

            case 3:
                return 0x4F;

            case 4:
                return 0x66;

            case 5:
                return 0x6D;

            case 6:
                return 0x7D;

            case 7:
                return 0x27;

            case 8:
                return 0x7F;

            case 9:
                return 0x6F;
        }
    }
}
//common anode seven segment display function
unsigned char seven_seg_com_ano(unsigned char number, unsigned char decimal_select)
{
    if(decimal_select==DECIMAL_ON)         //turn on decimal
    {
        switch(number)
        {
            case 0:
                return 0x40;

            case 1:
                return 0x79;

            case 2:
                return 0x24;

            case 3:
                return 0x30;

            case 4:
                return 0x19;

            case 5:
                return 0x12;

            case 6:
                return 0x02;

            case 7:
                return 0x58;

            case 8:
                return 0x00;

            case 9:
                return 0x10;
        }
    }
    else if(decimal_select==DECIMAL_OFF)        //turn off decimal
    {
        switch(number)
        {
            case 0:
                return 0xC0;

            case 1:
                return 0xF9;

            case 2:
                return 0xA4;

            case 3:
                return 0xB0;

            case 4:
                return 0x99;

            case 5:
                return 0x92;

            case 6:
                return 0x82;

            case 7:
                return 0xD8;

            case 8:
                return 0x80;

            case 9:
                return 0x90;
        }
    }
}