/*
 * ultra_sonic.h
 *
 * Created: 9/20/2015 8:58:08 PM
 *  Author: Yahia
 * This driver is written to any AVR micro controller that supports timer0,timer1 and timer2 of atmega family
 * F_CPU should be 1 MHZ so that the timer works correctly ,but if you don't set it to this value
 * just add more prescaler in ultrasonic.c file or doing a time conversion in the equation of the distance
 *	distance=g_NumberOfTicks/58; where g_NumberOfTicks must be in (us)
 */ 


#ifndef ULTRA_SONIC_H_
#define ULTRA_SONIC_H_

#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"


#define Trig_DDR DDRB
#define Trig_PORT PORTB
#define Trig_BIT PB0

#define Echo_DDR DDRB
#define Echo_PIN PINB
#define Echo_BIT PB1

/*a delay between showing the result to lcd*/
#define ULTRA_SONIC_READING_DELAY() _delay_ms(300)
/*Replace with TimerN you want*/
#define TimerNumber Timer0

uint8 ultraSonic_distanceInCm();

#endif /* ULTRA_SONIC_H_ */