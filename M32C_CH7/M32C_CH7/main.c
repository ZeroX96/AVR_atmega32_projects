/*
 * M32C_CH7.c
 *
 * Created: 20/03/2018 07:14:53
 * Author : Mahmoud Saad
 */ 

//clock init
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
//avr lib and delay
#include <avr/io.h>
#include <util/delay.h>

//#define ON  0xff
//#define OFF 0x00
//#define UP  PORTA
//#define DWN PORTD
//a function takes digits and returns their 7seg representation 
//char bcd_seg(int in);
//void smile(int time_wanted_in_seconds);

//defined delay for portability
//#define DELAY_MS(x) (_delay_ms(x))

//s-reg flags


//bit defines
////#define pb0 0
////#define pb1 1
////#define pb2 2
////#define pb3 3
////#define pb4 4
////#define pb5 5
////#define pb6 6
////#define pb7 7

int main(void)
{	/*
	//char BCD_packed[10]={0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39};
	//DDRA =0xff;
	//DDRA&=~((1<<pb3)|(1<<pb4)|(1<<pb6));//clear pb3,pb4&pb6
	 //unsigned char ARR[10]={-4,-3,-2,-1,0,1,2,3,4,5};
	//unsigned char i=0;
	//PORTA=0xff;
    //DDRA=0xff;
	//PORTB=0xff;  //pull up res enable
	//DDRB=0xff;
	
	//A structure  for bit manipulation
	*/
	/*
	typedef struct  
	{
		unsigned int pb0:1;
		unsigned int pb1:1;
		unsigned int pb2:1;
		unsigned int pb3:1;
		unsigned int pb4:1;
		unsigned int pb5:1;
		unsigned int pb6:1;
		unsigned int pb7:1;
	}bits;
	
	//using the structure
	//#define PORTX (*(bits*) (&PORTA))
	//#define PINX (*(bits*) (&PINB))
	*/
/*
	DDRC&=~(1<<3);
	unsigned char str=0x00;
	for(int i=0;i<8;i++)
	{
		if(PINC & (1<<3))
		str|=(1<<7);
		else if(PINC & (1<<3))
		str&=~(1<<7);
		str>>=1;
		_delay_ms(1000);
	}
*/

//DDRC|=(1<<3);
//while(1)
//{
	//PORTC|=(1<<3);//0x08&0x08
	//_delay_ms(1000);
	//PORTC&=~(1<<3);//0x08&0x08
	//_delay_ms(1000);
//}

//sends a byte serially,one bit at a time via pinC3 & MSB goes first	
	//unsigned char storage=0x44;  //0b01000100
	//unsigned char temp =storage;
	//unsigned char x=0;
	//DDRC|=(1<<3);
	//
	//for(x=0;x<8;x++)
	//{
		//if(temp &(1<<7))
		//PORTC|=(1<<3);
		//else if(!(temp & (1<<7)))
		//PORTC&=~(1<<3);
		//temp<<=1;
		//_delay_ms(1000);
	//}
	
	
	//sends a byte serially,one bit at a time via pinA0 & LSB goes first
	//unsigned char storage=0x44;
	//for(char i=0;i<=8;i++)
	//{
		//if(storage & (1<<0))
			//PORTA|=(1<<0);
		//else
			//PORTA &=~(1<<0);
		//storage >>=1;
		//_delay_ms(1000); 
		//
		 //
	//}
	
	
	while (1)
    {
		
		
		
		/*
		//packed to ascii conversion
		-------
		//unsigned char src=0x56;
		//unsigned char fuk=src;
		//fuk>>=4;
		//PORTA=fuk|0x30;
		//PORTB=(src&(0x0f))|0x30;
		
		//unsigned char src='5'; //0b 0011 0101
		//unsigned char fuk='9'; //0b 0011 1001
		//
		//src&=0x0f;
		//fuk&=0x0f;
		//fuk<<=4;
		//src|=fuk;
		//PORTA=src;  //0b 1001 0101
		
		//PORTA=0xff;
		//DELAY_MS(1000);
		//PORTA =~ PORTA;
		//DELAY_MS(1000);
		//if (!(PINX.pb0) && !(PINX.pb1))
		//{
			//PORTA='0';
		//} 
		//else if ((PINX.pb0) && !(PINX.pb1))
		//{
			//PORTA='1';
		//}
		//else if (!(PINX.pb0) && (PINX.pb1))
		//{
			//PORTA='2';
		//}
		//else if ((PINX.pb0) && (PINX.pb1))
	//{
		//PORTA='3';
	//}
		
		
	    //PORTA|=((1<<1)|(1<<3)|(1<<5));DELAY_MS(1000);
	    //PORTA&=~((1<<1)|(1<<3)|(1<<5));DELAY_MS(1000);
		//PORTA=PINB;
		//PORTX.pb2=PINX.pb1;
		//if((PINB &(1<<1)))
		//PORTA=(PINB &(1<<1));
		//else
		//PORTA=(PINB &(1<<1));
		//PORTX.pb3=1 ;
		//DELAY_MS(1000);
		//PORTX.pb5=1;
		//DELAY_MS(1000);
		//PORTX.pb7=1;
		//DELAY_MS(1000);
		//PORTX.pb3&=~(PORTX.pb3);
		//DELAY_MS(1000);
		//PORTX.pb5&=~(PORTX.pb5);
		//DELAY_MS(1000);
		//PORTX.pb7&=~(PORTX.pb7);
		//DELAY_MS(1000);
		//PORTX.pb3&=~(1);
		//DELAY_MS(1000);
		//PORTX.pb5&=~(1);
		//DELAY_MS(1000);
		//PORTX.pb7&=~(1);
		//DELAY_MS(1000);
		
		//wrong
		//PORTX.pb0&=~(PINB&(1<<1)); 
		//DELAY_MS(1000);
		
		
		//for(i=0;i<10;i++)
		//{
			//PORTA=0xff;
			////DELAY_MS(1000);
		//}
		
		*/
	}
	
		
	return 0;
}


		/*
		smile(4);
		PORTD=0x00;
		PORTA=0x00;
		_delay_ms(1000);*/	
		
