
_interrupt:

;batarya .c,103 :: 		void interrupt (void)
;batarya .c,158 :: 		}
L_interrupt0:
;batarya .c,159 :: 		}
L_end_interrupt:
L__interrupt20:
	RETFIE      1
; end of _interrupt

_main:

;batarya .c,161 :: 		void main()
;batarya .c,163 :: 		float adcValue=0;
	CLRF        main_adcValue_L0+0 
	CLRF        main_adcValue_L0+1 
	CLRF        main_adcValue_L0+2 
	CLRF        main_adcValue_L0+3 
	CLRF        main_i_L0+0 
	CLRF        main_i_L0+1 
;batarya .c,166 :: 		ADCON1  = 0b00001111;      //all port is digital
	MOVLW       15
	MOVWF       ADCON1+0 
;batarya .c,167 :: 		INTCON=0b11101000;
	MOVLW       232
	MOVWF       INTCON+0 
;batarya .c,168 :: 		INTCON2=0b00000000;              //GLOBLE INTRRUPT ENABLE
	CLRF        INTCON2+0 
;batarya .c,170 :: 		T0CON  = 0b100000000;      //prescaler value put
	MOVLW       0
	MOVWF       T0CON+0 
;batarya .c,172 :: 		TMR0   = 55536;            //start counter after this value
	MOVLW       240
	MOVWF       _TMR0+0 
	MOVLW       216
	MOVWF       _TMR0+1 
;batarya .c,174 :: 		ADCON0 = 0b00000011;     //select adc channel
	MOVLW       3
	MOVWF       ADCON0+0 
;batarya .c,175 :: 		ADCON1 = 0b00001110;     //select analog and digital i/p
	MOVLW       14
	MOVWF       ADCON1+0 
;batarya .c,176 :: 		ADCON2 = 0b10001010;     //eqisation time holding cap time
	MOVLW       138
	MOVWF       ADCON2+0 
;batarya .c,178 :: 		TRIS_seg1   =0;
	BCF         TRISC+0, 0 
;batarya .c,179 :: 		TRIS_seg2   =0;
	BCF         TRISC+0, 1 
;batarya .c,180 :: 		TRIS_seg3   =0;
	BCF         TRISC+0, 2 
;batarya .c,181 :: 		TRIS_seg4   =0;
	BCF         TRISC+0, 4 
;batarya .c,182 :: 		TRIS_led1   = 0;
	BCF         TRISA+0, 2 
;batarya .c,183 :: 		TRIS_led2   = 0;
	BCF         TRISA+0, 5 
;batarya .c,184 :: 		TRIS_led3   =0;
	BCF         TRISA+0, 0 
;batarya .c,185 :: 		TRIS_led4   =0;
	BCF         TRISA+0, 1 
;batarya .c,186 :: 		TRIS_led5   =0;
	BCF         TRISA+0, 4 
;batarya .c,187 :: 		TRIS_PORTB    = 0;
	CLRF        TRISB+0 
;batarya .c,188 :: 		TRIS_adcpin    = 1;
	BSF         TRISA+0, 0 
;batarya .c,189 :: 		TRIS_dot    = 0;
	BCF         TRISB+0, 7 
;batarya .c,190 :: 		while(1)
L_main11:
;batarya .c,192 :: 		adc_init();
	CALL        _ADC_Init+0, 0
;batarya .c,193 :: 		for(i=0;i<40;i++)
	CLRF        main_i_L0+0 
	CLRF        main_i_L0+1 
L_main13:
	MOVLW       128
	XORWF       main_i_L0+1, 0 
	MOVWF       R0 
	MOVLW       128
	SUBWF       R0, 0 
	BTFSS       STATUS+0, 2 
	GOTO        L__main22
	MOVLW       40
	SUBWF       main_i_L0+0, 0 
L__main22:
	BTFSC       STATUS+0, 0 
	GOTO        L_main14
;batarya .c,195 :: 		Value[i]=adc_value();
	MOVF        main_i_L0+0, 0 
	MOVWF       R0 
	MOVF        main_i_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       main_Value_L0+0
	ADDWF       R0, 0 
	MOVWF       FLOC__main+0 
	MOVLW       hi_addr(main_Value_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FLOC__main+1 
	CALL        _adc_value+0, 0
	MOVFF       FLOC__main+0, FSR1L
	MOVFF       FLOC__main+1, FSR1H
	MOVF        R0, 0 
	MOVWF       POSTINC1+0 
	MOVF        R1, 0 
	MOVWF       POSTINC1+0 
	MOVF        R2, 0 
	MOVWF       POSTINC1+0 
	MOVF        R3, 0 
	MOVWF       POSTINC1+0 
;batarya .c,196 :: 		adcValue+=Value[i];
	MOVF        main_i_L0+0, 0 
	MOVWF       R0 
	MOVF        main_i_L0+1, 0 
	MOVWF       R1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	RLCF        R0, 1 
	BCF         R0, 0 
	RLCF        R1, 1 
	MOVLW       main_Value_L0+0
	ADDWF       R0, 0 
	MOVWF       FSR2L 
	MOVLW       hi_addr(main_Value_L0+0)
	ADDWFC      R1, 0 
	MOVWF       FSR2H 
	MOVF        main_adcValue_L0+0, 0 
	MOVWF       R0 
	MOVF        main_adcValue_L0+1, 0 
	MOVWF       R1 
	MOVF        main_adcValue_L0+2, 0 
	MOVWF       R2 
	MOVF        main_adcValue_L0+3, 0 
	MOVWF       R3 
	MOVF        POSTINC2+0, 0 
	MOVWF       R4 
	MOVF        POSTINC2+0, 0 
	MOVWF       R5 
	MOVF        POSTINC2+0, 0 
	MOVWF       R6 
	MOVF        POSTINC2+0, 0 
	MOVWF       R7 
	CALL        _Add_32x32_FP+0, 0
	MOVF        R0, 0 
	MOVWF       main_adcValue_L0+0 
	MOVF        R1, 0 
	MOVWF       main_adcValue_L0+1 
	MOVF        R2, 0 
	MOVWF       main_adcValue_L0+2 
	MOVF        R3, 0 
	MOVWF       main_adcValue_L0+3 
;batarya .c,193 :: 		for(i=0;i<40;i++)
	INFSNZ      main_i_L0+0, 1 
	INCF        main_i_L0+1, 1 
;batarya .c,197 :: 		}
	GOTO        L_main13
