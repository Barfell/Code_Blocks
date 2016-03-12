//button debounce function
unsigned char debounce_state(unsigned char pin_state, unsigned char  col_no)
{
    unsigned char after_debounce, before_debounce;
    before_debounce=pin_state;
    Delay_ms(20);
    switch(col_no)
    {
        case 1:                  //1st column
            after_debounce=c1;
            break;

        case 2:                  //2nd column
            after_debounce=c2;
            break;

        case 3:                  //3rd column
            after_debounce=c3;
            break;

        case 4:                  //4th column
            after_debounce=c4;
            break;

        default:                      //invalid column
            after_debounce=10;
    }
    if(before_debounce==after_debounce)
    {
        switch(col_no)
        {
            case 1:                  //1st column
                return 1;

            case 2:                  //2nd column
                return 2;

            case 3:                  //3rd column
                return 3;

            case 4:                  //4th column
                return 4;

            default:                      //invalid column
                return 0;
        }
    }
    else
    {
        return 0;
    }
}

//row check function
unsigned char row_check(unsigned char col_no)
{
    switch(col_no)
    {
        case 1:              //checking column 1
            r2=1;
            r3=1;
            r4=1;
            if(c1==0)
            {
                return 0;
            }
            r1=1;
            r2=0;
            if(c1==0)
            {
                return 1;
            }
            r2=1;
            r3=0;
            if(c1==0)
            {
                return 2;
            }
            r3=1;
            r4=0;
            if(c1==0)
            {
                return 3;
            }

        case 2:             //checking column 2
            r2=1;
            r3=1;
            r4=1;
            if(c2==0)
            {
                return 0;
            }
            r1=1;
            r2=0;
            if(c2==0)
            {
                return 1;
            }
            r2=1;
            r3=0;
            if(c2==0)
            {
                return 2;
            }
            r3=1;
            r4=0;
            if(c2==0)
            {
                return 3;
            }

        case 3:               //checking column 3
            r2=1;
            r3=1;
            r4=1;
            if(c3==0)
            {
                return 0;
            }
            r1=1;
            r2=0;
            if(c3==0)
            {
                return 1;
            }
            r2=1;
            r3=0;
            if(c3==0)
            {
                return 2;
            }
            r3=1;
            r4=0;
            if(c3==0)
            {
                return 3;
            }

        case 4:                     //checking column 4
            r2=1;
            r3=1;
            r4=1;
            if(c4==0)
            {
                return 0;
            }
            r1=1;
            r2=0;
            if(c4==0)
            {
                return 1;
            }
            r2=1;
            r3=0;
            if(c4==0)
            {
                return 2;
            }
            r3=1;
            r4=0;
            if(c4==0)
            {
                return 3;
            }

        default:
            return 8;
    }
}
// key scan function to get row & column
unsigned char keyscan(void)
{
    unsigned char debounce_result=0;
    unsigned char column, row;                             //address of key pressed
    unsigned char keypad[4][4]={'1','2','3','A',
                                '4','5','6','B',
                                '7','8','9','C',
                                '*','0','#','D'};            //keypad array

    //just set any random value for row & column; ensure its not a valid value for the keypad array
    column=8;
    row=8;

    //setup keypad
    r1=0;
    r2=0;
    r3=0;
    r4=0;

    //scan keypad
    if((c1==0))            //possible key press on column 1
    {
        debounce_result=debounce_state(c1, 1);         //debounce key
    }
    if((c2==0))            //possible key press on column 2
    {
        debounce_result=debounce_state(c2, 2);         //debounce key
    }
    if((c3==0))            //possible key press on column 3
    {
        debounce_result=debounce_state(c3, 3);         //debounce key
    }
    if((c4==0))            //possible key press on column 4
    {
        debounce_result=debounce_state(c4, 4);         //debounce key
    }

    //genuine key press
    if(debounce_result!=0)                     
    {
        switch(debounce_result)                    //get column
        {
            case 1:
                column=0;    //1
                break;

            case 2:
                column=1;    //2
                break;

            case 3:
                column=2;    //3
                break;

            case 4:
                column=3;    //4
                break;

            default:
                column=8;
        }
    }
    row=row_check(debounce_result);                   //get row
    
    if((row!=8) && (column!=8))
    {
        return keypad[row][column];
    }
    else
    {
        return 0;
    }
}
