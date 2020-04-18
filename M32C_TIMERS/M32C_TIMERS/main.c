/*
 * M32C_TIMERS.c
 *
 * Created: 06/04/2018 23:57:23
 * Author : Mahmoud Saad ZeroX86
 */ 

#include <avr/io.h>


int main(void)
{
	DDRA=0xff;
	
    
    while (1) 
    {
		PORTA=0xff;
		TCNT0=0x00;
		TCCR0=0x1;
		while(!(TIFR&(1<<TOV0)));
		TCCR0=0;
		TCCR0=(1<<TOV0);
		PORTA=0x00;
		TCNT0=0x00;
		TCCR0=0x1;
		while(!(TIFR&(1<<TOV0)));
		TCCR0=0;
		TIFR=(1<<TOV0);
	}
}