L_main14:
;batarya .c,198 :: 		adcValue=(float)adcValue/40.0;
	MOVLW       0
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVLW       32
	MOVWF       R6 
	MOVLW       132
	MOVWF       R7 
	MOVF        main_adcValue_L0+0, 0 
	MOVWF       R0 
	MOVF        main_adcValue_L0+1, 0 
	MOVWF       R1 
	MOVF        main_adcValue_L0+2, 0 
	MOVWF       R2 
	MOVF        main_adcValue_L0+3, 0 
	MOVWF       R3 
	CALL        _Div_32x32_FP+0, 0
	MOVF        R0, 0 
	MOVWF       main_adcValue_L0+0 
	MOVF        R1, 0 
	MOVWF       main_adcValue_L0+1 
	MOVF        R2, 0 
	MOVWF       main_adcValue_L0+2 
	MOVF        R3, 0 
	MOVWF       main_adcValue_L0+3 
;batarya .c,199 :: 		convert(adcValue);
	MOVF        R0, 0 
	MOVWF       FARG_convert+0 
	MOVF        R1, 0 
	MOVWF       FARG_convert+1 
	MOVF        R2, 0 
	MOVWF       FARG_convert+2 
	MOVF        R3, 0 
	MOVWF       FARG_convert+3 
	CALL        _convert+0, 0
;batarya .c,200 :: 		delay_ms(100);
	MOVLW       2
	MOVWF       R11, 0
	MOVLW       134
	MOVWF       R12, 0
	MOVLW       153
	MOVWF       R13, 0
L_main16:
	DECFSZ      R13, 1, 1
	BRA         L_main16
	DECFSZ      R12, 1, 1
	BRA         L_main16
	DECFSZ      R11, 1, 1
	BRA         L_main16
;batarya .c,201 :: 		}
	GOTO        L_main11
;batarya .c,202 :: 		}
L_end_main:
	GOTO        $+0
; end of _main

_adc_value:

;batarya .c,205 :: 		float adc_value(void)
;batarya .c,207 :: 		float adc_data=0;
;batarya .c,208 :: 		while(GO/DONE==1);                   //higher bit data start conversion adc value
L_adc_value17:
	GOTO        L_adc_value17
;batarya .c,212 :: 		}
L_end_adc_value:
	RETURN      0
; end of _adc_value

_convert:

;batarya .c,214 :: 		void convert(float f)
;batarya .c,216 :: 		int d=(f*100);
	CLRF        convert_d_L0+0 
	CLRF        convert_d_L0+1 
;batarya .c,217 :: 		digit1=d%10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        convert_d_L0+0, 0 
	MOVWF       R0 
	MOVF        convert_d_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       _digit1+0 
	MOVF        R1, 0 
	MOVWF       _digit1+1 
;batarya .c,218 :: 		d=d/10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        convert_d_L0+0, 0 
	MOVWF       R0 
	MOVF        convert_d_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16x16_S+0, 0
	MOVF        R0, 0 
	MOVWF       convert_d_L0+0 
	MOVF        R1, 0 
	MOVWF       convert_d_L0+1 
;batarya .c,219 :: 		digit2=d%10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       _digit2+0 
	MOVF        R1, 0 
	MOVWF       _digit2+1 
;batarya .c,220 :: 		d=d/10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        convert_d_L0+0, 0 
	MOVWF       R0 
	MOVF        convert_d_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16x16_S+0, 0
	MOVF        R0, 0 
	MOVWF       convert_d_L0+0 
	MOVF        R1, 0 
	MOVWF       convert_d_L0+1 
;batarya .c,221 :: 		digit3=d%10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	CALL        _Div_16x16_S+0, 0
	MOVF        R8, 0 
	MOVWF       R0 
	MOVF        R9, 0 
	MOVWF       R1 
	MOVF        R0, 0 
	MOVWF       _digit3+0 
	MOVF        R1, 0 
	MOVWF       _digit3+1 
;batarya .c,222 :: 		digit4=d/10;
	MOVLW       10
	MOVWF       R4 
	MOVLW       0
	MOVWF       R5 
	MOVF        convert_d_L0+0, 0 
	MOVWF       R0 
	MOVF        convert_d_L0+1, 0 
	MOVWF       R1 
	CALL        _Div_16x16_S+0, 0
	MOVF        R0, 0 
	MOVWF       _digit4+0 
	MOVF        R1, 0 
	MOVWF       _digit4+1 
;batarya .c,223 :: 		}
L_end_convert:
	RETURN      0
; end of _convert
