/*
 * tess.c
 *
 * Created: 11/30/2016 3:18:53 PM
 *  Author: MABAKCH-AYRIM
 */ 




#include <avr/io.h>
#define F_CPU 1000000UL
				#include <util/delay.h>
				#define lcd_dprt PORTC
				#define lcd_dddr DDRC
				#define lcd_dpin PINC
uint16_t adc_res[4]; //Array
#define lcd_rs 0
#define lcd_rw 1
#define lcd_en 2
#include <math.h>
#define V_REF 0X20

//LCD CODING

void LCD_COMM (unsigned char cmd)
{
	//DDRB=0xff;
	lcd_dprt=(lcd_dprt & 0x0F) | (cmd & 0xF0);//sending first 4bits
	lcd_dprt&=~(1<<lcd_rs);
	lcd_dprt&=~(1<<lcd_rw);
	
	//sending a high to low pulse as said in data sheet
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	
	_delay_us(100);
	
	
	lcd_dprt=(lcd_dprt & 0x0F) | (cmd<<4);//sending 2nd 4bits
	
	//sending a high to low pulse as said in data sheet
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	_delay_us(100);
}

void LCD_DATA_CHAR (unsigned char data)
{
	lcd_dprt=(lcd_dprt & 0x0F) | (data & 0xF0);//sending first 4bits
	lcd_dprt|=(1<<lcd_rs);
	lcd_dprt&=~(1<<lcd_rw);
	
	//sending a high to low pulse as said in data sheet
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	lcd_dprt=(lcd_dprt & 0x0F) | (data<<4);//sending 2nd 4bits
	
	//sending a high to low pulse as said in data sheet
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt&=~(1<<lcd_en);
	_delay_us(100);
	
	
}

void LCD_DATA_ARR(char *data)
{
	unsigned char i=0;
	while (data[i] !=0)
	{
		LCD_DATA_CHAR(data[i]);
		i++;
		//_delay_ms(50);
	}
	
	
}

void lcd_pos (unsigned char x,unsigned char y)
{
	unsigned char position[]={0x80,0xc0,0x94,0xd4};
	LCD_COMM(position[y-1]+(x-1));
	_delay_ms(10);

}

void LCD_INIT ()
{
	lcd_dddr=0xFF; //setting lcd port output so can write on the lcd
	lcd_dprt&=~(1<<lcd_en);
	_delay_us(2000);          //WAIT FOR LCD GETTING READY
	LCD_COMM(0x33);          //setting the lcd in 4bit mode
	_delay_us(100);            //wait as said in data sheet
	LCD_COMM(0x32);          //setting the lcd in 4bit mode
	_delay_us(100);            //wait as said in data sheet
	LCD_COMM(0x28);          //setting the lcd in 4bit mode
	_delay_us(100);            //wait as said in data sheet
	LCD_COMM(0x0E);          //powering up the lcd
	_delay_us(100);            //wait as said in data sheet
	LCD_COMM(0x01);          //clearing the lcd
	_delay_ms(2000);            //wait as said in data sheet
	LCD_COMM(0x06);          //powering up the lcd
	_delay_us(100);            //wait as said in data sheet
	
}

int main(void)
{
LCD_INIT();
    while(1)
    {
		lcd_pos(1,1);
		LCD_DATA_ARR("BLACK_HATERS ^_^");
		_delay_ms(500);
		lcd_pos(1,2);
		LCD_DATA_ARR("WE R JUST TRYING!");
		_delay_ms(500);
        //TODO:: Please write your application code 
    }
}