
_main:

;Soft_UART.c,1 :: 		void main(void)
;Soft_UART.c,3 :: 		char text[]="mikroC UART TEST\n";
	MOVLW       ?ICSmain_text_L0+0
	MOVWF       TBLPTRL 
	MOVLW       hi_addr(?ICSmain_text_L0+0)
	MOVWF       TBLPTRH 
	MOVLW       higher_addr(?ICSmain_text_L0+0)
	MOVWF       TBLPTRU 
	MOVLW       main_text_L0+0
	MOVWF       FSR1 
	MOVLW       hi_addr(main_text_L0+0)
	MOVWF       FSR1H 
	MOVLW       18
	MOVWF       R0 
	MOVLW       1
	MOVWF       R1 
	CALL        ___CC2DW+0, 0
;Soft_UART.c,6 :: 		error=Soft_UART_Init(&PORTD, 0, 1, 9600, 0);      //setup software UART for 9600bps comm
	MOVLW       PORTD+0
	MOVWF       FARG_Soft_UART_Init_port+0 
	MOVLW       hi_addr(PORTD+0)
	MOVWF       FARG_Soft_UART_Init_port+1 
	CLRF        FARG_Soft_UART_Init_rx_pin+0 
	MOVLW       1
	MOVWF       FARG_Soft_UART_Init_tx_pin+0 
	MOVLW       128
	MOVWF       FARG_Soft_UART_Init_baud_rate+0 
	MOVLW       37
	MOVWF       FARG_Soft_UART_Init_baud_rate+1 
	MOVLW       0
	MOVWF       FARG_Soft_UART_Init_baud_rate+2 
	MOVWF       FARG_Soft_UART_Init_baud_rate+3 
	CLRF        FARG_Soft_UART_Init_inverted+0 
	CALL        _Soft_UART_Init+0, 0
;Soft_UART.c,8 :: 		while(1)
L_main0:
;Soft_UART.c,10 :: 		for(i=0; i<18; i++)
	CLRF        main_i_L0+0 
L_main2:
	MOVLW       18
	SUBWF       main_i_L0+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main3
;Soft_UART.c,12 :: 		Soft_UART_Write(text[i]);
	MOVLW       main_text_L0+0
	MOVWF       FSR0 
	MOVLW       hi_addr(main_text_L0+0)
	MOVWF       FSR0H 
	MOVF        main_i_L0+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Soft_UART_Write_udata+0 
	CALL        _Soft_UART_Write+0, 0
;Soft_UART.c,10 :: 		for(i=0; i<18; i++)
	INCF        main_i_L0+0, 1 
;Soft_UART.c,13 :: 		}
	GOTO        L_main2
L_main3:
;Soft_UART.c,14 :: 		Delay_ms(1000);
	MOVLW       61
	MOVWF       R11, 0
	MOVLW       225
	MOVWF       R12, 0
	MOVLW       63
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	DECFSZ      R11, 1, 1
	BRA         L_main5
	NOP
	NOP
;Soft_UART.c,15 :: 		}
	GOTO        L_main0
;Soft_UART.c,16 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
