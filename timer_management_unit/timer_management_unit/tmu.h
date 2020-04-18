/*
 * tmu.h
 *
 * Created: 14/07/2018 11:09:40
 *  Author: Mahmoud
 */ 
//using this module will take all control of timer0 

#ifndef TMU_H_
#define TMU_H_
#include "common.h"
#include <avr/interrupt.h>

#define MAX_NO 2
#define ONE_SHOOT 0
#define PERIODIC 1

typedef struct {
	ecore_u16 given_time;
	ecore_s16 rem_time;
	void (*pf_cb)(void);
	ecore_u8 t_type;
	ecore_u8 index;
}timer_object;

typedef enum {
	periodic_en=0,
	one_shoot,
	no_type,
	}timer_type;

bool_t tmu_init(ecore_u16 timer_res);
bool_t tmu_start_timer(timer_object *ptr_object,void (*cb_pf)(void),ecore_u16 time,timer_type t_type);
bool_t tmu_stop_timer(timer_object *ptr_object);
bool_t tmu_dispatch(void);
bool_t tmu_de_init(void);

		#if (F_CPU == 1000000UL)
		
			#elif  (F_CPU == 2000000UL)
		
			#elif  (F_CPU == 3000000UL)
		
			#elif  (F_CPU == 4000000UL)
		
			#elif  (F_CPU == 8000000UL)
		
			#elif  (F_CPU == 10000000UL)
		
			#elif  (F_CPU == 12000000UL)
		
			#elif  (F_CPU == 16000000UL)
				
		#endif


#endif /* TMU_H_ */