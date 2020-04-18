/*
 * M32C_LED_MATRIX.c
 *
 * Created: 14/04/2018 02:03:53
 * Author : Mahmoud Saad ZeroX86
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>

#define DELAY 1500
#define UP PORTC
#define  DWN PORTA  
int main(void)
{
	DDRC=0xff;
	DDRA=0xff;
	long long int var1=1,var2=1;
    while (1) 
    {
	    
	    var1++;
		if(var1 == 0)
		var2++;
		
	    UP  = 0b00011000;//////////////
	    DWN = 0b01111111;
	    _delay_us(DELAY);
	    UP  = 0b00100100;///////////////
	    DWN = 0b10111111;
	    
		
		_delay_us(DELAY);
	    UP  = 0b01000010;//////////////
	    DWN = 0b11011111;
	    _delay_us(DELAY);
		
		
	    UP  = 0b00001000;//////////////
	    DWN = 0b11101111;
	    _delay_us(DELAY);
	    UP  = 0b10010010;//////////////
	    DWN = 0b11110111;
	    _delay_us(DELAY);
	    UP  = 0b01111100;//////////////
	    DWN = 0b11111011;
	    _delay_us(DELAY);
	    UP  = 0b00010000;//////////////
	    DWN = 0b11111101;
	    _delay_us(DELAY);
	    UP  = 0b00111000;//////////////
	    DWN = 0b11111110;
	    _delay_us(DELAY);
    }
}


    //UP  = 0b00011000;//////////////
    //DWN = 0b01111111;
    //_delay_us(DELAY);
    //UP  = 0b00100100;///////////////
    //DWN = 0b10111111;
    //_delay_us(DELAY);
    //UP  = 0b01000010;//////////////
    //DWN = 0b11011111;
    //_delay_us(DELAY);
    //UP  = 0b00011000;//////////////
    //DWN = 0b11101111;
    //_delay_us(DELAY);
    //UP  = 0b00011000;//////////////
    //DWN = 0b11110111;
    //_delay_us(DELAY);
    //UP  = 0b00100100;//////////////
    //DWN = 0b11111011;
    //_delay_us(DELAY);
    //UP  = 0b01100110;//////////////
    //DWN = 0b11111101;
    //_delay_us(DELAY);
    //UP  = 0b01100110;//////////////
    //DWN = 0b11111110;
    //_delay_us(DELAY);