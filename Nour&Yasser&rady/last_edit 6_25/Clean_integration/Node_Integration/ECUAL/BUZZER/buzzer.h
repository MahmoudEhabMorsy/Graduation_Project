/*
 * buzzer.h
 *
 *  Created on: Oct 31, 2022
 *      Author: Mahmoud Qotp
 */

#ifndef BUZZER_H_
#define BUZZER_H_
#include "../../MCAL/DIO/dio.h"

/*******************************************************************************
 *                                   Definitions                               *
 *******************************************************************************/

//#define BUZZER_PORT PORTC_ID
//#define BUZZER_PIN PIN6_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/*
 * Description : Function to Setup the direction for the buzzer pin as output pin through the GPIO driver,
 * 				and Turn off the buzzer through the GPIO.
 * Inputs: No inputs
 * Outputs: No outputs.
 */
void BUZZER_init(uint8 port_number, uint8 pin_number);
/*
 * Description : Function to turn the Buzzer On.
 * Inputs: No inputs
 * Outputs: No outputs.
 */

void BUZZER_ON(uint8 port_number, uint8 pin_number);

/*
 * Description : Function to turn the Buzzer Off.
 * Inputs: No inputs
 * Outputs: No outputs.
 */
void BUZZER_OFF(uint8 port_number, uint8 pin_number);


void BUZZER_TOGGLE(uint8 port_number, uint8 pin_number);

#endif /* BUZZER_H_ */
