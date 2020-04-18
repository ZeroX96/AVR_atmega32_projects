/*
 * RE_PASSWORD.c
 *
 * Created: 12/26/2016 5:25:36 PM
 *  Author: MABAKCH-AYRIM
 */ 



////////////////////////////////////////////////////////////////////////////////////////////////////////
//**************************************************************//
//Microcontroller			:ATmega32
//System Clock				:1MHz
//Project					:4X4 Keypad based  Password with ATmega32 and LCD Display
//Software					:AVR Studio 4
//LCD Data Interfacing		:8-Bit
//Author					:Arun Kumar Garg
//							:ABLab Solutions
//							:www.ablab.in
//							:info@ablab.in
//Date						:1st January 2012
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	1000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#define		KEYPAD_PORT		PORTC
/*Defines a macro for the keypad.h header file. KEYPAD_PORT is the microcontroller PORT Register to which 4X4 keypad is connected. Default PORT Register in keypad.h header file is PORTB*/

#define		KEYPAD_PIN		PINC
/*Defines a macro for the keypad.h header file. KEYPAD_PIN is the microcontroller PIN Register to which 4X4 keypad is connected. Default PIN Register in keypad.h header file is PINB*/

//#include<avr/keypad.h>
/////////////////
//Micricontroller		:All 8-bit AVR Micricontrollers with Similar Register Configuration with ATmega16
//System Clock			:1 MHz - 16 MHz
//Header File Version 		:1.1
//Author			:Arun Kumar Garg 
//				:ABLab Solutions
//				:www.ablab.in
//				:info@ablab.in
//Date				:1st August 2011

/*Copyright (c) 2011 ABLab Solutions All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 	following disclaimer in the documentation 
     and/or other materials provided with the distribution.
   * Neither the name of the copyright holders nor the names of contributors may be used to endorse or promote products derived from this software without 
     specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

/*Function defination*/
unsigned char read_keypad(void)
{
	unsigned char keypad_input=0xff,keypad_output=0xff;
	KEYPAD_PORT=0xfe;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
		keypad_output=0x01;
	else if(keypad_input==0xd0)
		keypad_output=0x02;
	else if(keypad_input==0xb0)
		keypad_output=0x03;
	else if(keypad_input==0x70)
		keypad_output=0x0c;
	else 
		;

	KEYPAD_PORT=0xfd;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
		keypad_output=0x04;
	else if(keypad_input==0xd0)
		keypad_output=0x05;
	else if(keypad_input==0xb0)
		keypad_output=0x06;
	else if(keypad_input==0x70)
		keypad_output=0x0d;
	else 
		;

	KEYPAD_PORT=0xfb;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
		keypad_output=0x07;
	else if(keypad_input==0xd0)
		keypad_output=0x08;
	else if(keypad_input==0xb0)
		keypad_output=0x09;
	else if(keypad_input==0x70)
		keypad_output=0x0e; 
	else 
		;		
		
	KEYPAD_PORT=0xf7;
	_delay_us(2);
	keypad_input=KEYPAD_PIN & 0xf0;

	if(keypad_input==0xe0)
		keypad_output=0x0a; 
	else if(keypad_input==0xd0)
		keypad_output=0x00;
	else if(keypad_input==0xb0)
		keypad_output=0x0b;
	else if(keypad_input==0x70)
		keypad_output=0x0f;
	else 
		;

	return keypad_output;
}
/////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>



#define _LCD_H
/*_________________________________________________________________________________________*/
 
/************************************************
	LCD CONNECTIONS
*************************************************/

#define LCD_DATA B	//Port PB2-PB5 are connected to D4-D7

#define LCD_E B //Enable/strobe signal
#define LCD_E_POS	PB0	//Position of enable in above port

#define LCD_RS B	
#define LCD_RS_POS PB7

#define LCD_RW B
#define LCD_RW_POS PB6

#define LCD_DATA_POS 2


//************************************************

#define LS_NONE  0B00000000
#define LS_BLINK 0B00000001
#define LS_ULINE 0B00000010

//Backlight is connected here
#define OC1A_PORT D
#define OC1A_PIN PD5


/***************************************************
			F U N C T I O N S
****************************************************/



void LCDInit(uint8_t style);
void LCDWriteString(const char *msg);
void LCDWriteInt(int val,unsigned int field_length);
void LCDGotoXY(uint8_t x,uint8_t y);
void LCDBacklightOn();
void LCDBacklightOff();


//Low level
void LCDByte(uint8_t,uint8_t);
#define LCDCmd(c) (LCDByte(c,0))
#define LCDData(d) (LCDByte(d,1))

void LCDBusyLoop();





/***************************************************
			F U N C T I O N S     E N D
****************************************************/


