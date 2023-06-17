/*
 * buzzer.c
 *
 *  Created on: Oct 31, 2022
 *      Author: Mahmoud Qotp
 */


#include "std_types.h"
#include "gpio.h"
#include "buzzer.h"
#include <avr/io.h>
#include "common_macros.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description : Function to Setup the direction for the buzzer pin as output pin through the GPIO driver,
 * 				and Turn off the buzzer through the GPIO.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void Buzzer_init(void)
{
	GPIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

/*
 * Description : Function to turn the Buzzer On.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void Buzzer_on(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}


/*
 * Description : Function to turn the Buzzer Off.
 * Inputs: No inputs
 * Outputs: No outputs.
 */
void Buzzer_off(void)
{
	GPIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

void Buzzer_toggle(void)
{
	GPIO_togglePin(BUZZER_PORT,BUZZER_PIN);
}

