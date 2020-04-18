;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                                       ATmega32  Specific code
;                                           GNU AVR Compiler
;
;
; File     : avr_isr.s (originally bsp_isr.s)
; By       : JJL
;          : FT
;          : [with modifications by Nick D'Ademo]
;********************************************************************************************************

//#include  <os_cpu_i.h>
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////msa_TEST
;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                                       ATmega32  Specific code
;                                           GNU AVR Compiler
;
;
; File         : os_cpu_i.h
; Version      : 1.19
; Programer(s) : JJL
;              : FT 
;
;********************************************************************************************************

;********************************************************************************************************
;                                            BIT DEFINITIONS
;********************************************************************************************************

BIT00   = 0x01
BIT01   = 0x02
BIT02   = 0x04
BIT03   = 0x08
BIT04   = 0x10
BIT05   = 0x20
BIT06   = 0x40
BIT07   = 0x80

;********************************************************************************************************
;                                           I/O PORT ADDRESSES
;********************************************************************************************************

SREG    = 0x3F
SPH     = 0x3E
SPL     = 0x3D
EIND    = 0x3C
;RAMPZ   = 0x3B
;RAMPY   = 0x3A
;RAMPX   = 0x39
;RAMPD   = 0x38

;********************************************************************************************************
;                                         MACROS
;********************************************************************************************************

;*
;*********************************************************************************************************
;*                               PUSH ALL THE REGISTER INTO THE STACK
;*
;* Description : Save all the register into the stack.
;*                           +-------+
;*             [RO..RAMPZ] ->|  RO   |
;*                           |  SREG |
;*                           |  R1   |
;*                           |  R2   |
;*                           |   .   |
;*                           |   .   |
;*                           | RAMPZ |
;*                           +-------+
;*********************************************************************************************************
;*

               .macro  PUSH_ALL                            ; Save all registers
	            PUSH    R0
				IN      R0, SREG
				PUSH    R0
				PUSH    R1
				CLR     R1				
				PUSH    R2
				PUSH    R3
				PUSH    R4
				PUSH    R5
				PUSH    R6
				PUSH    R7
				PUSH    R8
				PUSH    R9
				PUSH    R10
				PUSH    R11
				PUSH    R12
				PUSH    R13
				PUSH    R14
				PUSH    R15
				PUSH    R16
				PUSH    R17
				PUSH    R18
				PUSH    R19
				PUSH    R20
				PUSH    R21
				PUSH    R22
				PUSH    R23
				PUSH    R24
				PUSH    R25
				PUSH    R26
				PUSH    R27
				PUSH    R28
				PUSH    R29
				PUSH    R30
				PUSH    R31
                ;IN      R16, EIND
                ;PUSH    R16                
				;IN      R16, RAMPD
                ;PUSH    R16                
				;IN      R16, RAMPX
                ;PUSH    R16                
				;IN      R16, RAMPY
                ;PUSH    R16
				;IN      R16, RAMPZ
                ;PUSH    R16                
                .endm
;*
;*********************************************************************************************************
;*                               POP ALL THE REGISTER OUT THE STACK
;*
;* Description : Restore all the register form the stack
;*                +-------+
;*                |  RO   | ---> [RO..RAMPZ]
;*                |  SREG |
;*                |  R1   |
;*                |  R2   |
;*                |   .   |
;*                |   .   |
;*                | RAMPZ |
;*                +-------+
;*********************************************************************************************************
;*
                .macro  POP_ALL                             ; Restore all registers
                ;POP     R16								;//modified_by_msa_to_meet_the_atmega32_constrains
                ;OUT     RAMPZ, R16							;//modified_by_msa_to_meet_the_atmega32_constrains
				;POP     R16								;//modified_by_msa_to_meet_the_atmega32_constrains
                ;OUT     RAMPY, R16							;//modified_by_msa_to_meet_the_atmega32_constrains
                ;POP     R16								;//modified_by_msa_to_meet_the_atmega32_constrains
                ;OUT     RAMPX, R16							;//modified_by_msa_to_meet_the_atmega32_constrains
                ;POP     R16								;//modified_by_msa_to_meet_the_atmega32_constrains
                ;OUT     RAMPD, R16							;//modified_by_msa_to_meet_the_atmega32_constrains
                ;POP     R16								;//modified_by_msa_to_meet_the_atmega32_constrains
                ;OUT     EIND,  R16							;//modified_by_msa_to_meet_the_atmega32_constrains
				POP     R31
				POP     R30
				POP     R29
				POP     R28
				POP     R27
				POP     R26
				POP     R25
				POP     R24
				POP     R23
				POP     R22
				POP     R21
				POP     R20
				POP     R19
				POP     R18
				POP     R17
				POP     R16
				POP     R15
				POP     R14
				POP     R13
				POP     R12
				POP     R11
				POP     R10
				POP     R9
				POP     R8
				POP     R7
				POP     R6
				POP     R5
				POP     R4
				POP     R3
				POP     R2
				POP     R1
				POP     R0
				OUT     SREG, R0
				POP     R0
                .endm
;*
;*********************************************************************************************************
;*                               PUSH THE STACK POINTER INTO THE STACK
;*
;* Description : Save the stack pointer
;* 
;* Note(s)     : R28 and R29 are equal to the current stak pointer [R28-R29] = SP
;*               after the macro exit.
;*
;*********************************************************************************************************
;*
     
                .macro  SAVE_SP                            ; Save stack pointer
                IN      R26,  SPL
				IN      R27,  SPH
			  .endm

;*
;*********************************************************************************************************
;*                               RESTORE THE STACK POINTER
;*
;* Description : Restore the Stack Pointer
;* 
;* Note(s)     : X register points to the memory location where the SP is contained.
;*
;*********************************************************************************************************
;*
                .macro  RESTORE_SP                             ; Restore stack pointer
                 LD      R28,X+
                 OUT     SPL,R28
                 LD      R29,X+
                 OUT     SPH,R29
				.endm               

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////msa_TEST

;********************************************************************************************************
;                                         PUBLIC DECLARATIONS
;********************************************************************************************************

		.global TickISR				
		;.global usartc0_rx_isr			//modified_by_msa_to_meet_the_atmega32_constrains
		;.global usartf0_rx_isr			//modified_by_msa_to_meet_the_atmega32_constrains
		;.global pushbutton_timer_isr	//modified_by_msa_to_meet_the_atmega32_constrains


;********************************************************************************************************
;                                         EXTERNAL DECLARATIONS
;********************************************************************************************************

		.extern OSIntNesting
		.extern OSTCBCur
		.extern OSTimeTick
		.extern OSIntExit

		;.extern usartc0_rx_isr_handler			//modified_by_msa_to_meet_the_atmega32_constrains
		;.extern usartf0_rx_isr_handler			//modified_by_msa_to_meet_the_atmega32_constrains
		;.extern pushbutton_timer_isr_handler	//modified_by_msa_to_meet_the_atmega32_constrains


        .text

;/*$PAGE*/
;********************************************************************************************************
;                                           SYSTEM TICK ISR
;
; Description : This function is the Tick ISR.
;
;               The following C-like pseudo-code describe the operation being performed in the code below.
;
;               - Save all registers on the current task's stack:
;                      Use the PUSH_ALL macro
;               - OSIntNesting++;
;               if (OSIntNesting == 1) {
;                  OSTCBCur->OSTCBStkPtr = SP
;               }
;               Clear the interrupt;                  Not needed for the timer we used.
;               OSTimeTick();                         Notify uC/OS-II that a tick has occured
;               OSIntExit();                          Notify uC/OS-II about end of ISR
;               Restore all registers that were save on the current task's stack:
;                      Use the POP_ALL macro to restore the remaining registers
;               Return from interrupt
;********************************************************************************************************

               
TickISR:       
		PUSH_ALL                                                ; Save all registers and status register        	
		LDS     R16,OSIntNesting                                ; Notify uC/OS-II of ISR
        INC     R16                                             ;
        STS     OSIntNesting,R16                                ;

        CPI     R16,1                                           ; if (OSIntNesting == 1) {
        BRNE    TickISR_1

        SAVE_SP				                                    ; X = SP 		
		LDS     R28,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R29,OSTCBCur+1                                  ;    
        
		ST      Y+,R26
        ST      Y+,R27                                          ; }

TickISR_1:
        CALL    OSTimeTick                                  	; Handle the tick ISR

        CALL    OSIntExit                                       ; Notify uC/OS-II about end of ISR
        		
        POP_ALL                                                 ; Restore all registers
        
        RETI

;/*$PAGE*/
;**********************************************************************************************
;*                                       USARTC0 Rx ISR
;*
;* Description: This function is invoked when USARTC0 receives a character
;*
;* Arguments  : none
;*
;* Note(s)    : 1) Pseudo code:
;*                 Disable Interrupts
;*                 Save all registers
;*                 OSIntNesting++
;*                 if (OSIntNesting == 1) {
;*                     OSTCBCur->OSTCBStkPtr = SP
;*                 }
;*                 usartc0_rx_isr_handler();
;*                 OSIntExit();
;*                 Restore all registers
;*                 Return from interrupt;
;**********************************************************************************************
 /*       	//modified_by_msa_to_meet_the_atmega32_constrains
usartc0_rx_isr:        
        PUSH_ALL                                                ; Save all registers and status register        

        LDS     R16,OSIntNesting                                ; Notify uC/OS-II of ISR
        INC     R16                                             ;
        STS     OSIntNesting,R16                                ;

        CPI     R16,1                                           ; if (OSIntNesting == 1) {
        BRNE    usartc0_rx_isr_1

        SAVE_SP				                                    ; X = SP 		
		LDS     R28,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R29,OSTCBCur+1                                  ;    
        
		ST      Y+,R26
        ST      Y+,R27                                          ; }


usartc0_rx_isr_1:
        CALL    usartc0_rx_isr_handler                          ; Call Handler written in C

        CALL    OSIntExit                                       ; Notify uC/OS-II about end of ISR

        LDS     R26,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R27,OSTCBCur+1                                  ;                         X = Y = SP
        
        POP_ALL                                                 ; Restore all registers
        
		RETI
		*/
