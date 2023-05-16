/******************************************************************************
 *
 *	Module: TIMERS
 *
 *	File name: timers.h
 *
 *  Author: Mahmoud Khaled
 *
 *******************************************************************************/

#ifndef TIMER_H_
#define TIMER_H_

#include "../../CommonDef/std_types.h"

/********************************************************/
/* Type definitions */
/********************************************************/

typedef enum{
	Timer0, Timer1, Timer2
}Timer_ID;

typedef enum{
	Normal, CTC
}Timer_mode;

typedef enum{
	NO_Clock , Prescaler_1, Prescaler_8, Prescaler_64, Prescaler_256, Prescaler_1024,
	External_T1_Falling_Edge, External_T1_Rising_Edge
}Timer_Prescaler;

typedef struct{
	Timer_ID timer_ID;
	Timer_mode mode;
	uint16 initialValue;
	uint16 compareValue;
	Timer_Prescaler prescaler;
	void (*callBackPtr)(void);
}Timer_configuration;


/********************************************************/
/* Functions prototypes */
/********************************************************/

void Timer_init(const Timer_configuration* timer_config);


void Timer_deInit(Timer_ID timer_ID);

#endif /* TIMER_H_ */
