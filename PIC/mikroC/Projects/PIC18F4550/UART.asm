
_main:

;UART.c,1 :: 		void main()
;UART.c,5 :: 		UART1_Init(9600);      //setup UART for 9600bps comm
	BSF         BAUDCON+0, 3, 0
	MOVLW       4
	MOVWF       SPBRGH+0 
	MOVLW       225
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;UART.c,6 :: 		UART1_Write_Text("mikroC UART TEST\n");
	MOVLW       ?lstr1_UART+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_UART+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;UART.c,8 :: 		while(1)
L_main0:
;UART.c,10 :: 		if(UART1_Data_Ready())       //data received
	CALL        _UART1_Data_Ready+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main2
;UART.c,12 :: 		UART1_Read_Text(buffer, "\n", 255);          //read data
	MOVLW       main_buffer_L0+0
	MOVWF       FARG_UART1_Read_Text_Output+0 
	MOVLW       hi_addr(main_buffer_L0+0)
	MOVWF       FARG_UART1_Read_Text_Output+1 
	MOVLW       ?lstr2_UART+0
	MOVWF       FARG_UART1_Read_Text_Delimiter+0 
	MOVLW       hi_addr(?lstr2_UART+0)
	MOVWF       FARG_UART1_Read_Text_Delimiter+1 
	MOVLW       255
	MOVWF       FARG_UART1_Read_Text_Attempts+0 
	CALL        _UART1_Read_Text+0, 0
;UART.c,13 :: 		if(UART1_Tx_Idle())        //ready to transmit
	CALL        _UART1_Tx_Idle+0, 0
	MOVF        R0, 1 
	BTFSC       STATUS+0, 2 
	GOTO        L_main3
;UART.c,15 :: 		UART1_Write_Text(buffer);        //send data
	MOVLW       main_buffer_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_buffer_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;UART.c,16 :: 		}
L_main3:
;UART.c,17 :: 		}
L_main2:
;UART.c,18 :: 		}
	GOTO        L_main0
;UART.c,19 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