/***************************************************
	M A C R O S
***************************************************/
#define LCDClear() LCDCmd(0b00000001)
#define LCDHome() LCDCmd(0b00000010);

#define LCDWriteStringXY(x,y,msg) {\
 LCDGotoXY(x,y);\
 LCDWriteString(msg);\
}

#define LCDWriteIntXY(x,y,val,fl) {\
 LCDGotoXY(x,y);\
 LCDWriteInt(val,fl);\
}
/***************************************************/




/*_________________________________________________________________________________________*/





 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)


#define LCD_DATA_PORT 	PORT(LCD_DATA)
#define LCD_E_PORT 		PORT(LCD_E)
#define LCD_RS_PORT 	PORT(LCD_RS)
#define LCD_RW_PORT 	PORT(LCD_RW)

#define LCD_DATA_DDR 	DDR(LCD_DATA)
#define LCD_E_DDR 		DDR(LCD_E)
#define LCD_RS_DDR 		DDR(LCD_RS)
#define LCD_RW_DDR 		DDR(LCD_RW)

#define LCD_DATA_PIN	PIN(LCD_DATA)

#define SET_E() (LCD_E_PORT|=(1<<LCD_E_POS))
#define SET_RS() (LCD_RS_PORT|=(1<<LCD_RS_POS))
#define SET_RW() (LCD_RW_PORT|=(1<<LCD_RW_POS))

#define CLEAR_E() (LCD_E_PORT&=(~(1<<LCD_E_POS)))
#define CLEAR_RS() (LCD_RS_PORT&=(~(1<<LCD_RS_POS)))
#define CLEAR_RW() (LCD_RW_PORT&=(~(1<<LCD_RW_POS)))



void LCDByte(uint8_t c,uint8_t isdata)
{
//Sends a byte to the LCD in 4bit mode
//cmd=0 for data
//cmd=1 for command


//NOTE: THIS FUNCTION RETURS ONLY WHEN LCD HAS PROCESSED THE COMMAND

uint8_t hn,ln;			//Nibbles
uint8_t temp;

hn=c>>4;
ln=(c & 0x0F);

if(isdata==0)
	CLEAR_RS();
else
	SET_RS();

_delay_us(0.500);		//tAS

SET_E();

//Send high nibble

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((hn<<LCD_DATA_POS));
LCD_DATA_PORT=temp;

_delay_us(1);			//tEH

//Now data lines are stable pull E low for transmission

CLEAR_E();

_delay_us(1);

//Send the lower nibble
SET_E();

temp=(LCD_DATA_PORT & (~(0X0F<<LCD_DATA_POS)))|((ln<<LCD_DATA_POS));

LCD_DATA_PORT=temp;

_delay_us(1);			//tEH

//SEND

CLEAR_E();

_delay_us(1);			//tEL

LCDBusyLoop();
}

void LCDBusyLoop()
{
	//This function waits till lcd is BUSY

	uint8_t busy,status=0x00,temp;

	//Change Port to input type because we are reading data
	LCD_DATA_DDR&=(~(0x0f<<LCD_DATA_POS));

	//change LCD mode
	SET_RW();		//Read mode
	CLEAR_RS();		//Read status

	//Let the RW/RS lines stabilize

	_delay_us(0.5);		//tAS

	
	do
	{

		SET_E();

		//Wait tDA for data to become available
		_delay_us(0.5);

		status=(LCD_DATA_PIN>>LCD_DATA_POS);
		status=status<<4;

		_delay_us(0.5);

		//Pull E low
		CLEAR_E();
		_delay_us(1);	//tEL

		SET_E();
		_delay_us(0.5);

		temp=(LCD_DATA_PIN>>LCD_DATA_POS);
		temp&=0x0F;

		status=status|temp;

		busy=status & 0b10000000;

		_delay_us(0.5);
		CLEAR_E();
		_delay_us(1);	//tEL
	}while(busy);

	CLEAR_RW();		//write mode
	//Change Port to output
	LCD_DATA_DDR|=(0x0F<<LCD_DATA_POS);

}

