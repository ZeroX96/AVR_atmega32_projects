/*
 * timer_management_unit.c
 *
 * Created: 14/07/2018 11:08:25
 * Author : Mahmoud
 */ 
#define  F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "tmu.h"
#include "common.h"

void pin_toggle1(void)
{
	PORTA|=(1<<0);
	_delay_ms(10);
	PORTA|=(1<<0);
	_delay_ms(10);
}

void pin_toggle2(void)
{
	PORTA|=(1<<1);
	_delay_ms(10);
	PORTA&=~(1<<1);
	_delay_ms(10);
}


int main(void)
{
	DDRA=0xff;
	sei();
	timer_object obj1;
	timer_object obj2;
	tmu_init(3);
	tmu_start_timer(&obj1,pin_toggle1,2,periodic_en);
    while (1) 
    {
		tmu_dispatch();
    }
}

