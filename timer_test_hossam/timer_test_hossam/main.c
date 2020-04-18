/*
 * timer_test_hossam.c
 *
 * Created: 13/07/2018 14:34:00
 * Author : Mahmoud
 */ 

#define F_CPU 1000000  //one mega HZ
#include <avr/io.h>
#include <util/delay.h>  //so can use the _delay_ms()

//the next four ways do the same function but in different ways as i promised U :D 

//a way for setting the I.O :D >>Uncomment and test :D 
/*
#define port_set(reg,pin) (reg|=(1<<pin))
#define port_clear(reg,pin) (reg&=~(1<<pin))

int main(void)
{
	port_set(DDRA,0)	;//will be converted in the preprocessing to DDRA|=(1<<0)  THAT LEAVES ALL THE DATA in DDRA and puts one in the first bit "bit 0"
						;//putting one in the reg will make it an output pin
	port_clear(DDRA,1)	;//will be converted in the preprocessing to DDRA&=~(1<<1)  which equal to ddra=ddra&(1111 1101) ==>will clear the second bit
						 //THAT LEAVES ALL THE DATA in DDRA and puts zero in the second bit "bit 1"
						;//putting zero in the reg will make it an input pin
	//since i cleared the second bit then it's good to activate the pull-up res so will use that's inside the cpu or put it in the hardware circuit as found in protues's file :D 
	port_set(PORTA,1);//activate the internal pull-up res
					 ;//since the pull-up res is activated then there will be a HIGH till i press the button so goes to low that's why i tests for ZERO in the IF func
	while(1)
	{
		if ( (PINA&(1<<1)) == 0)//if the button is pressed 
		{
			port_set(PORTA,0);//ON the LED
			_delay_ms(30);
		}
		port_clear(PORTA,0);//OFF the LED
	}
						
	return 0;
}*/

//a second way for setting the I.O :D >>Uncomment and test :D
/*int main(void)
{
	DDRA |=(1<<0);//make the first pin output
	DDRA &=~(1<<1);//make the second pin input
	PORTA |=(1<<1);//enable the pull-up res
	while(1)
	{
		if ( (PINA&(1<<1)) == 0)//if the button is pressed
		{
			PORTA |=(1<<0);//ON the LED
			_delay_ms(30);//to debounce the button...it's our new task :P hhhhh
		}
		PORTA &=~(1<<0);//OFF the LED
	}
	
	return 0;
	}
*/

//a third way for setting the I.O :D >>Uncomment and test :D
/*int main(void)
{
	DDRA |=0x01;				//make the first pin output
	DDRA &=0b11111101;			//== 0xfd  //make the second pin input
	PORTA =0x02;				//enable the pull-up res
	while(1)
	{
		if ( (PINA&(1<<1)) == 0)//if the button is pressed
		{
			PORTA |=0b00000001; //== 0x01  //ON the LED
			_delay_ms(30);		//to debounce the button...it's our new task :P hhhhh
		}
		PORTA &=0b11111110;		//== 0xfe  //OFF the LED
	}
	
	return 0;
}*/

//a fourth way for setting the I.O :D >>Uncomment and test :D
/* typedef struct 
 {
	 unsigned int bit_0:1;
	 unsigned int bit_1:1;
	 unsigned int bit_2:1;
	 unsigned int bit_3:1;
	 unsigned int bit_4:1;
	 unsigned int bit_5:1;
	 unsigned int bit_6:1;
	 unsigned int bit_7:1;
	 
 }bits;
 
 //just used X in the next three lines as PORTA/DDRA/PINA are already defined #include <avr/io.h>
 #define PORTX	(*(bits *)0x3B)  //0x3B is the address of the register PORTA from the data sheet !!note!!
 #define DDRX	(*(bits *)0x3A)  //0x3A is the address of the register DDRA from the data sheet  !!note!!
 #define PINX	(*(bits *)0x39)  //0x39 is the address of the register PINA from the data sheet  !!note!!
 
int main(void)
{
	DDRX.bit_0=1;
	DDRX.bit_1=0;
	PORTX.bit_1=1;//enable the internal pull-up resistor
	while(1)
	{
		if(PINX.bit_1 == 0)
		{
			PORTX.bit_0=1;
			_delay_ms(30);
		}
		PORTX.bit_0=0;
	}
	
	return 0;
}*/
 
//the code that enabled the timer on wave generation mode >>Uncomment and test :D

int main(void)
{	
	TCCR0 |=(1<<WGM00)|(1<<WGM01)|(1<<CS00)|(1<<COM01);
	OCR0=150;
	DDRB|=(1<<3);
    while (1) 
    {
		//PORTB=0x00;
		
    }
}

