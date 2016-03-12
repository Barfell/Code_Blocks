
_interrupt:

;USB_HID.c,8 :: 		void interrupt(){
;USB_HID.c,9 :: 		USB_Interrupt_Proc();                   // USB servicing is done inside the interrupt
	CALL        _USB_Interrupt_Proc+0, 0
;USB_HID.c,10 :: 		}
L_end_interrupt:
L__interrupt10:
	RETFIE      1
; end of _interrupt

_main:

;USB_HID.c,12 :: 		void main(void)
;USB_HID.c,14 :: 		ADCON1 |= 0x0F;                         // Configure all ports with analog function as digital
	MOVLW       15
	IORWF       ADCON1+0, 1 
;USB_HID.c,15 :: 		CMCON  |= 7;                            // Disable comparators
	MOVLW       7
	IORWF       CMCON+0, 1 
;USB_HID.c,17 :: 		HID_Enable(&readbuff,&writebuff);       // Enable HID communication
	MOVLW       _readbuff+0
	MOVWF       FARG_HID_Enable_readbuff+0 
	MOVLW       hi_addr(_readbuff+0)
	MOVWF       FARG_HID_Enable_readbuff+1 
	MOVLW       _writebuff+0
	MOVWF       FARG_HID_Enable_writebuff+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_HID_Enable_writebuff+1 
	CALL        _HID_Enable+0, 0
;USB_HID.c,19 :: 		while(1)
L_main0:
;USB_HID.c,21 :: 		while(!HID_Read());         //wait for getting input data from USB
L_main2:
	CALL        _HID_Read+0, 0
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_main3
	GOTO        L_main2
L_main3:
;USB_HID.c,24 :: 		for(cnt=0;cnt<64;cnt++)
	CLRF        _cnt+0 
L_main4:
	MOVLW       64
	SUBWF       _cnt+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main5
;USB_HID.c,26 :: 		writebuff[cnt]=test_data[cnt];
	MOVLW       _writebuff+0
	MOVWF       FSR1 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FSR1H 
	MOVF        _cnt+0, 0 
	ADDWF       FSR1, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR1H, 1 
	MOVLW       _test_data+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_test_data+0)
	MOVWF       FSR0H 
	MOVF        _cnt+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       POSTINC1+0 
;USB_HID.c,24 :: 		for(cnt=0;cnt<64;cnt++)
	INCF        _cnt+0, 1 
;USB_HID.c,27 :: 		}
	GOTO        L_main4
L_main5:
;USB_HID.c,29 :: 		while(!HID_Write(&writebuff,64));      //send data over USB
L_main7:
	MOVLW       _writebuff+0
	MOVWF       FARG_HID_Write_writebuff+0 
	MOVLW       hi_addr(_writebuff+0)
	MOVWF       FARG_HID_Write_writebuff+1 
	MOVLW       64
	MOVWF       FARG_HID_Write_len+0 
	CALL        _HID_Write+0, 0
	MOVF        R0, 1 
	BTFSS       STATUS+0, 2 
	GOTO        L_main8
	GOTO        L_main7
L_main8:
;USB_HID.c,30 :: 		}
	GOTO        L_main0
;USB_HID.c,31 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
