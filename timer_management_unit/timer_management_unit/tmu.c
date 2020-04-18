/*
 * tmu.c
 *
 * Created: 14/07/2018 11:09:17
 *  Author: Mahmoud
 */ 
#include "tmu.h"
#include "common.h"
#include <avr/io.h>
static timer_object * arr_obj_timers[MAX_NO];

static ecore_u8 objects_counters=0;
/*
// static ecore_u8 main_counter=0;
*/

ISR(TIMER0_COMP_vect)
{
	for (int i=0;i<MAX_NO;i++)
	{
		if (arr_obj_timers[i] != NULL)
		{
			(arr_obj_timers[i]->rem_time)--;
			
		}
	}
}

bool_t tmu_init(ecore_u16 timer_res)
{
	cli();
	bool_t b_ret_val=E_TRUE;
	TCCR0 = 0x28;
	TCCR0 |= 0x02;
	OCR0 = 124;
	TIMSK|=(1<<OCIE0);
	return b_ret_val;
	sei();
}



bool_t tmu_start_timer(timer_object *ptr_object,void (*cb_pf)(void),ecore_u16 time,timer_type tm_type)
{
	cli();
	/*
	for (int i=0;i<MAX_NO;i++)
	{
		arr_obj_timers[i]=NULL;
	}*/
	
	
	bool_t b_ret_val=E_TRUE;
	if ( (ptr_object != NULL) && (cb_pf != NULL) && (time != 0) && ((tm_type == periodic_en)||(tm_type == one_shoot)))
	{
		ptr_object->given_time=time;
		ptr_object->rem_time=time;
		ptr_object->pf_cb=cb_pf;
		ptr_object->t_type=tm_type;
		ptr_object->index=objects_counters;
		arr_obj_timers[objects_counters]=ptr_object;
		objects_counters++;
	} 
	else
	{
		b_ret_val=E_FALSE;
	}
	sei();
	return b_ret_val;
}



bool_t tmu_stop_timer(timer_object *ptr_object)
{	bool_t b_ret_val=E_TRUE;

	ptr_object->given_time=0;
	//
	ptr_object->pf_cb=NULL;
	ptr_object->t_type=no_type;
	arr_obj_timers[ptr_object->index]=NULL;
		return b_ret_val;

}



bool_t tmu_dispatch(void)
{
	static ecore_s16 temp;
	bool_t b_ret_val=E_TRUE;
	for (int i=0;i<MAX_NO;i++)
	{
		if (arr_obj_timers[i] != NULL)
		{
			temp=arr_obj_timers[i]->rem_time;
			if (arr_obj_timers[i]->rem_time <=0)//rewrite this================================
			{
				arr_obj_timers[i]->pf_cb();
				if(arr_obj_timers[i]->t_type == one_shoot)
					tmu_stop_timer(arr_obj_timers[i]);
				arr_obj_timers[i]->rem_time=( (arr_obj_timers[i]->given_time)+(arr_obj_timers[i]->rem_time) );	
			}
		}
	}
	
	
	
	return b_ret_val;
}







bool_t tmu_de_init(void)
{
	bool_t b_ret_val=E_TRUE;

	return b_ret_val;

	//de-init;
}