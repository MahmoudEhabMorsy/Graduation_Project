/*
 * interrupts.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Mahmoud Qotp
 */

#include "interrupts.h"

// External INT1 enable and configuration function
void INT1_Init(void)
{
		/*INT1 init Function*/
		// Configure INT1/PD3 as input pin
		DIO_setupPinDirection(PORTD_ID,PIN3_ID,PIN_INPUT);

		// Pull Up Resistor
		DIO_writePin(PORTD_ID,PIN3_ID,LOGIC_HIGH);

		/*Trigger INT1 with the falling edge*/
		MCUCR |= (1<<ISC11);
		MCUCR &=~  (1 << ISC10);

		GICR  |= (1<<INT1);    // Enable external interrupt pin INT1

		SREG |= (1<<7);
		/* End of INT1 init Function*/
}
