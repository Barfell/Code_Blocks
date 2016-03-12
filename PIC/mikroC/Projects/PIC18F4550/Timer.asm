
_main:

;Timer.c,1 :: 		void main(void)
;Timer.c,3 :: 		TRISD=0xFE;        //RD0 is output
	MOVLW       254
	MOVWF       TRISD+0 
;Timer.c,4 :: 		T0CON.B6=1;          //timer configured in 8-bit mode
	BSF         T0CON+0, 6 
;Timer.c,5 :: 		T0CON.B5=0;            //clock source is internal clock
	BCF         T0CON+0, 5 
;Timer.c,6 :: 		T0CON.B7=1;          //enable timer 0
	BSF         T0CON+0, 7 
;Timer.c,9 :: 		while(1)
L_main0:
;Timer.c,11 :: 		INTCON.B2=0;                //clear overflow
	BCF         INTCON+0, 2 
;Timer.c,12 :: 		TMR0L=0xE0;                 //load timer register
	MOVLW       224
	MOVWF       TMR0L+0 
;Timer.c,13 :: 		PORTD.B0=~PORTD.B0;
	BTG         PORTD+0, 0 
;Timer.c,14 :: 		while(TMR0IF==0);           //check for overflow
L_main3:
;Timer.c,15 :: 		}
	GOTO        L_main0
;Timer.c,16 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
