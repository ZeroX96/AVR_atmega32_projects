;
; testAssem.asm
;
; Created: 12-Oct-17 10:10:52 PM
; Author : Mahmoud
;


; Replace with your application code

.INCLUDE "M32DEF.INC"
LDI R16,HIGH(RAMEND)
OUT SPH,R16
LDI R16,LOW(RAMEND)
OUT SPH,R16
.ORG 0X00
	;	SBI DDRC,0
	;	SBI DDRC,1
	;	CBI DDRC,2

	LDI R16,0B11111011
	OUT DDRC,R16
;LOOP :  SBIS PINC,2
;		SBI PORTC,0
;		SBIS PINC,2
;		RJMP LOOP
;		SBIC PINC,2
;		SBI PORTC,1
;		RJMP LOOP 

LOOP :  SBIS PINC,2
		RJMP OVER
		SBI PORTC,1
		RJMP LOOP
OVER :	SBI PORTC,0
		RJMP LOOP 