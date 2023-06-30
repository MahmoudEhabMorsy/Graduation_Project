/*
 * buzzer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: Mahmoud Qotp
 */


#include "buzzer.h"
#include <avr/io.h>


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : Function to Setup the direction for the buzzer pin as output pin through the GPIO driver,
 * 				and Turn off the buzzer through the GPIO.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void BUZZER_init(uint8 port_number, uint8 pin_number)
{
	DIO_setupPinDirection(port_number,pin_number,PIN_OUTPUT);
	DIO_writePin(port_number,pin_number,LOGIC_LOW);
}

/*
 * Description : Function to turn the Buzzer On.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void BUZZER_ON(uint8 port_number, uint8 pin_number)
{
	DIO_writePin(port_number,pin_number,LOGIC_HIGH);
}


/*
 * Description : Function to turn the Buzzer Off.
 * Inputs: No inputs
 * Outputs: No outputs.
 */
void BUZZER_OFF(uint8 port_number, uint8 pin_number)
{
	DIO_writePin(port_number,pin_number,LOGIC_LOW);
}

void BUZZER_TOGGLE(uint8 port_number, uint8 pin_number)
{
	DIO_togglePin(port_number,pin_number);
}

