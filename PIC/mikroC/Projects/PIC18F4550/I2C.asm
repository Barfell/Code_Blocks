
_main:

;I2C.c,8 :: 		void main(void)
;I2C.c,10 :: 		error=Soft_UART_Init(&PORTD, 0, 1, 9600, 0);      //setup software UART for 9600bps comm
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
	MOVF        R0, 0 
	MOVWF       _error+0 
;I2C.c,11 :: 		for(i=0; i<17; i++)
	CLRF        _i+0 
L_main0:
	MOVLW       17
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main1
;I2C.c,13 :: 		Soft_UART_Write(greet[i]);
	MOVLW       _greet+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_greet+0)
	MOVWF       FSR0H 
	MOVF        _i+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Soft_UART_Write_udata+0 
	CALL        _Soft_UART_Write+0, 0
;I2C.c,11 :: 		for(i=0; i<17; i++)
	INCF        _i+0, 1 
;I2C.c,14 :: 		}
	GOTO        L_main0
L_main1:
;I2C.c,16 :: 		rtc_init();                   //initialize RTC
	CALL        _rtc_init+0, 0
;I2C.c,17 :: 		Delay_ms(1);                  //wait a little
	MOVLW       16
	MOVWF       R12, 0
	MOVLW       148
	MOVWF       R13, 0
L_main3:
	DECFSZ      R13, 1, 1
	BRA         L_main3
	DECFSZ      R12, 1, 1
	BRA         L_main3
	NOP
;I2C.c,19 :: 		while(1)
L_main4:
;I2C.c,22 :: 		write_stat=I2C1_Start();                   //generate start condition
	CALL        _I2C1_Start+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,24 :: 		write_stat=I2C1_Wr(0xD0);         //RTC address=1101000
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,26 :: 		write_stat=I2C1_Wr(0x00);         //RTC seconds register
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,27 :: 		I2C1_Repeated_Start();                      //generate repeated start condition
	CALL        _I2C1_Repeated_Start+0, 0
;I2C.c,29 :: 		write_stat=I2C1_Wr(0xD1);         //RTC address=1101000
	MOVLW       209
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,32 :: 		for(i=0; i<7; i++)
	CLRF        _i+0 
L_main6:
	MOVLW       7
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main7
;I2C.c,34 :: 		if(i<6)
	MOVLW       6
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main9
;I2C.c,36 :: 		rtc_data[i]=I2C1_Rd(1);     //read data from RTC and send acknowledge
	MOVLW       _rtc_data+0
	MOVWF       FLOC__main+0 
	MOVLW       hi_addr(_rtc_data+0)
	MOVWF       FLOC__main+1 
	MOVF        _i+0, 0 
	ADDWF       FLOC__main+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__main+1, 1 
	MOVLW       1
	MOVWF       FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVFF       FLOC__main+0, FSR1
	MOVFF       FLOC__main+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
;I2C.c,37 :: 		}
	GOTO        L_main10
L_main9:
;I2C.c,40 :: 		rtc_data[i]=I2C1_Rd(0);     //read data from RTC and send no acknowledge
	MOVLW       _rtc_data+0
	MOVWF       FLOC__main+0 
	MOVLW       hi_addr(_rtc_data+0)
	MOVWF       FLOC__main+1 
	MOVF        _i+0, 0 
	ADDWF       FLOC__main+0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FLOC__main+1, 1 
	CLRF        FARG_I2C1_Rd_ack+0 
	CALL        _I2C1_Rd+0, 0
	MOVFF       FLOC__main+0, FSR1
	MOVFF       FLOC__main+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
;I2C.c,41 :: 		}
L_main10:
;I2C.c,32 :: 		for(i=0; i<7; i++)
	INCF        _i+0, 1 
;I2C.c,42 :: 		}
	GOTO        L_main6
L_main7:
;I2C.c,43 :: 		I2C1_Stop();                     //generate stop condition
	CALL        _I2C1_Stop+0, 0
;I2C.c,46 :: 		for(i=0; i<7; i++)
	CLRF        _i+0 
L_main11:
	MOVLW       7
	SUBWF       _i+0, 0 
	BTFSC       STATUS+0, 0 
	GOTO        L_main12
;I2C.c,48 :: 		Soft_UART_Write(rtc_data[i]);
	MOVLW       _rtc_data+0
	MOVWF       FSR0 
	MOVLW       hi_addr(_rtc_data+0)
	MOVWF       FSR0H 
	MOVF        _i+0, 0 
	ADDWF       FSR0, 1 
	BTFSC       STATUS+0, 0 
	INCF        FSR0H, 1 
	MOVF        POSTINC0+0, 0 
	MOVWF       FARG_Soft_UART_Write_udata+0 
	CALL        _Soft_UART_Write+0, 0
;I2C.c,46 :: 		for(i=0; i<7; i++)
	INCF        _i+0, 1 
;I2C.c,49 :: 		}
	GOTO        L_main11
L_main12:
;I2C.c,51 :: 		Delay_ms(1000);           //wait a bit
	MOVLW       61
	MOVWF       R11, 0
	MOVLW       225
	MOVWF       R12, 0
	MOVLW       63
	MOVWF       R13, 0
L_main14:
	DECFSZ      R13, 1, 1
	BRA         L_main14
	DECFSZ      R12, 1, 1
	BRA         L_main14
	DECFSZ      R11, 1, 1
	BRA         L_main14
	NOP
	NOP
;I2C.c,52 :: 		}
	GOTO        L_main4
;I2C.c,53 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_rtc_init:

;I2C.c,56 :: 		void rtc_init(void)
;I2C.c,58 :: 		I2C1_Init(100000);       //initialize I2C for 100kbps
	MOVLW       120
	MOVWF       SSPADD+0 
	CALL        _I2C1_Init+0, 0
;I2C.c,59 :: 		write_stat=I2C1_Start();                   //generate start condition
	CALL        _I2C1_Start+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,61 :: 		write_stat=I2C1_Wr(0xD0);         //RTC address=1101000
	MOVLW       208
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,63 :: 		write_stat=I2C1_Wr(0x00);         //RTC seconds register
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,65 :: 		write_stat=I2C1_Wr(0x00);        //enable oscillator & seconds value
	CLRF        FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,67 :: 		write_stat=I2C1_Wr(0x59);         //minutes value
	MOVLW       89
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,69 :: 		write_stat=I2C1_Wr(0x51);            //12-hour mode & hours value
	MOVLW       81
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,71 :: 		write_stat=I2C1_Wr(0x06);         //weekday
	MOVLW       6
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,73 :: 		write_stat=I2C1_Wr(0x10);        //date
	MOVLW       16
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,75 :: 		write_stat=I2C1_Wr(0x05);         //month
	MOVLW       5
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,77 :: 		write_stat=I2C1_Wr(0x14);        //year
	MOVLW       20
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,79 :: 		write_stat=I2C1_Wr(0x13);           //enable 32.768 kHz square wave
	MOVLW       19
	MOVWF       FARG_I2C1_Wr_data_+0 
	CALL        _I2C1_Wr+0, 0
	MOVF        R0, 0 
	MOVWF       _write_stat+0 
;I2C.c,80 :: 		I2C1_Stop();                     //generate stop condition
	CALL        _I2C1_Stop+0, 0
;I2C.c,81 :: 		}
L_end_rtc_init:
	RETURN      0
; end of _rtc_init
