
_main:

;SPI.c,3 :: 		void main(void)
;SPI.c,5 :: 		ADCON1=0x0F;              //all pins are digital IO
	MOVLW       15
	MOVWF       ADCON1+0 
;SPI.c,8 :: 		TRISB&=0xFB;
	MOVLW       251
	ANDWF       TRISB+0, 1 
;SPI.c,9 :: 		ss=1;
	BSF         PORTB+0, 2 
;SPI.c,11 :: 		SPI1_Init_Advanced(_SPI_MASTER_OSC_DIV64, _SPI_DATA_SAMPLE_MIDDLE, _SPI_CLK_IDLE_LOW, _SPI_LOW_2_HIGH);   //initialize SPI in 00 mode
	MOVLW       2
	MOVWF       FARG_SPI1_Init_Advanced_master+0 
	CLRF        FARG_SPI1_Init_Advanced_data_sample+0 
	CLRF        FARG_SPI1_Init_Advanced_clock_idle+0 
	MOVLW       1
	MOVWF       FARG_SPI1_Init_Advanced_transmit_edge+0 
	CALL        _SPI1_Init_Advanced+0, 0
;SPI.c,14 :: 		ss=0;
	BCF         PORTB+0, 2 
;SPI.c,15 :: 		SPI1_Write(0x37);
	MOVLW       55
	MOVWF       FARG_SPI1_Write_data_+0 
	CALL        _SPI1_Write+0, 0
;SPI.c,16 :: 		SPI1_Write(0xFF);
	MOVLW       255
	MOVWF       FARG_SPI1_Write_data_+0 
	CALL        _SPI1_Write+0, 0
;SPI.c,17 :: 		ss=1;
	BSF         PORTB+0, 2 
;SPI.c,18 :: 		Delay_ms(1);
	MOVLW       16
	MOVWF       R12, 0
	MOVLW       148
	MOVWF       R13, 0
L_main0:
	DECFSZ      R13, 1, 1
	BRA         L_main0
	DECFSZ      R12, 1, 1
	BRA         L_main0
	NOP
;SPI.c,22 :: 		while(1);
L_main1:
	GOTO        L_main1
;SPI.c,23 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
