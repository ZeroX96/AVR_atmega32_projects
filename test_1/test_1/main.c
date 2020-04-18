/*
 * test_1.c
 *
 * Created: 17/04/2018 14:35:49
 * Author : Mahmoud
 */ 

#include <avr/io.h>
#include <util/delay.h>
//#define portx (char (char *) 0x05)
int main(void)
{
	DDRA=0xff; //0b 1111 1111
    //DDRD=0x00;
    /* Replace with your application code */
	
    while (1) 
    {
		
		PORTA=0x01;  //0b 0000 0001  
		_delay_ms(1000);
		PORTA=0x02;  //  0b 0000 0010  
		_delay_ms(1000);
		//_delay_us(6..)
    }
}

