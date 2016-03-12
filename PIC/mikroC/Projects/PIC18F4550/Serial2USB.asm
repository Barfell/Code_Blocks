
_interrupt:

;Serial2USB.c,17 :: 		void interrupt(){
;Serial2USB.c,18 :: 		USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
	CALL        _USB_Interrupt_Proc+0, 0
;Serial2USB.c,19 :: 		}
L_end_interrupt:
L__interrupt6:
	RETFIE      1
; end of _interrupt

_main:

;Serial2USB.c,21 :: 		void main(void)
;Serial2USB.c,23 :: 		ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
	MOVLW       15
	IORWF       ADCON1+0, 1 
;Serial2USB.c,24 :: 		CMCON  |= 7;                            // Disable comparators
	MOVLW       7
	IORWF       CMCON+0, 1 
;Serial2USB.c,26 :: 		HID_Enable(&readbuff,&writebuff);       // Enable HID communication
	MOVLW       _readbuff+0
	MOVWF       FARG_HID_Enable_readbuff+0 
	MOVLW       hi_addr(_readbuff+0)
	MOVWF       FARG_HID_Enable_readbuff+1 
	MOVLW       _writebuff+0
	MOVWF       FARG_HID_Enable_writebuff+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_HID_Enable_writebuff+1 
	CALL        _HID_Enable+0, 0
;Serial2USB.c,27 :: 		UART1_Init(9600);      //setup UART for 9600bps comm
	BSF         BAUDCON+0, 3, 0
	MOVLW       4
	MOVWF       SPBRGH+0 
	MOVLW       225
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;Serial2USB.c,28 :: 		UART1_Write_Text("mikroC USB-2-Serial Converter TEST\n");
	MOVLW       ?lstr1_Serial2USB+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_Serial2USB+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;Serial2USB.c,30 :: 		while(1)
L_main0:
;Serial2USB.c,32 :: 		if(UART1_Data_Ready())       //wait for getting input data from UART
	CALL        _UART1_Data_Ready+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main2
;Serial2USB.c,34 :: 		UART1_Read_Text(writebuff, "\n", 255);          //read data
	MOVLW       _writebuff+0
	MOVWF       FARG_UART1_Read_Text_Output+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_UART1_Read_Text_Output+1 
	MOVLW       ?lstr2_Serial2USB+0
	MOVWF       FARG_UART1_Read_Text_Delimiter+0 
	MOVLW       hi_addr(?lstr2_Serial2USB+0)
	MOVWF       FARG_UART1_Read_Text_Delimiter+1 
	MOVLW       255
	MOVWF       FARG_UART1_Read_Text_Attempts+0 
	CALL        _UART1_Read_Text+0, 0
;Serial2USB.c,35 :: 		while(!HID_Write(&writebuff,64));      //send data over USB
L_main3:
	MOVLW       _writebuff+0
	MOVWF       FARG_HID_Write_writebuff+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_HID_Write_writebuff+1 
	MOVLW       64
	MOVWF       FARG_HID_Write_len+0 
	CALL        _HID_Write+0, 0
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_main4
	GOTO        L_main3
L_main4:
;Serial2USB.c,36 :: 		}
L_main2:
;Serial2USB.c,37 :: 		}
	GOTO        L_main0
;Serial2USB.c,38 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
