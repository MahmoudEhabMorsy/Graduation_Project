/*
 * pump.c
 *
 *  Created on: May 11, 2023
 *      Author: HP
 */

#include "../../MCAL/DIO/dio.h"
#include "../../ECUAL/WATERPUMP/waterpump.h"

void WATERPUMP_init(void)
{
	DIO_setupPinDirection(PUMP_PORT,PUMP_PIN,PIN_OUTPUT);
	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_LOW);
}

void WATERPUMP_on(void)
{
	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_HIGH);
}

void WATERPUMP_off(void)
{
	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_LOW);
}


