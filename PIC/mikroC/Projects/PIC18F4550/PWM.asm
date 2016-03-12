
_main:

;PWM.c,1 :: 		void main(void)
;PWM.c,4 :: 		TRISC=0xFB;       //RC2 is output
	MOVLW       251
	MOVWF       TRISC+0 
;PWM.c,5 :: 		PWM1_Init(10000);    //10kHz PWM
	BSF         T2CON+0, 0, 0
	BCF         T2CON+0, 1, 0
	MOVLW       124
	MOVWF       PR2+0, 0
	CALL        _PWM1_Init+0, 0
;PWM.c,6 :: 		PWM1_Start();              //start PWM
	CALL        _PWM1_Start+0, 0
;PWM.c,7 :: 		while(1)
L_main0:
;PWM.c,9 :: 		for(i=0; i<=255; i++)
	CLRF        main_i_L0+0 
L_main2:
	MOVF        main_i_L0+0, 0 
	SUBLW       255
	BTFSS       STATUS+0, 0 
	GOTO        L_main3
;PWM.c,11 :: 		PWM1_Set_Duty(i);
	MOVF        main_i_L0+0, 0 
	MOVWF       FARG_PWM1_Set_Duty_new_duty+0 
	CALL        _PWM1_Set_Duty+0, 0
;PWM.c,12 :: 		Delay_ms(50);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       69
	MOVWF       R12, 0
	MOVLW       169
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
;PWM.c,9 :: 		for(i=0; i<=255; i++)
	INCF        main_i_L0+0, 1 
;PWM.c,13 :: 		}
	GOTO        L_main2
L_main3:
;PWM.c,14 :: 		}
	GOTO        L_main0
;PWM.c,15 :: 		}
L_end_main:
	GOTO        $+0
; end of _main
