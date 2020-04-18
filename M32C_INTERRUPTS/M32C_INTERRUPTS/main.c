/*
 * M32C_INTERRUPTS.c
 *
 * Created: 12/04/2018 21:57:48
 * Author : Mahmoud
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
/*
int main()
{
	
	
	
	return 0;
}
*/


/*
int main ()
{
	DDRC=0x00;
	DDRD=0xff;
	
	TCNT0=0xaa;
	TCNT1L=0xff;
	TCNT1H=0x55;
	TCCR0=0x01;
	TCCR1A=0x00;
	TCCR1B=0x01;
	DDRB |= (1<<1)|(1<<7);
	TIMSK |=(1<<TOIE0)|(1<<TOIE1);
	sei();
	while (1)
	{
		PORTD=PINC;
	}
	

ISR(TIMER0_OVF_vect)
{
	TCNT0=0xaa;
	PORTB ^=(1<<1);
	
}

ISR (TIMER1_OVF_vect)
{
	TCCR1A=0x00;
	TCCR1B=0x01;
	PORTB ^= (1<<7);
}
	return 0;
}
*/



int main(void)
{
	DDRC=0xff;
	//DDRD=0x00;
	DDRA=0xff;
	PORTD=0xff;
	TCNT0=0x55;
	TCCR0=(1<<0)|(1<<1); 
	TIMSK=(1<<TOIE0);   
	GICR=(1<<INT0);
	sei();

    while (1) 
    {
		
		PORTA^=0x1;
    }
}



ISR(TIMER0_OVF_vect)
{
	TCNT0=0x55;
	PORTB ^=(1<<5);
	_delay_ms(500);
}

ISR(INT0_vect)
{
	sei();
	PORTA ^= (1<<4);
}