void main()
{
     char buffer[10];         //10 character buffer for data comm

     UART1_Init(9600);      //setup UART for 9600bps comm
     UART1_Write_Text("mikroC UART TEST\n");

     while(1)
     {
             if(UART1_Data_Ready())       //data received
             {
                  UART1_Read_Text(buffer, "\n", 255);          //read data
                  if(UART1_Tx_Idle())        //ready to transmit
                  {
                       UART1_Write_Text(buffer);        //send data
                  }
             }
     }
}