;/*$PAGE*/
;**********************************************************************************************
;*                                       USARTF0 Rx ISR
;*
;* Description: This function is invoked when USARTF0 receives a character
;*
;* Arguments  : none
;*
;* Note(s)    : 1) Pseudo code:
;*                 Disable Interrupts
;*                 Save all registers
;*                 OSIntNesting++
;*                 if (OSIntNesting == 1) {
;*                     OSTCBCur->OSTCBStkPtr = SP
;*                 }
;*                 usartf0_rx_isr_handler();
;*                 OSIntExit();
;*                 Restore all registers
;*                 Return from interrupt;
;**********************************************************************************************
 /*       	//modified_by_msa_to_meet_the_atmega32_constrains
usartf0_rx_isr:        
        PUSH_ALL                                                ; Save all registers and status register        

        LDS     R16,OSIntNesting                                ; Notify uC/OS-II of ISR
        INC     R16                                             ;
        STS     OSIntNesting,R16                                ;

        CPI     R16,1                                           ; if (OSIntNesting == 1) {
        BRNE    usartf0_rx_isr_1

        SAVE_SP				                                    ; X = SP 		
		LDS     R28,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R29,OSTCBCur+1                                  ;    
        
		ST      Y+,R26
        ST      Y+,R27                                          ; }


usartf0_rx_isr_1:
        CALL    usartf0_rx_isr_handler                          ; Call Handler written in C

        CALL    OSIntExit                                       ; Notify uC/OS-II about end of ISR

        LDS     R26,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R27,OSTCBCur+1                                  ;                         X = Y = SP
        
        POP_ALL                                                 ; Restore all registers
        
		RETI
		*/
