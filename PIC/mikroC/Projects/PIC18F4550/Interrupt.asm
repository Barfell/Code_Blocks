
_main:

;Interrupt.c,3 :: 		void main(void)
;Interrupt.c,5 :: 		TRISD=0xFE;        //RD0 is output
	MOVLW       254
	MOVWF       TRISD+0 
;Interrupt.c,6 :: 		T0CON.B6=1;          //timer configured in 8-bit mode
	BSF         T0CON+0, 6 
;Interrupt.c,7 :: 		T0CON.B5=0;            //clock source is internal clock
	BCF         T0CON+0, 5 
;Interrupt.c,8 :: 		TMR0L=0xE0;            //load timer register
	MOVLW       224
	MOVWF       TMR0L+0 
;Interrupt.c,9 :: 		T0CON.B7=1;          //enable timer 0
	BSF         T0CON+0, 7 
;Interrupt.c,10 :: 		RCON.B7=1;           //enable interrupt priority
	BSF         RCON+0, 7 
;Interrupt.c,11 :: 		INTCON2.B2=1;        //timer 0 interrupt is of high priority
	BSF         INTCON2+0, 2 
;Interrupt.c,12 :: 		INTCON=0xE0;         //enable high and low priority interrupts, enable timer 0 interrupt, clear timer 0 interrupt flag
	MOVLW       224
	MOVWF       INTCON+0 
;Interrupt.c,14 :: 		while(1);
L_main0:
	GOTO        L_main0
;Interrupt.c,15 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_interrupt:

;Interrupt.c,18 :: 		void interrupt(void)
;Interrupt.c,20 :: 		t0_isr();     //call timer 0 ISR
	CALL        _t0_isr+0, 0
;Interrupt.c,21 :: 		}
L_end_interrupt:
L__interrupt4:
	RETFIE      1
; end of _interrupt

_t0_isr:

;Interrupt.c,24 :: 		void t0_isr(void)
;Interrupt.c,26 :: 		T0CON.B7=0;        //turn off timer
	BCF         T0CON+0, 7 
;Interrupt.c,27 :: 		INTCON.B1=0;           //clear interrupt flag
	BCF         INTCON+0, 1 
;Interrupt.c,28 :: 		PORTD.B0=~PORTD.B0;          //toggle RD0
	BTG         PORTD+0, 0 
;Interrupt.c,29 :: 		TMR0L=0xE0;            //load timer register
	MOVLW       224
	MOVWF       TMR0L+0 
;Interrupt.c,30 :: 		T0CON.B7=1;        //turn  on timer
	BSF         T0CON+0, 7 
;Interrupt.c,31 :: 		}
L_end_t0_isr:
	RETURN      0
; end of _t0_isr
