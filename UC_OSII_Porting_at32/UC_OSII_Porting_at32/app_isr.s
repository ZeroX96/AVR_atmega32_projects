/*
 * app_isr.s
 *
 * Created: 02/11/2018 12:52:22
 *  Author: Mahmoud
 */ 
;********************************************************************************************************
;                                       APPLICATION SPECIFIC ISRs
;
;                                (c) Copyright 2005, Micrium, Weston, FL
;                                          All Rights Reserved
;
; File     : APP_ISR.S90
; By       : Jean J. Labrosse
;********************************************************************************************************


                NAME    app_isr

                RSEG    CSTACK:DATA:NOROOT(0)
                RSEG    RSTACK:DATA:NOROOT(0)

#include        <os_cpu_i.s>
                
;********************************************************************************************************
;                                         EXTERNAL DECLARATIONS
;********************************************************************************************************

                EXTERN  OSIntExit
                EXTERN  OSIntNesting
                EXTERN  OSTCBCur
                
                EXTERN  BSP_TickISR_Handler

;********************************************************************************************************
;                                          PUBLIC DECLARATIONS
;********************************************************************************************************

                PUBLIC  BSP_TickISR


;/*$PAGE*/
;********************************************************************************************************
;                                           SYSTEM TICK ISR
;
; Description : This function is the Tick ISR.
;
;               The following C-like pseudo-code describe the operation being performed in the code below.
;
;               Save all registers on the current task's stack:
;                      Use the PUSH_ALL macro
;                      Get the SREG, set Bit #7 and save onto the task's stack using -Y addressing
;                      Use the PUSH_SP macro to save the task's hardware stack pointer onto the current task's stack
;               OSIntNesting++;
;               if (OSIntNesting == 1) {
;                  OSTCBCur->OSTCBStkPtr = SP
;               }
;               Clear the interrupt;                  Not needed for the timer we used.
;               OSTimeTick();                         Notify uC/OS-II that a tick has occured
;               OSIntExit();                          Notify uC/OS-II about end of ISR
;               Restore all registers that were save on the current task's stack:
;                      Use the POP_SP macro to restore the task's hardware stack pointer
;                      Use the POP_SREG macro to restore the SREG register
;                      Use the POP_ALL macro to restore the remaining registers
;               Return from interrupt
;********************************************************************************************************

                RSEG    CODE:CODE:NOROOT(1)
                
BSP_TickISR:
                PUSH_ALL                            ; Save all registers and status register
                IN      R16,SREG                    ; Save the SREG but with interrupts enabled
                SBR     R16,BIT07                    
                ST      -Y,R16
                PUSH_SP                             ; Save the task's hardware stack pointer onto task's stack

                LDS     R16,OSIntNesting            ; Notify uC/OS-II of ISR
                INC     R16                         ;
                STS     OSIntNesting,R16            ;

                CPI     R16,1                       ; if (OSIntNesting == 1) {
                BRNE    BSP_TickISR_1

                LDS     R30,OSTCBCur                ;     OSTCBCur->OSTCBStkPtr = Y
                LDS     R31,OSTCBCur+1
                ST      Z+,R28
                ST      Z+,R29                      ; }

BSP_TickISR_1:
                CALL    BSP_TickISR_Handler         ; Call tick ISR Handler written in C

                CALL    OSIntExit                   ; Notify uC/OS-II about end of ISR

                POP_SP                              ; Restore the hardware stack pointer from task's stack
                POP_SREG_INT
                POP_ALL                             ; Restore all registers
                RETI

                END
