
_interrupt:

;USB2Serial.c,17 :: 		void interrupt(){
;USB2Serial.c,18 :: 		USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
	CALL        _USB_Interrupt_Proc+0, 0
;USB2Serial.c,19 :: 		}
L_end_interrupt:
L__interrupt9:
	RETFIE      1
; end of _interrupt

_main:

;USB2Serial.c,21 :: 		void main(void)
;USB2Serial.c,23 :: 		ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
	MOVLW       15
	IORWF       ADCON1+0, 1 
;USB2Serial.c,24 :: 		CMCON  |= 7;                            // Disable comparators
	MOVLW       7
	IORWF       CMCON+0, 1 
;USB2Serial.c,26 :: 		HID_Enable(&readbuff,&writebuff);       // Enable HID communication
	MOVLW       _readbuff+0
	MOVWF       FARG_HID_Enable_readbuff+0 
	MOVLW       hi_addr(_readbuff+0)
	MOVWF       FARG_HID_Enable_readbuff+1 
	MOVLW       _writebuff+0
	MOVWF       FARG_HID_Enable_writebuff+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_HID_Enable_writebuff+1 
	CALL        _HID_Enable+0, 0
;USB2Serial.c,27 :: 		UART1_Init(9600);      //setup UART for 9600bps comm
	BSF         BAUDCON+0, 3, 0
	MOVLW       4
	MOVWF       SPBRGH+0 
	MOVLW       225
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;USB2Serial.c,28 :: 		UART1_Write_Text("mikroC USB-2-Serial Converter TEST\n");
	MOVLW       ?lstr1_USB2Serial+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_USB2Serial+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;USB2Serial.c,30 :: 		while(1)
L_main0:
;USB2Serial.c,32 :: 		do
L_main2:
;USB2Serial.c,34 :: 		cnt=HID_Read();          //wait for getting input data from USB
	CALL        _HID_Read+0, 0
	MOVF        R0, 0 
	MOVWF       _cnt+0 
;USB2Serial.c,36 :: 		while((!cnt));
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main2
;USB2Serial.c,38 :: 		for(i=0; i<cnt; i++)
	CLRF        _i+0 
L_main5:
	MOVF        _cnt+0, 0 
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main6
;USB2Serial.c,40 :: 		UART1_Write(readbuff[i]);            //send data through UART
	MOVLW       _readbuff+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_readbuff+0)
	MOVWF       FSR0H 
	MOVF        _i+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_UART1_Write_data_+0 
	CALL        _UART1_Write+0, 0
;USB2Serial.c,38 :: 		for(i=0; i<cnt; i++)
	INCF        _i+0, 1 
;USB2Serial.c,42 :: 		}
	GOTO        L_main5
L_main6:
;USB2Serial.c,49 :: 		}
	GOTO        L_main0
;USB2Serial.c,50 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
