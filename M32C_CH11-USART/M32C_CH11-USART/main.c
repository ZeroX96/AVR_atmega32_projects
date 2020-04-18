/*
 * M32C_CH11-USART.c
 *
 * Created: 23/04/2018 05:19:04
 * Author : Mahmoud
 */ 

#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>

//the adc
void adc_init(void)
{
	DDRA=0x00; // 3<<5   0110 0000<<5  10000000
	ADCSRA=(1<<ADEN)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2); // 0b10000111; 1000 0111
	ADMUX=(1<<REFS0)|(1<<ADLAR);
}
//#define uint8_t unsigned int
uint8_t adc_read(uint8_t channle)
{
	//ch = 0b 0000 0001
	channle &= 0b00000111;
	ADMUX   &= 0b11111000;
	ADMUX   |=channle;
	ADCSRA  |=(1<<ADSC);
	while(!(ADCSRA &(1<<ADIF)));
	return ADCH; 
}

//the usart
void usart_init (void )
{
	UCSRB=(1<<TXEN)|(1<<RXEN);
	UCSRC=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL=0x33; //9600 @ 8mhz
}
void usart_send(unsigned char ch)
{
	while (!(UCSRA &(1<<UDRE)))
	;
	UDR=ch;
}
void usart_send_arr(uint8_t *val)
{
	unsigned char i=0;
	for (i=0;val[i] ;i++)
	{
		usart_send(val[i]);
	}
	//usart_send('\n');
	
}
unsigned char usart_recve(void){
	static unsigned char temp;
	while(!(UCSRA & (1<<RXC)))
	;
	temp=UDR;
	return temp;
}

//motors commands
void frwrd(void )
{
	PORTB=0b10000101;
}
void bkwrd(void )
{
	PORTB=0b10001010;
}
void lft(void )
{
	PORTB=0b10001001;
}
void rit(void )
{
	PORTB=0b10000110;
}
void stp()
{
	PORTB=0b00000000;
	PORTB=0xf0;
}
void led1()
{
	PORTB=0b11100000;
}
void led2()
{
	PORTB=0b11010000;
}
void led3()
{
	PORTB=0b10110000;
}
void Beeb()
{
	PORTB=0b01110000;
	
}


//  the ultrasonic
static volatile int pulse = 0;  // integer  to access all though the program
static volatile int i = 0;      // integer  to access all though the program
			// storing digital output
uint8_t read_ultra_sonic(void) //0000 0011
{
			static uint8_t COUNTA = 0;
			PORTC |=(1<<0);
			_delay_us(15);		//triggering the sensor for 15usec
			PORTC &=~(1<<0);
			COUNTA = pulse/58;	//getting the distance based on formula on introduction
			return COUNTA;
}
void send_usonic(uint16_t COUNTA)
{
			
			char SHOWA [3];			// displaying digital output as it's sent as ascii
			itoa(COUNTA,SHOWA,10);
			usart_send_arr(SHOWA);
			
}

int main(void)
{
	adc_init();
	usart_init();
	DDRA=0x00;
	DDRB=0xff;
	PORTB=0b11110000;
	DDRC=0xff;
	unsigned char temp;
	//ultrasonic
	DDRD &=~(1<<2);      //setting the interrupt pin as an input
		_delay_ms(50);
		GICR|=(1<<INT0);//|(1<<INT1);     //enabling interrupt0
		MCUCR|=(1<<ISC00);   //setting interrupt triggering logic change
		sei();               //enabling global interrupts
		

    while (1) 
    {
	    usart_send_arr("Hi,i'm the BLACK KNIGHT :D \n");
	    usart_send_arr("please choose the mode,1=control,2=autonomous \n");
		temp=usart_recve();
		
		if (temp == '1')
		{
			usart_send_arr("note...to quit send q\n");
			while(temp != 'q')
			{
				temp=usart_recve();
				if(temp == 'w')
				{
					frwrd();
					//usart_send_arr("up");
					
				}
				else if (temp == 's')
				{
					bkwrd();
					//usart_send_arr("dn");
				}
				else if (temp == 'a')
				{
					lft();
					//usart_send_arr("lt");
				}
				else if (temp == 'd')
				{
					rit();
					//usart_send_arr("rt");
				}
				else if (temp == 'o')
				{
					stp();
					//usart_send_arr("off");
				}
				else if (temp == 'b')
				{
					Beeb();
					//usart_send_arr("beeb");
				}
				else if (temp == 'z')
				{
					led1();
					//usart_send_arr("red led is on!");
				}
				else if (temp == 'x')
				{
					led2();
					//usart_send_arr("green led is on!");
				}
				else if (temp == 'c')
				{
					led3();
					//usart_send_arr("blue led is on!");
				}
			}
		}
		else if(temp == '2')
		{
			usart_send_arr("note...to quit send q\n");
			static uint8_t usonic;
			static uint8_t rit_sensor;
			static uint8_t lft_sensor;
			while(temp != 'q')
			{
				
				usonic=read_ultra_sonic();
				usonic=read_ultra_sonic();
				rit_sensor =adc_read(0);
				lft_sensor =adc_read(1);
				if (usonic >= 15)
				{
						frwrd();
						usart_send_arr("up ");
						_delay_ms(60);
						usonic=read_ultra_sonic();
					
				}
				else 
				{
					rit();
					_delay_ms(15);
					usonic=read_ultra_sonic();
				
					/*
					if ( (rit_sensor-8) << (lft_sensor-150) )
					{
						rit();
						_delay_ms(100);
					} 
					else
					{
						
						lft();
						_delay_ms(100);
					}*/
					//stp();
					//usart_send_arr("below the wanted\n ");
				}
				/*char SHOWA [3];			// displaying digital output as it's sent as ascii
				
				itoa(usonic,SHOWA,10);
				usart_send_arr("usonic data = ");
				usart_send_arr(SHOWA);
				usart_send_arr("    ");
				
				itoa(rit_sensor,SHOWA,10);
				usart_send_arr("rit_sensor data = ");
				usart_send_arr(SHOWA);
				usart_send_arr("    ");
				itoa(lft_sensor,SHOWA,10);
				usart_send_arr("lft_sensor data = ");
				usart_send_arr(SHOWA);
				usart_send_arr("    ");
				
				char a=usart_recve();*/
				
				}
			
		}
		else
		{
			usart_send_arr("i said 1=control,2=autonomous not ");
			usart_send(temp);
			usart_send(' ');
		}
	
	}
}


ISR(INT0_vect)//interrupt service routine when there is a change in logic level
{

	if (i==1)//when logic from HIGH to LOW

	{

		TCCR1B=0;//disabling counter

		pulse=TCNT1;//count memory is updated to integer

		TCNT1=0;//resetting the counter memory

		i=0;

	}

	  if (i==0)//when logic change from LOW to HIGH

	{

		TCCR1B|=(1<<CS10);//enabling counter

		i=1;

	}

}