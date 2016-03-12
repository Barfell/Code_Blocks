
_main:

;PIC18F4550_DEV.c,1 :: 		void main(void)
;PIC18F4550_DEV.c,3 :: 		TRISD=0xFE;
	MOVLW       254
	MOVWF       TRISD+0 
;PIC18F4550_DEV.c,4 :: 		while(1)
L_main0:
;PIC18F4550_DEV.c,6 :: 		PORTD.B0=~PORTD.B0;
	BTG         PORTD+0, 0 
;PIC18F4550_DEV.c,7 :: 		Delay_ms(500);
	MOVLW       13
	MOVWF       R11, 0
	MOVLW       175
	MOVWF       R12, 0
	MOVLW       182
	MOVWF       R13, 0
L_main2:
	DECFSZ      R13, 1, 1
	BRA         L_main2
	DECFSZ      R12, 1, 1
	BRA         L_main2
	DECFSZ      R11, 1, 1
	BRA         L_main2
	NOP
;PIC18F4550_DEV.c,8 :: 		}
	GOTO        L_main0
;PIC18F4550_DEV.c,9 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
