/*
 * M32C_CH13-ADC_DAC.c
 *
 * Created: 29/04/2018 20:10:09
 * Author : Mahmoud
 */ 

#include <avr/io.h>

void adc_init(void)
{
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);
	ADMUX=(1<<REFS0)|(1<<ADLAR);
}

uint8_t adc_read(uint8_t channle)
{
	channle &= 0b00000111;
	ADMUX   &= 0b11111000;
	ADMUX   |=channle;
	ADCSRA  |=(1<<ADSC);
	while(!(ADCSRA &(1<<ADIF)));
	return ADCH;
}

int main(void)
{
	adc_init();
    DDRB=0xff;
	DDRD=0xff;
	DDRA=0x00;
    while (1) 
    {
		uint8_t ch0=adc_read(0);
		uint8_t ch1=adc_read(1);
		PORTB=ch0;
		PORTD=ch1;
    }
}

