/*
 * ultra_sonic.c
 *
 * Created: 9/20/2015 8:57:46 PM
 *  Author: Yahia
 */ 
#include "ultra_sonic.h"

#if( (TimerNumber == Timer0) || (TimerNumber == Timer2))
#define TIMER_MAX 255 //8 bits timers
#elif((TimerNumber == Timer1))
#define TIMER_MAX 65535 //16 bits timers
#endif

volatile uint32 g_OverFlowCounter=0;
volatile uint32 g_NumberOfTicks=0;


static inline void TimerInit(void)
{
#if( TimerNumber == Timer0 )
	TCNT0=0; /*Initiate counter register */
	TCCR0=(1<<FOC0)|(1<<CS00); /*Normal mode with no scale */
	TIMSK=(1<<TOIE0);		/*Enable interrupt mode*/
#elif( TimerNumber == Timer1 )
	 TCNT1=0;
	 TCCR1A=0;    /*Normal mode*/                        
	 TCCR1B |= (1<<CS10);              
	 TIMSK |= (1<<TOIE1);
#elif(TimerNumber == Timer2)
	TCNT2=0; /*Initiate counter register */
	TCCR2=(1<<FOC2)|(1<<CS20); /*Normal mode with no scale */
	TIMSK=(1<<TOIE2);		/*Enable interrupt mode*/
#endif 	

	sei(); /*enable global interrupt*/
}

static inline void TimerDisable(void)
{
#if( TimerNumber == Timer0 )
	TCCR0=0; /*No clock source for timer so it will stop*/
#elif( TimerNumber == Timer1 )
	TCCR1B=0;
#elif( TimerNumber == Timer2 )
	TCCR2=0;
#endif
	cli();
}

#if( TimerNumber == Timer0 )
ISR(TIMER0_OVF_vect)
{
	g_OverFlowCounter++; /*Counter reaches its max*/
	TCNT0=0;			/*Reset Counter*/
}
#elif( TimerNumber == Timer1 )
ISR(TIMER1_OVF_vect)
{
	g_OverFlowCounter++; /*Counter reaches its max*/
	TCNT1=0;			/*Reset Counter*/
}
#elif( TimerNumber == Timer2)
ISR(TIMER2_OVF_vect)
{
	g_OverFlowCounter++; /*Counter reaches its max*/
	TCNT2=0;			/*Reset Counter*/
}
#endif

static inline void ultraSonic_Init(void)
{
	CLEAR_BIT(Echo_DDR,Echo_BIT); /*Set echo pin as input to the micro*/
	SET_BIT(Trig_DDR,Trig_BIT);   /*Set trig pin as an output from the micro*/
}

static inline void ultraSonic_trig(void)
{
	/* Trig of SR04 must receive a pulse of high (5V) for at least 10us */
	
	CLEAR_BIT(Trig_PORT,Trig_BIT); /*Reset The Trig pin*/
	_delay_us(2);
	SET_BIT(Trig_PORT,Trig_BIT); /*Output High on the trig pin*/
	_delay_us(12);
	CLEAR_BIT(Trig_PORT,Trig_BIT);
	_delay_us(2);
}



uint8 ultraSonic_distanceInCm()
{
	uint8 distance=0;
	
	ultraSonic_Init();						/*Initiate sensor ports*/
	ultraSonic_trig();						/*Send Trigger signals*/
	
	while(BIT_IS_CLEAR(Echo_PIN,Echo_BIT)); /*Wait until echo comes*/
	
	g_OverFlowCounter=0;					 /*Reset  OverFlowCounter*/
	TimerInit();							 /*Initiate Timer*/
	
	while(BIT_IS_SET(Echo_PIN,Echo_BIT));	 /*Wait until echo goes low*/
	
	TimerDisable();							/*Stop the timer*/
	
	g_NumberOfTicks=g_OverFlowCounter*TIMER_MAX +TCNT0; /*plus the last Counting Number*/
	
	distance=g_NumberOfTicks/58;  			/*As data sheet specifies*/
	
	return distance;
}
