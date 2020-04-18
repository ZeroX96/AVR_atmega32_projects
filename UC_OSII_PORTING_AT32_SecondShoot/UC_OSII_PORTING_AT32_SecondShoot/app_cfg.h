/*
*************************************************************************************************************
*                                APPLICATION SPECIFIC  CONFIGURATION FILE
*
*                                (c) Copyright 2005, Micrium, Weston, FL
*                                          All Rights Reserved
*
* File : APP_CFG.H
* By   : Jean J. Labrosse
*************************************************************************************************************
*/

/*
**************************************************************************************************************
*                                               STACK SIZES
**************************************************************************************************************
*/

#define  OS_TASK_START_STK_SIZE          240
#define  OS_TASK_START_STK_SIZE_HARD      64

#define  OS_TASK_START_STK_SIZE          240
#define  OS_TASK_START_STK_SIZE_HARD      64

#define  OS_TASK_1_STK_SIZE              240
#define  OS_TASK_1_STK_SIZE_HARD          64

#define  OS_TASK_2_STK_SIZE              240
#define  OS_TASK_2_STK_SIZE_HARD          64

#define  OS_VIEW_TASK_STK_SIZE           200
#define  OS_VIEW_TASK_STK_SIZE_HARD       64

#define  OS_TASK_TMR_STK_SIZE            240
#define  OS_TASK_TMR_STK_SIZE_HARD        64

#define  OS_TASK_STAT_STK_SIZE           240
#define  OS_TASK_STAT_STK_SIZE_HARD       64

#define  OS_TASK_IDLE_STK_SIZE           240
#define  OS_TASK_IDLE_STK_SIZE_HARD       64

/*
**************************************************************************************************************
*                                             TASK PRIORITIES
**************************************************************************************************************
*/

#define  OS_TASK_START_PRIO                0

#define  OS_TASK_1_PRIO                    1
#define  OS_TASK_2_PRIO                    2

#define  OS_VIEW_TASK_PRIO                 3
#define  OS_VIEW_TASK_ID                   3

#define  OS_TASK_TMR_PRIO                  4

/*       OS_TASK_STAT_PRIO       OS_LOWEST_PRIO - 1                                                         */
/*       OS_TASK_IDLE_PRIO       OS_LOWEST_PRIO                                                             */

/*
**************************************************************************************************************
*                                                uC/OS-View
**************************************************************************************************************
*/

#define  OS_VIEW_PARSE_TASK                1   /* Received packet will be service by ISR (0) or Task (1)    */
#define  OS_VIEW_TMR_32_BITS               0   /* The AVR uses a 16-bit timer                               */

#define  OS_VIEW_COMM_0                    0
#define  OS_VIEW_COMM_1                    1
#define  OS_VIEW_COMM_2                    2
#define  OS_VIEW_COMM_3                    3

#define  OS_VIEW_COMM_SEL     OS_VIEW_COMM_0   /* Determine which USART we will use for uC/OS-View          */


#define  OS_VIEW_TMR_1                     1
#define  OS_VIEW_TMR_3                     3
#define  OS_VIEW_TMR_4                     4
#define  OS_VIEW_TMR_5                     5

#define  OS_VIEW_TMR_SEL       OS_VIEW_TMR_1   /* Determine which timer will be used for uC/OS-View         */
