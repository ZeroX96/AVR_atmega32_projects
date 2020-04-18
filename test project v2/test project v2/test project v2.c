/*
 * test_project_v2.c
 *
 * Created: 12/12/2016 5:48:07 AM
 *  Author: MABAKCH-AYRIM
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>
#define lcd_dprt PORTC
#define lcd_dddr DDRC
#define lcd_dpin PINC
#define lcd_rs 0
#define lcd_rw 1
#define lcd_en 2
#define output_r PORTD
#define input_c PIND>>5
#define key_dir DDRD
char counter=0;
int A=9,B=0,C=5,D=0,E=9,F=0,G=5,H=2,I=2,J=1,K=6,L=1,mode=0;

//lcd////////////////////////////////////////////////////////

void LCD_COMM (unsigned char cmd)
{
	//DDRB=0xff;
	lcd_dprt=(lcd_dprt & 0x0F) | (cmd & 0xF0);//sending firts 4bits
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
	lcd_dprt=(lcd_dprt & 0x0F) | (data & 0xF0);//sending firts 4bits
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

void LCD_POS (unsigned char row,unsigned char colom)
{
	unsigned char position[]={0x80,0xc0,0x94,0xd4};
	LCD_COMM(position[colom-1]+(row-1));
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

//lcd done//////////////////////////////////////////////////

//adc//////////////////////////////////////////////////////
uint16_t adc_result[4];
void adc_init()
{
	DDRA=0X00;
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
	LCD_POS(9,1);
	LCD_DATA_ARR("T=");
	LCD_POS(11,1);
	LCD_DATA_ARR(IRL);
	LCD_DATA_ARR("C");
	
	
	
	uint16_t IRC[4];
	itoa(adc_result[1],IRC,10);
	LCD_POS(1,2);
	LCD_DATA_ARR("GAS RATIO:");
	LCD_POS(13,2);
	LCD_DATA_ARR(IRC);
	LCD_DATA_ARR("%");
	
	uint16_t IRR[4];
	itoa(adc_result[2],IRR,10);
	
	LCD_POS(1,1);
	LCD_DATA_ARR("IR=");
	LCD_POS(4,1);
	LCD_DATA_ARR(IRR);
	LCD_DATA_ARR(" ");
	//LDR
	//uint16_t LDR[4];
	//itoa(adc_result[3],LDR,10);
	/*int LDR=adc_result[3];
	if(LDR>=30)
	{	_delay_ms(10)
		PORTB|=(1<<0);
		_delay_ms(1000);
		return;
	}
	PORTB=0X00;*/
	//LCD_POS(10,2);
	//LCD_DATA_ARR(LDR);
	//LCD_DATA_ARR(" ");
	inc();
}
//adc done////////////////////////////////////////////////

//KEYPAD/////////////////////////////////////////////////
/*
unsigned char get_key()
{	
	key_dir=0B00011110;
	if (counter>=15)
	{
		counter=0;
		LCD_POS(0,2);
	}
		char i;
	while(1){
		for (i=4;i<=32;i=i<<1)
		{
			output_r=i;
			_delay_ms(5);
			if (i==4)
			{
				switch (input_c)
				{
					case 1:
					counter++;wait();return '1';
					case 2:
					counter++;wait();return '2';
					case 4:
					counter++;wait();return '3';
				}
			}
			else if (i==8)
			{
				switch (input_c)
				{
					case 1:
					counter++;wait();return '4';
					case 2:
					counter++;wait();return '5';
					case 4:
					counter++;wait();return '6';
				}
			}
			else if (i==16)
			{
				switch (input_c)
				{
					case 1:
					counter++;wait();return '7';
					case 2:
					counter++;wait();return '8';
					case 4:
				//	lcd_print("next mode!");
					counter++;wait();return '9';
				}
			}
		}
	}
	
	} 
	void wait()
	{
	while(input_c>0);
	}
//KEYPAD DONE////////////////////////////////////////////
*/
void alarm()
{
	
	t_alarm();
	g_alarm();
	ldr_alarm();
	ir_alarm();
	leds();
}