;**********************************************************************************************
;*                                       Push-Button Timer ISR
;*
;* Description: This function is called every 20ms and reads the state of the PORTF push-buttons.
;*
;* Arguments  : none
;*
;* Note(s)    : 1) Pseudo code:
;*                 Disable Interrupts
;*                 Save all registers
;*                 OSIntNesting++
;*                 if (OSIntNesting == 1) {
;*                     OSTCBCur->OSTCBStkPtr = SP
;*                 }
;*                 pushbutton_timer_isr_handler();
;*                 OSIntExit();
;*                 Restore all registers
;*                 Return from interrupt;
;**********************************************************************************************
/*        	//modified_by_msa_to_meet_the_atmega32_constrains
pushbutton_timer_isr:        
        PUSH_ALL                                                ; Save all registers and status register        

        LDS     R16,OSIntNesting                                ; Notify uC/OS-II of ISR
        INC     R16                                             ;
        STS     OSIntNesting,R16                                ;

        CPI     R16,1                                           ; if (OSIntNesting == 1) {
        BRNE    pushbutton_timer_isr_1

        SAVE_SP				                                    ; X = SP 		
		LDS     R28,OSTCBCur                                    ; OSTCBCur->OSTCBStkPtr = X
        LDS     R29,OSTCBCur+1                                  ;    
        
		ST      Y+,R26
        ST      Y+,R27                                          ; }


pushbutton_timer_isr_1:
        CALL    pushbutton_timer_isr_handler                    ; Call Handler written in C

        CALL    OSIntExit                                       ; Notify uC/OS-II about end of ISR

        LDS     R26,OSTCBCur                                    ;     OSTCBCur->OSTCBStkPtr = X
        LDS     R27,OSTCBCur+1                                  ;                         X = Y = SP
        
        POP_ALL                                                 ; Restore all registers
        
		RETI*/