/*
*************************************************************************************************************
*                                                uC/OS-II
*                                          The Real-Time Kernel
*
*                                         ATmega128  Sample code
*
* File : APP.C
* By   : Jean J. Labrosse
*************************************************************************************************************
*/

#include  <includes.h>

/*
**************************************************************************************************************
*                                               CONSTANTS
*
* Note(s) : 1) See OS_CFG.H for the default stack size: 'OS_TASK_STK_SIZE'
**************************************************************************************************************
*/


/*
**************************************************************************************************************
*                                               VARIABLES
**************************************************************************************************************
*/

OS_STK  AppTaskStartStk[OS_TASK_START_STK_SIZE];
OS_STK  AppTask1Stk[OS_TASK_1_STK_SIZE];
OS_STK  AppTask2Stk[OS_TASK_2_STK_SIZE];

/*
**************************************************************************************************************
*                                           FUNCTION PROTOTYPES
**************************************************************************************************************
*/

       void  main(void);
       
static void  AppTaskStart(void *p_arg);
static void  AppTaskCreate(void);
static void  AppTask1(void *p_arg);
static void  AppTask2(void *p_arg);

/*
**************************************************************************************************************
*                                                MAIN
*
* Note(s): 1) You SHOULD use OS_TASK_STK_SIZE (see OS_CFG.H) when setting OSTaskStkSize prior to calling 
*             OSInit() because OS_TASK_IDLE_STK_SIZE and OS_TASK_STAT_STK_SIZE are set to this value in
*             OS_CFG.H.
**************************************************************************************************************
*/

void  main (void)
{
#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    INT8U  err;
#endif


    /*---- Any initialization code prior to calling OSInit() goes HERE -------------------------------------*/

                                                     /* IMPORTANT: MUST be setup before calling 'OSInit()'  */
    OSTaskStkSize     = OS_TASK_IDLE_STK_SIZE;       /* Setup the default stack size                        */
    OSTaskStkSizeHard = OS_TASK_IDLE_STK_SIZE_HARD;  /* Setup the default hardware stack size               */

    OSInit();                                        /* Initialize "uC/OS-II, The Real-Time Kernel"         */

    /*---- Any initialization code before starting multitasking --------------------------------------------*/

    OSTaskStkSize     = OS_TASK_START_STK_SIZE;      /* Setup the total stack size                          */
    OSTaskStkSizeHard = OS_TASK_START_STK_SIZE_HARD; /* Setup the hardware stack size                       */
    OSTaskCreateExt(AppTaskStart,
                    (void *)0,
                    (OS_STK *)&AppTaskStartStk[OSTaskStkSize - 1],
                    OS_TASK_START_PRIO,
                    OS_TASK_START_PRIO,
                    (OS_STK *)&AppTaskStartStk[OSTaskStkSizeHard],
                    OSTaskStkSize - OSTaskStkSizeHard,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);

#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_TASK_START_PRIO, "Start Task", &err);
#endif
    /*---- Create any other task you want before we start multitasking -------------------------------------*/

    OSStart();                                       /* Start multitasking (i.e. give control to uC/OS-II)  */
}

/*
**************************************************************************************************************
*                                              STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
**************************************************************************************************************
*/

static void  AppTaskStart (void *p_arg)
{
    INT8U  i;


    (void)p_arg;                                 /* Prevent compiler warnings                          */

    BSP_Init();                                  /* Initialize the BSP                                 */

    AppTaskCreate();

    while (1) {                               /* Task body, always written as an infinite loop.     */
        for (i = 1; i <= 8; i++) {
            LED_On(i);
            OSTimeDly(OS_TICKS_PER_SEC / 10);
            LED_Off(i);
        }
        for (i = 7; i > 1; i--) {
            LED_On(i);
            OSTimeDly(OS_TICKS_PER_SEC / 10);
            LED_Off(i);
        }
    }
}


/*
**************************************************************************************************************
*                                        CREATE APPLICATION TASKS
*
* Description : This function creates the application tasks.
*
* Arguments   : p_arg   is the argument passed to 'AppStartTask()' by 'OSTaskCreate()'.
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
**************************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    INT8U  err;
#endif


    /*---- Task initialization code goes HERE! --------------------------------------------------------*/
    OSTaskStkSize     = OS_TASK_1_STK_SIZE;        /* Setup the default stack size                     */
    OSTaskStkSizeHard = OS_TASK_1_STK_SIZE_HARD;   /* Setup the default hardware stack size            */
    OSTaskCreateExt(AppTask1,
                    (void *)0,
                    (OS_STK *)&AppTask1Stk[OSTaskStkSize - 1],
                    OS_TASK_1_PRIO,
                    OS_TASK_1_PRIO,
                    (OS_STK *)&AppTask1Stk[OSTaskStkSizeHard],
                    OSTaskStkSize - OSTaskStkSizeHard,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_TASK_1_PRIO, "Task 1", &err);
#endif

    OSTaskStkSize     = OS_TASK_2_STK_SIZE;        /* Setup the default stack size                     */
    OSTaskStkSizeHard = OS_TASK_2_STK_SIZE_HARD;   /* Setup the default hardware stack size            */
    OSTaskCreateExt(AppTask2,
                    (void *)0,
                    (OS_STK *)&AppTask2Stk[OSTaskStkSize - 1],
                    OS_TASK_2_PRIO,
                    OS_TASK_2_PRIO,
                    (OS_STK *)&AppTask2Stk[OSTaskStkSizeHard],
                    OSTaskStkSize - OSTaskStkSizeHard,
                    (void *)0,
                    OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
#if (OS_TASK_NAME_SIZE > 14) && (OS_TASK_STAT_EN > 0)
    OSTaskNameSet(OS_TASK_2_PRIO, "Task 2", &err);
#endif
}

/*
**************************************************************************************************************
*                                                   TASK #1
**************************************************************************************************************
*/

static void  AppTask1(void *p_arg)
{
    p_arg = p_arg;
    while (1) {
        LED_Toggle(7);
        OSTimeDly(OS_TICKS_PER_SEC / 5);
    }
}

/*
**************************************************************************************************************
*                                                  TASK #2
**************************************************************************************************************
*/

static void  AppTask2(void *p_arg)
{
    p_arg = p_arg;
    while (1) {
        LED_Toggle(8);
        OSTimeDly(OS_TICKS_PER_SEC / 2);
    }
}