void t_alarm()
{
	
	if((ReadADC(0))>=30)
	{
		PORTB|=(1<<0);
		_delay_ms(250);
		ReadADC(0);//adc_result[0];
		PORTB!=~(1<<0);
		_delay_ms(250);
			ReadADC(0);
	}
	else
	PORTB&=0b11111110;
}
void g_alarm()
{
	
	if((ReadADC(1))>=20)
	{
		PORTB|=(1<<1);
		_delay_ms(250);
		ReadADC(0);//adc_result[0];
		PORTB!=~(1<<1);
		_delay_ms(250);
		ReadADC(0);
	}
	else
	PORTB&=0b11111101;
}
void ldr_alarm()
{
	
	if((ReadADC(2))>=20)
	{
		PORTB|=(1<<2);
		_delay_ms(250);
		ReadADC(0);//adc_result[0];
		PORTB!=~(1<<2);
		_delay_ms(250);
		ReadADC(0);
	}
	else
	PORTB&=0b11111011;
}
void ir_alarm()
{
	
	
	if((ReadADC(3))>=20)
	{
		PORTB|=(1<<3);
		_delay_ms(250);
		ReadADC(0);//adc_result[0];
		PORTB!=~(1<<3);
		_delay_ms(250);
		ReadADC(0);
	}
	else
	PORTB&=0b11110111;
	
}
void ADD()
{
	
	LCD_POS(1,1);
	LCD_DATA_ARR("BLACK_HATERS ^_^");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("WE R JUST TRYING!");
	_delay_ms(1000);
	LCD_COMM(0X01);
	LCD_POS(1,1);
	LCD_DATA_ARR("MADE BY:_        ");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("MAHMOUD SAAD MSA");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("ABDELKADER A.M.E");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("ABD ELTAWAB H.E.");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("EL-SAYED ZEHRY  ");
	_delay_ms(1000);
	LCD_POS(1,2);
	LCD_DATA_ARR("MAHMOUD EHAB  ");
	LCD_POS(1,2);
	LCD_DATA_ARR("Ahmed Gamal   ");
	_delay_ms(1000);
	LCD_COMM(0X01);
}
void leds()
{
	PORTD=0xff;
	_delay_ms(250);
	PORTD=0x00;
	_delay_ms(250);
	
}
//// FUNCTION INPUTTING VALES FROM USERS AND STORING THEM TO AN ARRAY////
	/*
char password(char arr[])
{/* unsigned char i=0,k=0,N[16];
		LCD_COMM(0xc0);
		while(k!='9')
		{
			k=get_key();
			if(k && k!='9')
			{
				N[i++]=k;
				LCD_DATA_CHAR('*');
			}
		}
		strcpy(arr,N);
		arr[i]='\0';
	}

	/////////////////////////
	while(get_key()!='1')
	{	LCD_POS(1,1);
		LCD_DATA_ARR("PUT UR PASS_CODE");
		//new[i]= get_key();LCD_DATA_CHAR('*');
		
	}
	while(get_key()!='2')
	{LCD_POS(1,1);
		LCD_DATA_ARR("PUT UR PASS_CODE");
	}
	while(get_key()!='4')
	{LCD_POS(1,1);
		LCD_DATA_ARR("PUT UR PASS_CODE");
	}
	LCD_DATA_ARR("thx");
	return 1;*/	/*
}*/
	
	void inc()
	{
		A++;
		if(A==10)
		{
			A=0;
			B++;
			//I++;
		}
		_delay_ms(100);
		if (B==6)
		{
			B=0;
			C++;
		}
		_delay_ms(10);
		if (C==10)
		{
			C=0;
			D++;
		}
		_delay_ms(10);
		if (D==6)
		{
			D=0;
			E++;
		}
		_delay_ms(10);
		if (E==10)
		{
			E=0;
			F++;
		}
		_delay_ms(10);
		if (F==6)
		{
			F=0;
			switch (mode){
				case 1:
				mode=0;break;
				case 0:
				mode=1;break;
				G++;
			}
		}
		if (G==10)
		{
			G=0;
			H++;
		}
		if (H==3)
		{
			H=0;
			I++;
		}
		if (I==12)
		{
			I=0;
			J++;
		}
		if (J==10)
		{
			E=0;
			F++;
		}
	}
	void CLOCK()
	{
		
		uint16_t Q[4];
		//LCD_COMM(0X01);
		LCD_POS(1,1);
		LCD_DATA_ARR("CLOCK=");
		if (mode==1)
		{
			LCD_POS(15,1);
			LCD_DATA_ARR("AM");
		}
		else if (mode==0)
		{
			LCD_POS(15,1);
			LCD_DATA_ARR("PM");
		}
		LCD_POS(14,1);
		
		itoa(A,Q,10);
		LCD_DATA_ARR(Q);
		
		
		LCD_POS(13,1);
		itoa(B,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(12,1);
		LCD_DATA_CHAR(':');
		LCD_POS(11,1);
		itoa(C,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(10,1);
		itoa(D,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(9,1);
		
		LCD_DATA_CHAR(':');
		LCD_POS(8,1);
		itoa(E,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(7,1);
		itoa(F,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(1,2);
		LCD_DATA_ARR("DATE=");
		LCD_POS(13,2);
		itoa(G,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(12,2);
		itoa(H,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(11,2);
		LCD_DATA_CHAR(':');
		LCD_POS(10,2);
		itoa(I,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(9,2);
		itoa(J,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(7,2);
		itoa(K,Q,10);
		LCD_DATA_ARR(Q);
		LCD_POS(8,2);
		LCD_DATA_CHAR(':');
		LCD_POS(6,2);
		itoa(L,Q,10);
		LCD_DATA_ARR(Q);
		inc();
	}

int main(void)
{	adc_init();
	LCD_INIT();
	DDRB=0xFF;
	DDRC=0XFF;
	DDRD=0xff;
	ADD();
	
	    while(1)
    {	//PORTB=0X00;
		//CLOCK_DATE();
		//ConvertionToString();
/*	if (get_key()=='1')
    {
		PORTB!=~(1<<0);
    }*/
		
	CLOCK();
	alarm();
	_delay_ms(400);
		//LCD_COMM(0X01);
	CLOCK();
	alarm();
	_delay_ms(400);
	//LCD_COMM(0X01);
	CLOCK();
	alarm();
	_delay_ms(400);
	//LCD_COMM(0X01);
	CLOCK();
	alarm();
	_delay_ms(400);
	//LCD_COMM(0X01);
	CLOCK();
	alarm();
	_delay_ms(400);
	CLOCK();
	alarm();
	_delay_ms(400);
	CLOCK();
	alarm();
	_delay_ms(400);
	CLOCK();
	alarm();
	_delay_ms(400);
	CLOCK();
	alarm();
	_delay_ms(400);
	CLOCK();
	alarm();
	_delay_ms(400);
	/*CLOCK();
	alarm();
	_delay_ms(700);
	CLOCK();
	alarm();
	_delay_ms(700);*/
	LCD_COMM(0X01);/*
	ConvertionToString();
	alarm();
	_delay_ms(400);
	LCD_COMM(0X01);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	LCD_COMM(0X01);*/
	ConvertionToString();
	alarm();
	_delay_ms(400);
	//LCD_COMM(0X01);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	//LCD_COMM(0X01);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	ConvertionToString();
	alarm();
	_delay_ms(400);
	
	LCD_COMM(0X01);
	}
return 0;}