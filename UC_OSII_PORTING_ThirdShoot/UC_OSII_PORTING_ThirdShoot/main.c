/*
 * UC_OSII_PORTING_ThirdShoot.c
 *
 * Created: 03/11/2018 17:51:40
 * Author : Mahmoud
 */ 

#include <avr/io.h>

#include <includes.h>

/*
*********************************************************************************************************
*                                              GLOBAL VARIABLES
*********************************************************************************************************
*/
static OS_STK TaskStartStk[APP_CFG_TASK_START_STK_SIZE];
static OS_STK TaskStk[APP_CFG_N_TASKS][APP_CFG_TASK_STK_SIZE];

volatile INT8U buttonState;
bool show_cpu_usage=true;

// USARTC0 Receiver buffer
#define USARTC0_RX_BUFFER_SIZE_BYTES 512
char rx_buffer_usartc0[USARTC0_RX_BUFFER_SIZE_BYTES];
unsigned int rx_wr_index_usartc0=0,rx_rd_index_usartc0=0;
volatile unsigned int rx_counter_usartc0=0;
volatile bool rx_buffer_overflow_usartc0=false;

// USARTF0 Receiver buffer
#define USARTF0_RX_BUFFER_SIZE_BYTES 512
char rx_buffer_usartf0[USARTF0_RX_BUFFER_SIZE_BYTES];
unsigned int rx_wr_index_usartf0=0,rx_rd_index_usartf0=0;
volatile unsigned int rx_counter_usartf0=0;
volatile bool rx_buffer_overflow_usartf0=false;

// Semaphore declarations
OS_EVENT *usartc0_rx;
OS_EVENT *usartf0_rx;
OS_EVENT *pushbutton_event;

/*
*********************************************************************************************************
*                                            FUNCTION PROTOTYPES
*********************************************************************************************************
*/
static void TaskStart(void *p_arg);
void TaskStartCreateTasks(void);
void AVRInit(void);
void PortsInit(void);
void SystemClocksInit(void);
void USARTC0Init(void);
void USARTF0Init(void);
void PushButtonTimerInit(void);
void tc0_disable(TC0_t *ptc);
void tc1_disable(TC1_t *ptc);
void ClockTickStart(void);

#if PRINT_TO_USART == C0
char getchar_usartc0(void);
int usartc0_putchar(char c, FILE *stream);
#elif PRINT_TO_USART == F0
char getchar_usartf0(void);
int usartf0_putchar(char c, FILE *stream);
#endif

/*
*********************************************************************************************************
*                                                   MAIN
*********************************************************************************************************
*/

// Set the standard output stream
#if PRINT_TO_USART == C0
static FILE mystdout = FDEV_SETUP_STREAM(usartc0_putchar, NULL, _FDEV_SETUP_WRITE);
#elif PRINT_TO_USART == F0
static FILE mystdout = FDEV_SETUP_STREAM(usartf0_putchar, NULL, _FDEV_SETUP_WRITE);
#endif

int main(void)
{
	// Redefine standard output stream
	stdout=&mystdout;
	// Initialize AVR
	AVRInit();
	// Initialize uC/OS-II
	OSInit();
	// Create the start task
	OSTaskCreateExt((void (*)(void *)) TaskStart,
	(void           *) 0,
	(OS_STK         *)&TaskStartStk[APP_CFG_TASK_START_STK_SIZE - 1],
	(INT8U           ) APP_CFG_TASK_START_PRIO,
	(INT16U          ) APP_CFG_TASK_START_PRIO,
	(OS_STK         *)&TaskStartStk[0],
	(INT32U          )(APP_CFG_TASK_START_STK_SIZE),
	(void           *) 0,
	(INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
	// Create semaphores
	usartc0_rx=OSSemCreate(0);
	usartf0_rx=OSSemCreate(0);
	pushbutton_event=OSSemCreate(0);
	// Start multi-tasking
	OSStart();
	return 0;
}
