
_main:

;EEPROM.c,1 :: 		void main(void)
;EEPROM.c,6 :: 		UART1_Init(9600);      //setup UART for 9600bps comm
	BSF         BAUDCON+0, 3, 0
	MOVLW       4
	MOVWF       SPBRGH+0 
	MOVLW       225
	MOVWF       SPBRG+0 
	BSF         TXSTA+0, 2, 0
	CALL        _UART1_Init+0, 0
;EEPROM.c,7 :: 		UART1_Write_Text("mikroC EEPROM TEST\n");
	MOVLW       ?lstr1_EEPROM+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr1_EEPROM+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,10 :: 		EEPROM_Write(0, '1');    //write data
	CLRF        FARG_EEPROM_Write_address+0 
	MOVLW       49
	MOVWF       FARG_EEPROM_Write_data_+0 
	CALL        _EEPROM_Write+0, 0
;EEPROM.c,11 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	DECFSZ      R11, 1, 1
	BRA         L_main0
;EEPROM.c,13 :: 		EEPROM_Write(1, '2');    //write data
	MOVLW       1
	MOVWF       FARG_EEPROM_Write_address+0 
	MOVLW       50
	MOVWF       FARG_EEPROM_Write_data_+0 
	CALL        _EEPROM_Write+0, 0
;EEPROM.c,14 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main1:
	DECFSZ      R13, 1, 1
	BRA         L_main1
	DECFSZ      R12, 1, 1
	BRA         L_main1
	DECFSZ      R11, 1, 1
	BRA         L_main1
;EEPROM.c,16 :: 		EEPROM_Write(2, '3');    //write data
	MOVLW       2
	MOVWF       FARG_EEPROM_Write_address+0 
	MOVLW       51
	MOVWF       FARG_EEPROM_Write_data_+0 
	CALL        _EEPROM_Write+0, 0
;EEPROM.c,17 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
;EEPROM.c,20 :: 		IntToStr((int)EEPROM_Read(0), rom_data);      //read data
	CLRF        FARG_EEPROM_Read_address+0 
	CALL        _EEPROM_Read+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVLW       0
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;EEPROM.c,21 :: 		UART1_Write_Text("EEPROM Data : ");
	MOVLW       ?lstr2_EEPROM+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr2_EEPROM+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,22 :: 		UART1_Write_Text(rom_data);
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,23 :: 		UART_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;EEPROM.c,24 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main3:
	DECFSZ      R13, 1, 1
	BRA         L_main3
	DECFSZ      R12, 1, 1
	BRA         L_main3
	DECFSZ      R11, 1, 1
	BRA         L_main3
;EEPROM.c,26 :: 		IntToStr((int)EEPROM_Read(1), rom_data);      //read data
	MOVLW       1
	MOVWF       FARG_EEPROM_Read_address+0 
	CALL        _EEPROM_Read+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVLW       0
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;EEPROM.c,27 :: 		UART1_Write_Text("EEPROM Data : ");
	MOVLW       ?lstr3_EEPROM+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr3_EEPROM+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,28 :: 		UART1_Write_Text(rom_data);
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,29 :: 		UART_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;EEPROM.c,30 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main4:
	DECFSZ      R13, 1, 1
	BRA         L_main4
	DECFSZ      R12, 1, 1
	BRA         L_main4
	DECFSZ      R11, 1, 1
	BRA         L_main4
;EEPROM.c,32 :: 		IntToStr((int)EEPROM_Read(2), rom_data);      //read data
	MOVLW       2
	MOVWF       FARG_EEPROM_Read_address+0 
	CALL        _EEPROM_Read+0, 0
	MOVF        R0, 0 
	MOVWF       FARG_IntToStr_input+0 
	MOVLW       0
	MOVWF       FARG_IntToStr_input+1 
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_IntToStr_output+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_IntToStr_output+1 
	CALL        _IntToStr+0, 0
;EEPROM.c,33 :: 		UART1_Write_Text("EEPROM Data : ");
	MOVLW       ?lstr4_EEPROM+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(?lstr4_EEPROM+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,34 :: 		UART1_Write_Text(rom_data);
	MOVLW       main_rom_data_L0+0
	MOVWF       FARG_UART1_Write_Text_uart_text+0 
	MOVLW       hi_addr(main_rom_data_L0+0)
	MOVWF       FARG_UART1_Write_Text_uart_text+1 
	CALL        _UART1_Write_Text+0, 0
;EEPROM.c,35 :: 		UART_Write('\n');
	MOVLW       10
	MOVWF       FARG_UART_Write__data+0 
	CALL        _UART_Write+0, 0
;EEPROM.c,36 :: 		Delay_ms(20);            //needed to ensure correct write/read
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       56
	MOVWF       R12, 0
	MOVLW       173
	MOVWF       R13, 0
L_main5:
	DECFSZ      R13, 1, 1
	BRA         L_main5
	DECFSZ      R12, 1, 1
	BRA         L_main5
	DECFSZ      R11, 1, 1
	BRA         L_main5
;EEPROM.c,38 :: 		while(1);
L_main6:
	GOTO        L_main6
;EEPROM.c,39 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
