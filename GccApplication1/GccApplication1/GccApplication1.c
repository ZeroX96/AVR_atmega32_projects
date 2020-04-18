/*
 * GccApplication1.c
 *
 * Created: 11/20/2016 8:13:09 PM
 *  Author: MABAKCH-AYRIM
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <LCD4Bit.h>
#define output_r PORTD
#define input_c PIND>>4
#define key_dir DDRD

unsigned char get_key()
{
	char i;
	while(1){
		for (i=1;i<=8;i=i<<1)
		{
			output_r=i;
			_delay_ms(5); 
		if (i==1)
			{
				switch (input_c)
				{
					case 1:
					return '1';
					case 2:
					return '2';
					case 4:
					return '3';
				}
			}
		else if (i==2)
			{
				switch (input_c)
				{
					case 1:
					return '4';
					case 2:
					return '5';
					case 4:
					return '6';
				}
			}
		else if (i==4)
				{
					switch (input_c)
					{
						case 1:
						return '7';
						case 2:
						return '8';
						case 4:
						lcd_print("next mode!");
						return '9';
					}
			}
		}
	}
} */
void wait()
{
while(input_c>0);	
}

uint16_t adc_result[4];
void adc_init()
{
	DDRA=0;
	ADCSRA =0x87;
	ADMUX =0xe0;
	
}
uint16_t ReadADC(uint8_t ch)
{
	//Select ADC Channel ch must be 0-7
	ch=ch&0b00000111;
	ADMUX|=(1<<ADLAR);
	ADMUX&=0b11100000;
	ADMUX|=ch;

	//Start Single conversion
	ADCSRA|=(1<<ADSC);

	//Wait for conversion to complete

	while(!(ADCSRA & (1<<ADIF)));
	
	ADCSRA|=(1<<ADIF);

	return(ADCH);
}
void ConvertionToString(void)  //7
{
	
	adc_result[0]=ReadADC(0);        // Read Analog value from channel-0
	adc_result[1]=ReadADC(1);        // Read Analog value from channel-1
	adc_result[2]=ReadADC(2);        // Read Analog value from channel-2
	adc_result[3]=ReadADC(3);
	
	uint16_t IRL[4];
	itoa(adc_result[0],IRL,10);
	lcd_gotoxy(9,1);
	lcd_print(IRL);
	lcd_print(" ");
	
	uint16_t IRC[4];
	itoa(adc_result[1],IRC,10);
	lcd_gotoxy(11,1);
	lcd_print(IRC);
	lcd_print(" ");
	
	uint16_t IRR[4];
	itoa(adc_result[2],IRR,10);
	lcd_gotoxy(3,2);
	lcd_print(IRR);
	lcd_print(" ");
	
	uint16_t LDR[4];
	itoa(adc_result[3],LDR,10);
	lcd_gotoxy(11,2);
	lcd_print(LDR);
	lcd_print(" ");
	}	
	/*
	void password()
	{char counter=0;
		if (get_key()==8)
		{   char pass[3]={'1','4','7'};
			while(1)
			{if (get_key()==pass[0])
			{
				if (get_key()==pass[1])
				{
					if (get_key()==pass[2])
					{
						lcd_print("right password");
					} 
					else
					{ lcd_print("wrong password sir!");
						counter++;
						if (counter<=3)
						{password();
						}
						else
						{
							lcd_print("wait 5 seconds");
							_delay_ms(5000);
							
						}
					}
				} 
				else
				{
					 lcd_print("wrong password sir!");
					 counter++;
					 if (counter<=3)
					 {password();
					 }
					 else
					 {
						 lcd_print("wait 5 seconds");
						 _delay_ms(5000);
						 
					 }
				}
			} 
			else
			{ lcd_print("wrong password sir!");
				counter++;
				if (counter<=3)
				{password();
				}
				else
				{
					lcd_print("wait 5 seconds");
					_delay_ms(5000);
					
				}
				
				
			}
				
			}
		}
	}*/
int main(void)
{
	lcd_init();
	unsigned char data;
	//adc_init();
	key_dir=0x0F;
	
	
    while(1)
    {
		lcd_gotoxy(0,1);
		lcd_print("thanks for yor efforts ");//_delay_ms(1000);
		lcd_gotoxy(0,2);
		lcd_print("eng:mohamed said");
		_delay_ms(2000);
			/*lcd_gotoxy(0,1);
			lcd_print("HI OMAR I MISS U");
			lcd_gotoxy(0,1);
			lcd_print("temp is ");
			_delay_ms(2000);
		
		ConvertionToString();
		lcd_gotoxy(12,1);
		lcddata('c');
		_delay_ms(500);*/
		//lcddata(get_key());
	//	_delay_ms(1000);
		//wait();
		//password();*/
		
		
		
		
		
		
    }
}