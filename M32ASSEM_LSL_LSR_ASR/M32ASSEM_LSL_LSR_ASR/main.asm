;
; M32ASSEM_LSL_LSR_ASR.asm
;
; Created: 22-Nov-17 08:27:58 PM
; Author : Mahmoud
;


; Replace with your application code
MAIN :
		LDI R16,0B11010010
		LDI R17,8
LOOP :	
		ASR R16
		DEC R17
		BRNE LOOP

		RJMP MAIN
