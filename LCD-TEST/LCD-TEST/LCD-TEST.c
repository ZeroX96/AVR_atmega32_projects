/*
 * LCD_TEST.c
 *
 * Created: 11/10/2016 5:40:31 AM
 *  Author: MABAKCH-AYRIM
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#define lcd_dprt PORTC
#define lcd_dddr DDRC
#define lcd_dpin PINC
#define lcd_rs 0
#define lcd_rw 1
#define lcd_en 2

void lcdcommand(unsigned char cmd)
{
	lcd_dprt = (lcd_dprt&0x0f)|(cmd&0xf0);
	lcd_dprt &=~(1<<lcd_rs);
	lcd_dprt &=~(1<<lcd_rw);
	lcd_dprt |=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt &=~(1<<lcd_en);
	_delay_us(100);
	lcd_dprt = (lcd_dprt&0x0f)|(cmd<<4);
	lcd_dprt|=(1<<lcd_en);
	_delay_us(1);
	lcd_dprt &=~(1<<lcd_en);
	_delay_us(100);
}
void lcddata(unsigned char data)
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
void lcd_init()
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
	lcdcommand(0x0f);
	_delay_us(100);
	lcdcommand(0x01);
	_delay_us(2000);
	lcdcommand(0x06);
	_delay_us(100);
	

}
void lcd_gotoxy (unsigned char x,unsigned char y)
{
	unsigned char firstcharadr[]={0x80,0xc0,0x94,0xd4};
	lcdcommand(firstcharadr[y-1]+x-1);
	_delay_us(100);
}
void lcd_print(char*str)
{
	unsigned char i=0;
	while(str[i]!=0)
	{
		lcddata(str[i]);
		i++;
	}
}
int main()
{
	lcd_init();
	while(1)
	{
		lcd_print("mahmoud");
	}
	return 0;
} 