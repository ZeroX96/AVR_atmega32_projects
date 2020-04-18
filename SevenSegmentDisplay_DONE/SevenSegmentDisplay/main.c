/*
 * seven_segment_display_hossam.c
 * 
 * Created: 11/07/2018 18:58:18
 * Author : Mahmoud
 */ 

#include <avr/io.h>
#include "seg_disp.h"
#include "common.h"
#include <util/delay.h>

#define WORKED 1
#define DIDNT_WORK 0

//void test_case_1(void) // just init,printout the value 5 & then deinit the display.
/*{
	bool_t b_ret_val= WORKED;
	ecore_u8 handler1=0;//,handler2=0,handler3=0,handler4=0;
	if(disp_init(_BASE_A,_COMMON_CATHODE,&handler1) == _NO_ERRORS)  //disp_initit returns _NO_ERRORS if worked well
	{
		if(disp_out(&handler1,6)== _NO_ERRORS)  //disp_out returns _NO_ERRORS if worked well
		{
			
			/*if(disp_deinit(&handler1) != _NO_ERRORS)  //disp_out returns _NO_ERRORS if worked well,so if didnt will change the b_ret_val
				b_ret_val=DIDNT_WORK;	//disp_de-init didnt work
		}
		else
		{
			b_ret_val=DIDNT_WORK;	//disp_out didnt work
		}
	}
	else
	{
		b_ret_val=DIDNT_WORK;	//disp_initit didnt work
	}
	PORTB=b_ret_val;
	//return b_ret_val;
}
*/


int main(void) {
	DDRA=0xff;DDRB=0xff;DDRC=0xff;DDRD=0xff;
	bool_t b_ret_val= WORKED;
	ecore_u8 handler1=0,handler2=0,handler3=0,handler4=0;		
	b_ret_val= disp_init(_BASE_A,_COMMON_CATHODE,&handler1);  //disp_initit returns _NO_ERRORS if worked well		
	b_ret_val= disp_init(_BASE_B,_COMMON_CATHODE,&handler2);  //disp_initit returns _NO_ERRORS if worked well
	b_ret_val= disp_init(_BASE_C,_COMMON_CATHODE,&handler3);  //disp_initit returns _NO_ERRORS if worked well
	b_ret_val= disp_init(_BASE_D,_COMMON_CATHODE,&handler4);  //disp_initit returns _NO_ERRORS if worked well
	ecore_u8 h1=0,h2=0,h3=0,h4=0;
	while (1)
	{
		b_ret_val= disp_out(&handler1,h1); //disp_out returns _NO_ERRORS if worked well
		b_ret_val= disp_out(&handler2,h2); //disp_out returns _NO_ERRORS if worked well
		b_ret_val= disp_out(&handler3,h3); //disp_out returns _NO_ERRORS if worked well
		b_ret_val= disp_out(&handler4,h4); //disp_out returns _NO_ERRORS if worked well
		_delay_ms(250);
		h1+=2;h2+=1;h3+=1;h4+=1;
		h1= h1>=MAX_POSSIBLE_VALS ? 0:h1;
		h2= h2>=6 ? 0:h2;
		h3= h3>=MAX_POSSIBLE_VALS ? 0:h3;
		h4= h4>=3 ? 0:h4;
	}
	return 0;
}

/*
bool_t test_case_1()
{
	if(val of kza == kza )
		if(val of kza == kza )
			if(val of kza == kza )
				if(val of kza == kza )
	if(counter == 4)
		b_ret=worked wel;
	else error
	return b_ret_val;
}
*/

