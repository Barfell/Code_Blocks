
_main:

;ADC.c,1 :: 		void main()
;ADC.c,5 :: 		TRISA|=0xFF;     //ADC input on AN0
	MOVLW       255
	IORWF       TRISA+0, 1 
;ADC.c,6 :: 		TRISC|=0xC0;     //setup IO pins for UART
	MOVLW       192
	IORWF       TRISC+0, 1 
;ADC.c,7 :: 		UART1_Init(9600);      //setup UART for 9600bps comm
	BSF         BAUDCON+0, 3, 0
	MOVLW       4
	MOVWF       SPBRGH+0 
	MOVLW       225
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;ADC.c,8 :: 		ADC_Init();           //start ADC
	CALL        _ADC_Init+0, 0
;ADC.c,9 :: 		UART1_Write_Text("mikroC ADC TEST\n");
	MOVLW       ?lstr1_ADC+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_ADC+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;ADC.c,11 :: 		while(1)
L_main0:
;ADC.c,13 :: 		IntToStr((int)ADC_Get_Sample(0), adc_data);      //get ADC data
	CLRF        FARG_ADC_Get_Sample_channel+0 
	CALL        _ADC_Get_Sample+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVF        R1, 0 
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       main_adc_data_L0+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(main_adc_data_L0+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;ADC.c,16 :: 		UART1_Write_Text("AN0 : ");
	MOVLW       ?lstr2_ADC+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr2_ADC+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;ADC.c,17 :: 		UART1_Write_Text(adc_data);
	MOVLW       main_adc_data_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_adc_data_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;ADC.c,18 :: 		UART_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;ADC.c,20 :: 		Delay_ms(1000);        //wait a bit
	MOVLW       61
	MOVWF       R11, 0
	MOVLW       225
	MOVWF       R12, 0
	MOVLW       63
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
	NOP
;ADC.c,21 :: 		}
	GOTO        L_main0
;ADC.c,22 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
