/*
 * pump.c
 *
 *  Created on: May 11, 2023
 *      Author: HP
 */

#include "../../MCAL/DIO/dio.h"
#include "buzzer.h"

void BUZZER_init(void)
{
	DIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

void BUZZER_on(void)
{
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void BUZZER_off(void)
{
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}
