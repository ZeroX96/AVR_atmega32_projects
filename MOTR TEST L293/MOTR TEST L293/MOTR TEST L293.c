/*
 * MOTR_TEST_L293.c
 *
 * Created: 12/21/2016 6:21:18 PM
 *  Author: MABAKCH-AYRIM
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{DDRA=0XFF;
	PORTA=0XFF;
    while(1)
    {
        PORTA=0b01010101;
		_delay_ms(5000);
		PORTA=0b01010100;
		_delay_ms(5000);
		PORTA=0b01010110;
		_delay_ms(5000);
    }
}