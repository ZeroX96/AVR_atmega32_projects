/*
 * blutooth.c
 *
 * Created: 11/29/2016 4:50:22 PM
 *  Author: MABAKCH-AYRIM
 */ 

#define F_CPU 1000000
#include <avr/io.h>
unsigned char GOT=0;
#include <util/delay.h>
//#include <LCD4Bit.h>
void blutooth_init()
{
	//UCSRB=0X10;
	UCSRB|=(1<<TXEN)|(1<<RXEN);
	UCSRC=0X86;
	UBRRL=0x33;	
	
}

void BT_SEND(unsigned char GO)
{
	while(!(UCSRA&(1<<UDRE)));
	UDR=GO;
}

void BT_SEND_words(char *data)
{
	while(*data>0)
	BT_SEND(*data++);
	BT_SEND('\0');
}

unsigned char BT_RECIEVED()
{
	unsigned char CH;
	while(!(UCSRA&(1<<RXC)));
	CH=UDR;
	return CH;
}

void BT_RECIEVED_words()
{
	char i=0;
	unsigned char *arr;
	while(BT_RECIEVED()!='Q'){
	arr[i]=BT_RECIEVED();
	i++; }
	;
	
}


int main(void)
{
	DDRA=0xff;
	blutooth_init();
   //BT_SEND_words("put your words to be printed on lcd");
    while(1)
    {
		unsigned char ch;
		char F='F';
		PORTA=0xFF;
		_delay_ms(100);
		ch=BT_RECIEVED();
		if (ch==F)
		{	BT_SEND('1');
			
			PORTA=0x00;
			//_delay_ms(1000);
		}
	//BT_SEND_words("msa ");
		//BT_RECIEVED_words();
		
    }
}