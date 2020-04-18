/*
*********************************************************************************************************
*                                           Atmel ATmega128
*                                         Board Support Package
*
*                                (c) Copyright 2005, Micrium, Weston, FL
*                                          All Rights Reserved
*
*
* File : BSP.C
* By   : Jean J. Labrosse
*********************************************************************************************************
*/

#include "includes.h"
//#define CPU_CLK_FREQ 1000000UL
/*
*********************************************************************************************************
*                                              PROTOTYPES
*********************************************************************************************************
*/

static  void  BSP_InitTickISR(void);
static  void  LED_Init(void);

/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    LED_Init();

    BSP_InitTickISR();
}


/*
*********************************************************************************************************
*                                        SETUP THE TICK RATE
*
* Note(s): 1) OCR0 = CPU_CLK_FREQ / (2 * Prescaler * OC_freq) - 1
*          2) The equation actually performs rounding by multiplying by 2, adding 1 and then divising by 2
*             in integer math, this is equivalent to adding 0.5
*********************************************************************************************************
*/

static  void  BSP_InitTickISR (void)
{
    INT32U  num;
    INT32U  denom;


    TCCR0  = 0x0E;                                      /* Set TIMER0 prescaler to CTC Mode, CLK/256   */
    TCNT0  =    0;                                      /* Start TCNT at 0 for a new cycle             */
    num    = (INT32U)CPU_CLK_FREQ;
    denom  = 2 * 256 * (INT32U)OS_TICKS_PER_SEC;
    OCR0   = (INT8U)((2 * num / denom + 1) / 2 - 1);
    TIFR  |= 0x02;                                      /* Clear  TIMER0 compare Interrupt Flag        */
    TIMSK |= 0x02;                                      /* Enable TIMER0 compare Interrupt             */
}


/*
*********************************************************************************************************
*                                     HANDLE THE TICK INTERRUPT
*
* Note(s): 1) No need to clear the interrupt source since we use output compare mode for Timer #0 and
*             the interrupt is automatically cleard in hardware when the ISR runs.
*********************************************************************************************************
*/

void  BSP_TickISR_Handler (void)
{
    OSTimeTick();
}


/*
*********************************************************************************************************
*                                         BSP INITIALIZATION
*
* Description : This function should be called by your application code before you make use of any of the
*               functions found in this module.
*
* Arguments   : none
*********************************************************************************************************
*/

static  void  LED_Init (void)
{
    DDRD  = 0xFF;                                 /* All PORTD pins are outputs                        */
    PORTD = 0xFF;
    LED_Off(0);                                   /* Turn ON all the LEDs                              */
}

/*
*********************************************************************************************************
*                                             LED ON
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to control
*                      0    indicates that you want ALL the LEDs to be ON
*                      1    turns ON LED1 on the board
*                      .
*                      .
*                      8    turns ON LED8 on the board
*********************************************************************************************************
*/

void  LED_On (INT8U led)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0;
#endif


    OS_ENTER_CRITICAL();
    switch (led) {
        case 0:
             PORTD  =  0x00;
             break;

        case 1:
             PORTD &= ~0x01;
             break;

        case 2:
             PORTD &= ~0x02;
             break;

        case 3:
             PORTD &= ~0x04;
             break;

        case 4:
             PORTD &= ~0x08;
             break;

        case 5:
             PORTD &= ~0x10;
             break;

        case 6:
             PORTD &= ~0x20;
             break;

        case 7:
             PORTD &= ~0x40;
             break;

        case 8:
             PORTD &= ~0x80;
             break;
    }
    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                             LED OFF
*
* Description : This function is used to control any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to turn OFF
*                      0    indicates that you want ALL the LEDs to be OFF
*                      1    turns OFF LED1 on the board
*                      .
*                      .
*                      8    turns OFF LED8 on the board
*********************************************************************************************************
*/

void  LED_Off (INT8U led)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0;
#endif


    OS_ENTER_CRITICAL();
    switch (led) {
        case 0:
             PORTD  =  0xFF;
             break;

        case 1:
             PORTD |=  0x01;
             break;

        case 2:
             PORTD |=  0x02;
             break;

        case 3:
             PORTD |=  0x04;
             break;

        case 4:
             PORTD |=  0x08;
             break;

        case 5:
             PORTD |=  0x10;
             break;

        case 6:
             PORTD |=  0x20;
             break;

        case 7:
             PORTD |=  0x40;
             break;

        case 8:
             PORTD |=  0x80;
             break;
    }
    OS_EXIT_CRITICAL();
}

/*
*********************************************************************************************************
*                                        LED TOGGLE
*
* Description : This function is used to toggle the state of any or all the LEDs on the board.
*
* Arguments   : led    is the number of the LED to toggle
*                      0    indicates that you want ALL the LEDs to toggle
*                      1    Toggle LED1 on the board
*                      .
*                      .
*                      8    Toggle LED8 on the board
*********************************************************************************************************
*/

void  LED_Toggle (INT8U led)
{
#if OS_CRITICAL_METHOD == 3                      /* Allocate storage for CPU status register           */
    OS_CPU_SR  cpu_sr = 0;
#endif


    OS_ENTER_CRITICAL();
    switch (led) {
        case 0:
             PORTD ^=  0xFF;
             break;

        case 1:
             PORTD ^=  0x01;
             break;

        case 2:
             PORTD ^=  0x02;
             break;

        case 3:
             PORTD ^=  0x04;
             break;

        case 4:
             PORTD ^=  0x08;
             break;

        case 5:
             PORTD ^=  0x10;
             break;

        case 6:
             PORTD ^=  0x20;
             break;

        case 7:
             PORTD ^=  0x40;
             break;

        case 8:
             PORTD ^=  0x80;
             break;
    }
    OS_EXIT_CRITICAL();
}
