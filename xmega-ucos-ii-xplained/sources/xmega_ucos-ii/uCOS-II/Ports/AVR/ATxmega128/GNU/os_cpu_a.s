;*
;*********************************************************************************************************
;*                                               uC/OS-II
;                                         The Real-Time Kernel
;*                                          uC/OS-II PORT FILE
;*
;*                          (c) Copyright 2004-2008; Micrium, Inc.; Weston, FL
;*
;*               All rights reserved.  Protected by international copyright laws.
;*
;*               uC/CPU is provided in source form for FREE evaluation, for educational
;*               use or peaceful research.  If you plan on using uC/CPU in a commercial
;*               product you need to contact Micrium to properly license its use in your
;*               product.  We provide ALL the source code for your convenience and to
;*               help you experience uC/CPU.  The fact that the source code is provided
;*               does NOT mean that you can use it without paying a licensing fee.
;*
;*               Knowledge of the source code may NOT be used to develop a similar product.
;*
;*               Please help us continue to provide the Embedded community with the finest
;*               software available.  Your honesty is greatly appreciated.
;*********************************************************************************************************
;*/

;********************************************************************************************************
;                                               uC/OS-II
;                                         The Real-Time Kernel
;
;                                       ATXmega128A1  Specific code
;                                             GNU AVR Compiler
;
;
; Filename       : os_cpu_a.s
; Version        : V1.20
; Programmer(s)  : FK
;                : FT
;                : [with modifications by Nick D'Ademo]
;********************************************************************************************************

#include  <os_cpu_i.h>

;********************************************************************************************************
;                                         PUBLIC DECLARATIONS
;********************************************************************************************************

		.global OS_CPU_SR_Save
		.global OS_CPU_SR_Restore
		.global OSStartHighRdy
		.global OSCtxSw
		.global OSIntCtxSw


;********************************************************************************************************
;                                         EXTERNAL DECLARATIONS
;********************************************************************************************************

		.extern OSTaskSwHook
		.extern OSRunning
		.extern OSTCBHighRdy
		.extern OSTCBCur
		.extern OSPrioHighRdy


		.text

;/*$PAGE*/
;********************************************************************************************************
;                            DISABLE/ENABLE INTERRUPTS USING OS_CRITICAL_METHOD #3
;
; Description : These functions are used to disable and enable interrupts using OS_CRITICAL_METHOD #3.
;
;               OS_CPU_SR  OSCPUSaveSR (void)
;                     Get current value of SREG
;                     Disable interrupts
;                     Return original value of SREG
;
;               void  OSCPURestoreSR (OS_CPU_SR cpu_sr)
;                     Set SREG to cpu_sr
;                     Return
;********************************************************************************************************

OS_CPU_SR_Save:
        IN      R24,SREG                                        ; Get current state of interrupts disable flag
        CLI                                                     ; Disable interrupts
        RET                                                     ; Return original SREG value in R24


OS_CPU_SR_Restore:
        OUT     SREG,R24                                        ; Restore SREG
        RET                                                     ; Return

;/*$PAGE*/
;********************************************************************************************************
;                               START HIGHEST PRIORITY TASK READY-TO-RUN
;
; Description : This function is called by OSStart() to start the highest priority task that was created
;               by your application before calling OSStart().
;
; Note(s)     : 1) The (data)stack frame is assumed to look as follows:
;                                                +======+
;                  OSTCBHighRdy->OSTCBStkPtr --> |RAMPZ |
;                                                |RAMPY |
;                                                |RAMPX |
;                                                |RAMPD |
;                                                |EIND  |
;                                                |R31   |
;                                                |R30   |
;                                                |R27   |
;                                                |.     |
;                                                |SREG  |
;                                                |R0    |
;                                                |PCH   |-|
;                                                |PCM   | |--> PC address (3 bytes)                     
;                                                |PCL   |-|                         (High memory)
;                                                +======+
;                  where the stack pointer points to the task start address.
;
;
;               2) OSStartHighRdy() MUST:
;                      a) Call OSTaskSwHook() then,
;                      b) Set OSRunning to TRUE,
;                      c) Switch to the highest priority task.
;********************************************************************************************************

OSStartHighRdy:
        CALL    OSTaskSwHook                                    ; Invoke user defined context switch hook

        LDS     R16,OSRunning                                   ; Indicate that we are multitasking
        INC     R16                                             ;
        STS     OSRunning,R16                                   ;

        LDS     R26,OSTCBHighRdy                                ; Let X point to TCB of highest priority task
        LDS     R27,OSTCBHighRdy+1                              ; ready to run

        RESTORE_SP                                              ; SP = MEM[X];	
        POP_ALL                                                 ; Restore all registers
        RETI                                                    ; Start task


