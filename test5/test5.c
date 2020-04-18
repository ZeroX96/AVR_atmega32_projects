/*
 * ADC_MEGA32_READY.c
 *
 * Created: 11/20/2016 3:45:00 PM
 *  Author: MABAKCH-AYRIM
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <LCD4Bit.h>

void ADC_select(char select/*,char ref*/)
{DDRA=0;
	if (select==8)
	{
		ADCSRA|=(1<<ADEN);
		ADMUX|=(1<<ADLAR);//then will take data from ADCH only!!!
		ADMUX|=(1<<REFS0);ADMUX&=~(1<<REFS1);//selecting the ref. to be avref
		ADCSRA|=(1<<ADEN)|(1<<ADSC);//enabling the chip and starting the convertion
		//ADCSRA|=(1<<ADATE);//auto triger 
		ADCSRA|=(1<<ADIF);//enabling complete conversion flag
		ADCSRA|=(1<<ADPS0)|(1<<ADPS1);ADCSRA&=~(1<<ADPS2);//prescaler by osc/8 as im using 1 mega internal crystal
		
	} 
	else if (select==10)
	{
	}
		
}


int main(void)
{unsigned char data=0;
	DDRC=0xff;
	ADC_select(8);
    while(1)
    {
		
		while((ADCSRA & ADIF)==0);
		ADCSRA|=(1<<ADIF);
		data=ADCH;
		data=(data*5/255);
		lcd_print(data);
		_delay_ms(1000);
      lcd_print("ya rab");
    }
}
