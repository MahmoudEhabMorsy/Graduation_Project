/*
 * pump_main.c
 *
 *  Created on: May 14, 2023
 *      Author: HP
 */

#include "dio.h"
#include "std_types.h"


#define PUMP_PORT				PORTA_ID
#define PUMP_PIN				PIN0_ID
#define BUZZER_PORT				PORTC_ID
#define BUZZER_PIN				PIN6_ID

int main (void)
{

	DIO_setupPinDirection(PUMP_PORT,PUMP_PIN,PIN_OUTPUT);
	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_LOW);

	DIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);

	while(1)
	{
		DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_HIGH);
		DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);

	}
	return 0;
}
