/*
 * TEST_ROBOT_MS.c
 *
 * Created: 11/19/2016 10:52:32 PM
 *  Author: MABAKCH-AYRIM
 */ 
#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>



#define left 0
#define center 1
#define right 2
#define _LDR 3

#define lcd_dprt PORTB
#define lcd_dddr DDRB
#define lcd_dpin PINB
#define lcd_rs 0
#define lcd_rw 1
#define lcd_en 2


// Function declaring prototyping
void ADC_Init();
uint16_t ReadADC(uint8_t ch);
void ConvertionToString(void);
void lcdcommand(unsigned char cmnd);
void lcddata(unsigned char data);
void lcd_init(void);
void lcd_gotoxy (unsigned char x,unsigned char y);
void lcd_print(char*str); // Function declaring prototyping


uint16_t adc_result[4]; //Array

int main(void)
{
	DDRA=0XF0;
	
	DDRD=0XFF;
	
	
	ADC_Init();
	
	lcd_init();
	_delay_ms(2);
	lcd_gotoxy(1,1);
	lcd_print("L:");
	lcd_gotoxy(9,1);
	lcd_print("C:");
	lcd_gotoxy(1,2);
	lcd_print("R:");
	lcd_gotoxy(9,2);
	lcd_print("D:");
	
	
	
	
	while(1)
	{
		
		ConvertionToString();
		
		
		if(adc_result[center]>=(55))
		{
		
			
			while((adc_result[left] >=(750)) || (adc_result[center]>=(55)))
			{
				
				ConvertionToString();
				
			}
			
			
			
		}
		
		
		else if(adc_result[right] >= (850))
		{

		
			while(adc_result[right]>=(850))
			{
				
				ConvertionToString();
				
			}

			
			
			
		}



		else if(adc_result[left] >= (750))
		{
			

		
			while(adc_result[left]>=(750))
			{
				
				//Read Sensor Values

				ConvertionToString();
				
			}

			

		}
		
		_delay_ms(2);
		
	}
	
	return 0;
	
}

/****************************************/

void ADC_Init()  //4
{
	ADMUX=0X42;
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);//prescalar div factor = 128
	
}


uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX&=0b11100000;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete

	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA|=(1<<ADIF);

	return(ADC);
}


void ConvertionToString(void)  //7
{
	uint16_t X=0;
	adc_result[0]=ReadADC(0);        // Read Analog value from channel-0
	adc_result[1]=ReadADC(1);        // Read Analog value from channel-1
	adc_result[2]=ReadADC(2);        // Read Analog value from channel-2
	adc_result[3]=ReadADC(3);
	
	uint16_t IRL[4];
	X=adc_result[0];
	X=X*5/255;
	itoa(X,IRL,10);
	lcd_gotoxy(3,1);
	lcd_print(IRL);
	lcd_print(" ");
	
	uint16_t IRC[4];
	X=adc_result[1];
	X=X*5/255;
	itoa(X,IRC,10);
	lcd_gotoxy(11,1);
	lcd_print(IRC);
	lcd_print(" ");
	
	uint16_t IRR[4];
	X=adc_result[2];
	X=X*5/255;
	itoa(X,IRR,10);
	lcd_gotoxy(3,2);
	lcd_print(IRR);
	lcd_print(" ");
	
	uint16_t LDR[4];
	X=adc_result[0];
	X=X*5/255;
	itoa(X,LDR,10);
	lcd_gotoxy(11,2);
	lcd_print(LDR);
	lcd_print(" ");
	
}


void lcdcommand(unsigned char cmnd)  //8
{
	lcd_dprt = (lcd_dprt&0x0f)|(cmnd&0xf0);
	lcd_dprt &=~(1<<lcd_rs);
	lcd_dprt &=~(1<<lcd_rw);
	lcd_dprt |=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt &=~(1<<lcd_en);
	_delay_us(100);
	lcd_dprt = (lcd_dprt&0x0f)|(cmnd<<4);
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt &=~(1<<lcd_en);
	_delay_us(100);
}
void lcddata(unsigned char data)  //9
{
	lcd_dprt=(lcd_dprt&0x0f)|(data &0xf0);
	lcd_dprt|=(1<<lcd_rs);
	lcd_dprt&=~(1<<lcd_rw);
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	lcd_dprt=(lcd_dprt&0x0f)|(data<<4);
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	_delay_us(100);
}


void lcd_init(void)  //10
{
	lcd_dddr=0xff;
	lcd_dprt&=~(1<<lcd_en);
	_delay_us(2000);
	lcdcommand(0x33);
	_delay_us(100);
	lcdcommand(0x32);
	_delay_us(100);
	lcdcommand(0x28);
	_delay_us(100);
	lcdcommand(0x01);
	_delay_us(2000);
	lcdcommand(0x06);
	lcdcommand(0x0c);
}


void lcd_gotoxy (unsigned char x,unsigned char y)  //11
{
	unsigned char firstcharadr[]={0x80,0xc0,0x94,0xd4};
	lcdcommand(firstcharadr[y-1]+x-1);
	_delay_us(100);
}


void lcd_print(char*str)  //12
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		lcddata(str[i]);
		i++;
	}
}