;/*$PAGE*/
;********************************************************************************************************
;                                       TASK LEVEL CONTEXT SWITCH
;
; Description : This function is called when a task makes a higher priority task ready-to-run.
;
; Note(s)     : (1) (A) Upon entry,
;                       OSTCBCur     points to the OS_TCB of the task to suspend
;                       OSTCBHighRdy points to the OS_TCB of the task to resume
;
;                   (B) The stack frame of the task to suspend looks as follows:
; 
;                                            SP+0 --> LSB of task code address
;                                              +2     MSB of task code address            (High memory)
;
;                   (C) The saved context of the task to resume looks as follows:
;
;                                                      +======+
;                        OSTCBHighRdy->OSTCBStkPtr --> |SPL   | ->stack pointer           (Low memory)                                             
;                                                      |SPH   | 
;                                                      |RAMPZ |
;                                                      |RAMPY |
;                                                      |RAMPX |
;                                                      |RAMPD |
;                                                      |EIND  |
;                                                      |R31   |
;                                                      |R30   |
;                                                      |R27   |
;                                                      |.     |
;                                                      |SREG  |
;                                                      |R0    |
;                                                      |PCH   |-|
;                                                      |PCM   | |--> PC address (3 bytes)                     
;                                                      |PCL   |-|                          (High memory)
;                                                      +======+
;                 (2) The OSCtxSW() MUST:
;                     - Save all register in the current task task. 
;                     - Make OSTCBCur->OSTCBStkPtr = SP.                     
;                     - Call user defined task swith hook.
;                     - OSPrioCur                  = OSPrioHighRdy
;                     - OSTCBCur                   = OSTCBHihgRdy 
;                     - SP                         = OSTCBHighRdy->OSTCBStrkPtr
;                     - Pop all the register from the new stack
;********************************************************************************************************

OSCtxSw:
        PUSH_ALL                                                ; Save current task's context   				
		      
		IN      R26,  SPL                                       ; X = SP
		IN      R27,  SPH                                       ;              
		
		LDS     R28,OSTCBCur                                    ; Y = OSTCBCur->OSTCBStkPtr
        LDS     R29,OSTCBCur+1                                  ;        		
        ST      Y+,R26                                          ; Y = SP
        ST      Y+,R27                                          ;

        CALL    OSTaskSwHook                                    ; Call user defined task switch hook

        LDS     R16,OSPrioHighRdy                               ; OSPrioCur = OSPrioHighRdy
        STS     OSPrioCur,R16

        LDS     R26,OSTCBHighRdy                                ; Let X point to TCB of highest priority task
        LDS     R27,OSTCBHighRdy+1                              ; ready to run
        STS     OSTCBCur,R26                                    ; OSTCBCur = OSTCBHighRdy
        STS     OSTCBCur+1,R27                                  
     
	    RESTORE_SP                                              ; SP = MEM[X];						        
		POP_ALL
		RET


;/*$PAGE*/
;*********************************************************************************************************
;                                INTERRUPT LEVEL CONTEXT SWITCH
;
; Description : This function is called by OSIntExit() to perform a context switch to a task that has
;               been made ready-to-run by an ISR.
;
; Note(s)     : 1) Upon entry,
;                  OSTCBCur     points to the OS_TCB of the task to suspend
;                  OSTCBHighRdy points to the OS_TCB of the task to resume
;
;               2) The stack frame of the task to suspend looks as follows:
;
;                  OSTCBCur->OSTCBStkPtr ------> SPL of (return) stack pointer           (Low memory)
;                                                SPH of (return) stack pointer
;                                                Flags to load in status register
;                                                RAMPZ
;                                                R31
;                                                R30
;                                                R27
;                                                .
;                                                .
;                                                R0
;                                                PCH
;                                                PCL                                     (High memory)
;
;               3) The saved context of the task to resume looks as follows:
;
;                  OSTCBHighRdy->OSTCBStkPtr --> SPL of (return) stack pointer           (Low memory)
;                                                SPH of (return) stack pointer
;                                                Flags to load in status register
;                                                RAMPZ
;                                                R31
;                                                R30
;                                                R27
;                                                .
;                                                .
;                                                R0
;                                                PCH
;                                                PCL                                     (High memory)
;*********************************************************************************************************

OSIntCtxSw:
        CALL    OSTaskSwHook                                    ; Call user defined task switch hook

        LDS     R16,OSPrioHighRdy                               ; OSPrioCur = OSPrioHighRdy
        STS     OSPrioCur,R16                                   ;

        LDS     R26,OSTCBHighRdy                                ; X = OSTCBHighRdy->OSTCBStkPtr
        LDS     R27,OSTCBHighRdy+1                              ;
        STS     OSTCBCur,R26                                    ; OSTCBCur = OSTCBHighRdy
        STS     OSTCBCur+1,R27                                  ;

        RESTORE_SP                                              ; SP = MEM[X];					     
		POP_ALL                                                 ; Restore all registers
        RETI