void LCDInit(uint8_t style)
{
	/*****************************************************************
	
	This function Initializes the lcd module
	must be called before calling lcd related functions

	Arguments:
	style = LS_BLINK,LS_ULINE(can be "OR"ed for combination)
	LS_BLINK :The cursor is blinking type
	LS_ULINE :Cursor is "underline" type else "block" type

	*****************************************************************/
	
	//After power on Wait for LCD to Initialize
	_delay_ms(30);
	
	//Set IO Ports
	LCD_DATA_DDR|=(0x0F<<LCD_DATA_POS);
	LCD_E_DDR|=(1<<LCD_E_POS);
	LCD_RS_DDR|=(1<<LCD_RS_POS);
	LCD_RW_DDR|=(1<<LCD_RW_POS);

	LCD_DATA_PORT&=(~(0x0F<<LCD_DATA_POS));
	CLEAR_E();
	CLEAR_RW();
	CLEAR_RS();

	//Set 4-bit mode
	_delay_us(0.3);	//tAS

	SET_E();
	LCD_DATA_PORT|=((0b00000010)<<LCD_DATA_POS); //[B] To transfer 0b00100000 i was using LCD_DATA_PORT|=0b00100000
	_delay_us(1);
	CLEAR_E();
	_delay_us(1);

	//Wait for LCD to execute the Functionset Command
	LCDBusyLoop();                                    //[B] Forgot this delay

	//Now the LCD is in 4-bit mode

	LCDCmd(0b00001100|style);	//Display On
	LCDCmd(0b00101000);			//function set 4-bit,2 line 5x7 dot format

	//PWM Backlight Control
	TCCR1A=(1<<COM1A1)|(1<<WGM10);

	//clk=fcpu/64
	TCCR1B=(1<<CS10);

	//Set the corresponding port pin to output
	DDR(OC1A_PORT)|=(1<<OC1A_PIN);
}
void LCDWriteString(const char *msg)
{
	/*****************************************************************
	
	This function Writes a given string to lcd at the current cursor
	location.

	Arguments:
	msg: a null terminated string to print


	*****************************************************************/
 while(*msg!='\0')
 {
	LCDData(*msg);
	msg++;
 }
}

void LCDWriteInt(int val,unsigned int field_length)
{
	/***************************************************************
	This function writes a integer type value to LCD module

	Arguments:
	1)int val	: Value to print

	2)unsigned int field_length :total length of field in which the value is printed
	must be between 1-5 if it is -1 the field length is no of digits in the val

	****************************************************************/

	char str[5]={0,0,0,0,0};
	int i=4,j=0;
	while(val)
	{
	str[i]=val%10;
	val=val/10;
	i--;
	}
	if(field_length==-1)
		while(str[j]==0) j++;
	else
		j=5-field_length;

	if(val<0) LCDData('-');
	for(i=j;i<5;i++)
	{
	LCDData(48+str[i]);
	}
}
void LCDGotoXY(uint8_t x,uint8_t y)
{
 if(x<40)
 {
  if(y) x|=0b01000000;
  x|=0b10000000;
  LCDCmd(x);
  }
}

void LCDBacklightOn()
{
	if(OCR1A==0x00)
	{
		uint8_t i;
		for(i=0;i<250;i++)
		{
			OCR1A=i;
			_delay_loop_2(1500);
		}

		OCR1A=0xFF;
	}

}

