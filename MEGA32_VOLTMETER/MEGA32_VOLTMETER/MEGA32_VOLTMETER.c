/*
 * MEGA32_VOLTMETER.c
 *
 * Created: 11/19/2016 11:27:19 PM
 *  Author: MABAKCH-AYRIM
 */ 


#include <avr/io.h>
#define V_REF 0X20
#include <util/delay.h>
#include <stdlib.h>
unsigned char READ_ADC(unsigned char input)
{
	ADMUX=input | (V_REF & 0XFF);
	_delay_us(100);
	ADCSRA|=0X40;

	while((ADCSRA & 0X10)==0);
	ADCSRA|=0X10;
	return ADCH;
}
#include <LCD4Bit.h>
int main(void)
{DDRA=0;
	lcd_init();
	float A;
	char str[4];
	ADMUX=V_REF & 0XFF;
	ADCSRA=0X01;
    while(1)
    {
		lcd_print("msa");_delay_ms(1000);
		/*A=READ_ADC(0X00);
		A=A*5/255.0;
		itoa(A,2,str);
		lcd_gotoxy(0,0);
		lcd_print(str);
		*/_delay_ms(1000);
lcd_print("msa          4");
	/*	A=READ_ADC(0X01);
		A=A*5/255.0;
		itoa(A,2,str);
		lcd_gotoxy(0,1);
		lcd_print(str);*/
		_delay_ms(1000);
lcd_print("msa       3");
	/*	A=READ_ADC(0X02);
		A=A*5/255.0;
		itoa(A,2,str);
		lcd_gotoxy(0,2);
		
		
		lcd_print(str);
		*/
		_delay_ms(1000);
lcd_print("msa          2");
		/*A=READ_ADC(0X03);
		A=A*5/255.0;
		itoa(A,2,str);
		lcd_gotoxy(0,3);
		lcd_print(str);*/
		_delay_ms(1000);
lcd_print("msa          1");
    }
}