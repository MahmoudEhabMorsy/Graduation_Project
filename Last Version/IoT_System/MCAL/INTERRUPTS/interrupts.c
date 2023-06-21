/*
 * interrupts.c
 *
 *  Created on: Jun 20, 2023
 *      Author: Mahmoud Qotp
 */

#include "interrupts.h"

uint8 g_INT1_Flag = 0;

/*ISR(INT1_vect)
{
	// set the interrupt flag to indicate that INT1 occurs
	g_INT1_Flag = 1;

	//Start the SPI to communication with the sensing control node
}

 External INT1 enable and configuration function
void INT1_Init(void)
{
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD &=~(1<<PD3); //Initially LOW
	Trigger INT1 with the rising edge
	MCUCR |= (1<<ISC11) | (1 << ISC10);
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
}*/