void LCDBacklightOff()
{
	if(OCR1A==0xFF)
	{
		uint8_t i;
		for(i=255;i>5;i--)
		{
			OCR1A=i;
			_delay_loop_2(1500);
		}

		OCR1A=0x00;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*Includes keypad.h header file which defines one function: read_keypad () to read the 4X4 keypad. Keypad header file version is 1.1*/

#define		LCD_DATA_PORT		PORTB
/*Defines a macro for the lcd.h header File. LCD_DATA_PORT is the microcontroller PORT Register to which the data pins of the LCD are connected. Default PORT Register for data pins in lcd.h header file is PORTA*/

#define 	LCD_CONT_PORT		PORTD
/*Defines a macro for the lcd.h header File. LCD_CONT_PORT is the microcontroller PORT Register to which the control pins of the LCD are connected. Default PORT Register for control pins in lcd.h header file is PORTB*/

#define 	LCD_RS 		PD0
/*Defines a macro for the lcd.h header file. LCD_RS is the microcontroller Port pin to which the RS pin of the LCD is connected. Default Port pin for RS pin in lcd.h header file is PB0*/

#define 	LCD_RW 		PD1
/*Defines a macro for the lcd.h header file. LCD_RW is the microcontroller Port pin to which the RW pin of the LCD is connected. Default Port pin for RW pin in lcd.h header file is PB1*/

#define 	LCD_EN 		PD2
/*Defines a macro for the lcd.h header file. LCD_EN is the microcontroller Port pin to which the EN pin of the LCD is connected. Default Port pin for EN pin in lcd.h header file is PB2*/

//#include<avr/lcd.h>
/*Includes lcd.h header file which defines different functions for all Alphanumeric LCD(8-Bit Interfacing Method). LCD header file version is 1.1*/

#include<string.h>
/*Includes string.h header file which defines different string functions*/

int main(void)
{
	DDRB=0xff;
	/*All the 8 pins of PortB are declared output (data pins of LCD are connected)*/

	DDRD=0x07;
	/*PD0, PD1 and PD2 pins of PortD are declared output (control pins of LCD are connected)*/

	DDRC=0x0f;
	/*PortC's upper 4 bits are declared input and lower 4 bits are declared output(4x4 Keypad is connected)*/

	PORTC=0xff;
	/*PortC's lower 4 bits are given high value and pull-up are enabled for upper 4 bits*/

	unsigned char count=0, keypad_value, password_status=0;
	char password_set[5]="1234", password_entered[5];
	/*Variable declarations*/

	lcd_init();
	/*LCD initialization*/

	LCDWriteString("ABLab Solutions");
	/*String display in 1st row of LCD*/

	lcd_command_write(0xc0);
	/*Cursor moves to 2nd row 1st column of LCD*/

	LCDWriteString("www.ablab.in");
	/*String display in 2nd row of LCD*/
	
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	/*Display stays for 2 second*/

	lcd_command_write(0x01);
	/*Clear screen*/

	LCDWriteString("Enter Password");
	/*String display in 1st row of LCD*/

	/*While loop for password entry and checking*/
	while(password_status==0x00)
	{
		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column of LCD*/

		/*While loop for 4 digit password entry*/
		while(count<4)
		{
			keypad_value=read_keypad();
			/*Scan's 4X4 keypad and returns pressed key value or default value*/

			/*Checking if any key is pressed or not*/
			if(keypad_value != 0xff)
			{
				password_entered[count]=keypad_value+48;
				/*Storing the pressed key value of 4X4 keypad in ASCII format*/

				count++;
				/*Counter increment*/

				lcd_data_write('*');
				/* Star(*) is displayed in 2nd row of LCD*/
			}
			else
			{
				;
				/*Null statement*/
			}

			_delay_ms(300);
			/*300ms delay as guard time between two consecutive pressing of key*/
		}
		count=0;
		/*Counter reset to 0*/

		password_entered[4]=0;
		/*Null character at the last of array(password_entered) to convert it to a string*/

		lcd_command_write(0x01);
		/*Clear screen*/

		/*Password Comparision*/
		if(!(strcmp(password_set,password_entered)))
		{
			LCDWriteString("Correct Password");
			/*String display in 1st row of LCD*/

			password_status=1;
			/*Changing the Password Status to Correct Password*/
		}
		else
		{
			LCDWriteString("Wrong Password");
			/*String display in 1st row of LCD*/
			
			_delay_ms(500);
			_delay_ms(500);
			_delay_ms(500);
			_delay_ms(500);
			/*Display stays for 2 second*/

			lcd_command_write(0x01);
			/*Clear screen*/

			LCDWriteString("Reenter Password");
			/*String display in 1st row of LCD*/
		}
	}

	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	/*Display stays for 2 second*/
	
	lcd_command_write(0x01);
	/*Clear Screen*/

	/*Start of infinite loop*/
	while(1)
	{
		lcd_command_write(0x80);
		/*Cursor moves to 2nd row 1st column of LCD*/

		LCDWriteString("Press any Key");
		/*String display in 1st row of LCD*/
		
		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column of LCD*/

		LCDWriteString("Key Value: ");
		/*String display in 1st row of LCD*/

		keypad_value=read_keypad();
		/*Scan's 4X4 keypad and returns pressed key value or default value*/
		
		/*Checking if any key is pressed or not*/
		if(keypad_value!=0xff)
		{
			switch(keypad_value)
			{
				case 0:
				lcd_data_write('0');
				/*Displays 0 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 1:
				lcd_data_write('1');
				/*Displays 1 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 2:
				lcd_data_write('2');
				/*Displays 2 in 2nd row of LCD*/

				break;
				/*Break statement*/
				
				case 3:
				lcd_data_write('3');
				/*Displays 3 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 4:
				lcd_data_write('4');
				/*Displays 4 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 5:
				lcd_data_write('5');
				/*Displays 5 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 6:
				lcd_data_write('6');
				/*Displays 6 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 7:
				lcd_data_write('7');
				/*Displays 7 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 8:
				lcd_data_write('8');
				/*Displays 8 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 9:
				lcd_data_write('9');
				/*Displays 9 in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 10:
				lcd_data_write('*');
				/*Displays * in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 11:
				lcd_data_write('#');
				/*Displays # in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 12:
				lcd_data_write('A');
				/*Displays A in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 13:
				lcd_data_write('B');
				/*Displays B in 2nd row of LCD*/

				break;
				/*Break statement*/

				case 14:
				lcd_data_write('C');
				/*Displays C in 2nd row of LCD*/

				break;
				/*Break statement*/;

				case 15:
				lcd_data_write('D');
				/*Displays D in 2nd row of LCD*/

				break;
				/*Break statement*/;
			}
		}
		else
		{
			;
			/*Null statement*/
		}

		_delay_ms(300);
		/*300ms delay as guard time between two consecutive pressing of key*/
	}
}
/*End of program*/
