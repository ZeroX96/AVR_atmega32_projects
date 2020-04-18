//**************************************************************//
//Microcontroller			:ATmega32
//System Clock				:8MHz
//Project					:Getting the Version of HC-05 Bluetooth Module with ATmega32
//Software					:ATmel Studio 6
//USART Baud Rate			:9600
//USART Data Bits			:8
//USART Stop Bits			:1
//USART Mode				:Asynchronous Mode
//USART Parity				:No Parity
//Author					:BALKRISHNA
//							:ABLab Solutions
//							:www.ablab.in
//							:info@ablab.in
//Date						:1st June 2015
//**************************************************************//

#include<avr/io.h>
/*Includes io.h header file where all the Input/Output Registers and its Bits are defined for all AVR microcontrollers*/

#define	F_CPU	8000000
/*Defines a macro for the delay.h header file. F_CPU is the microcontroller frequency value for the delay.h header file. Default value of F_CPU in delay.h header file is 1000000(1MHz)*/

#include<util/delay.h>
/*Includes delay.h header file which defines two functions, _delay_ms (millisecond delay) and _delay_us (microsecond delay)*/

#define		LCD_DATA_PORT		PORTB
/*Defines a macro for the lcd.h header File. LCD_DATA_PORT is the microcontroller PORT Register to which the data pins of the LCD are connected. Default PORT Register for data pins in lcd.h header file is PORTA*/

#define 	LCD_CONT_PORT		PORTC
/*Defines a macro for the lcd.h header File. LCD_CONT_PORT is the microcontroller PORT Register to which the control pins of the LCD are connected. Default PORT Register for control pins in lcd.h header file is PORTB*/

#define 	LCD_RS 		PC0
/*Defines a macro for the lcd.h header file. LCD_RS is the microcontroller Port pin to which the RS pin of the LCD is connected. Default Port pin for RS pin in lcd.h header file is PB0*/

#define 	LCD_RW 		PC1
/*Defines a macro for the lcd.h header file. LCD_RW is the microcontroller Port pin to which the RW pin of the LCD is connected. Default Port pin for RW pin in lcd.h header file is PB1*/

#define 	LCD_EN 		PC2
/*Defines a macro for the lcd.h header file. LCD_EN is the microcontroller Port pin to which the EN pin of the LCD is connected. Default Port pin for EN pin in lcd.h header file is PB2*/

#include<avr/lcd.h>
/*Includes lcd.h header file which defines different functions for all Alphanumeric LCD(8-Bit Interfacing Method). LCD header file version is 1.1*/

#include<avr/hc05.h>
/*Includes hc05.h header file which defines different functions for HC-05 Bluetooth Module. HC-05 header file version is 1.1*/

extern char hc_05_buffer2[];
/*Variable is declared in hc05.h header file*/

int main(void)
{
	DDRB=0xff;
	/*All the 8 pins of PortB are declared output (data pins of LCD are connected)*/

	DDRC=0x07;
	/*PC0, PC1 and PC2 pins of PortC are declared output (control pins of LCD are connected)*/
	
	unsigned char received_data;
	/*Variable declaration*/
	
	lcd_init();
	/*LCD initialization*/
	
	usart_init();
	/*USART initialization*/
	
	lcd_string_write("ABLab Solutions");
	/*String is displayed in 1st row of LCD*/

	lcd_command_write(0xc0);
	/*Cursor moves to 2nd row 1st column*/

	lcd_string_write("www.ablab.in");
	/*String is displayed in 2nd row of LCD*/
	
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	_delay_ms(500);
	
	do
	{
		received_data=hc_05_bluetooth_at_command_mode_test();
		_delay_ms(100);
	}while(!received_data);
	/*Waiting for the Bluetooth Module to enter into Command Mode*/
	
	lcd_command_write(0x01);
	/*Clear Screen*/
	
	lcd_string_write("Now in AT Mode");
	/*String is displayed in 1st row of LCD*/
	
	_delay_ms(500);
	_delay_ms(500);
	
	received_data=hc_05_bluetooth_get_version();
	/*Sending AT Command to know the Bluetooth Module's version*/
	
	/*Checking whether Bluetooth Module's version is read or not*/
	if(received_data==1)
	{
		lcd_command_write(0x01);
		/*Clear Screen*/
		
		lcd_string_write("BluetoothVersion");
		/*String is displayed in 1st row of LCD*/
		
		lcd_command_write(0xc0);
		/*Cursor moves to 2nd row 1st column*/
		
		lcd_string_write(hc_05_buffer2);
		/*String is displayed in 2nd row of LCD*/
	}
	else
	{
		;
		/*Null statement*/
	}
}
/*End of program*/


