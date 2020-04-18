/*
 * beg.c
 *
 * Created: 11/29/2016 7:26:39 PM
 *  Author: MABAKCH-AYRIM
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	//DDRC=0B11111111;//AHMED
	DDRA=0B11111111;
    while(1)
    {PORTA=0XFF;
		_delay_ms(500);
		PORTA=0x00;
		_delay_ms(500);
		
	}
}