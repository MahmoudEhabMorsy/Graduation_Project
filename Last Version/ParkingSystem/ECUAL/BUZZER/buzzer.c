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

void Buzzer_init(void) {
	DIO_setupPinDirection(BUZZER_PORT, BUZZER_PIN, PIN_OUTPUT);
	DIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

/*
 * Description : Function to turn the Buzzer On.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void Buzzer_on(void) {
	DIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_HIGH);
}

/*
 * Description : Function to turn the Buzzer Off.
 * Inputs: No inputs
 * Outputs: No outputs.
 */
void Buzzer_off(void) {
	DIO_writePin(BUZZER_PORT, BUZZER_PIN, LOGIC_LOW);
}

void Buzzer_toggle(void) {
	DIO_togglePin(BUZZER_PORT, BUZZER_PIN);
}