//void smile(int time_wanted_in_seconds)
	/*{
		#define DELAY 1500
		time_wanted_in_seconds =(int)(time_wanted_in_seconds/((float)DELAY/((float)1000000)));
		for(;time_wanted_in_seconds >0;time_wanted_in_seconds--)
		{
			UP  = 0b00011000;//////////////
			DWN = 0b01111111;
			_delay_us(DELAY);
			UP  = 0b00100100;///////////////
			DWN = 0b10111111;
			_delay_us(DELAY);
			UP  = 0b01000010;//////////////
			DWN = 0b11011111;
			_delay_us(DELAY);
			UP  = 0b00011000;//////////////
			DWN = 0b11101111;
			_delay_us(DELAY);
			UP  = 0b00011000;//////////////
			DWN = 0b11110111;
			_delay_us(DELAY);
			UP  = 0b00100100;//////////////
			DWN = 0b11111011;
			_delay_us(DELAY);
			UP  = 0b01100110;//////////////
			DWN = 0b11111101;
			_delay_us(DELAY);
			UP  = 0b01100110;//////////////
			DWN = 0b11111110;
			_delay_us(DELAY);
		}
		//return 0;
	}*/
	
//char bcd_seg(int in)
/*{

		if (in == 0)
		{
			return 0X3F;
		}
		else if(in == 1)
		{
			return 0X06;
		}
		else if(in == 2)
		{
			return 0X5B;
		}
		else if(in == 3)
		{
			return 0X4F;
		}
		else if(in == 4)
		{
			return 0X66;
		}
		else if(in == 5)
		{
			return 0X6D;
		}
		else if(in == 6)
		{
			return 0X7D;
		}
		else if(in == 7)
		{
			return 0X07;
		}
		else if(in == 8)
		{
			return 0X7F;
		}
		else
		{
			return 0X6F;
		}
}*/