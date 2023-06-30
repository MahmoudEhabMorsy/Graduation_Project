/*
 * led.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Qotp
 */


#include "led.h"
#include <util/delay.h>

void LED_init(uint8 port_number, uint8 pin_number)
{
	DIO_setupPinDirection(port_number,pin_number,PIN_OUTPUT);
	DIO_writePin(port_number,pin_number, LOGIC_LOW); /*Initiate LEDs to OFF*/
}

/*
 * Description :
 * Function to turn on LED.
 * It depends on DIO driver, as it take port number and pin number,
 * then turn on the required pin (LED).
 */
void LED_ON(uint8 port_number, uint8 pin_number)
{
	DIO_writePin(port_number,pin_number, LOGIC_HIGH);
}

/*
 * Description :
 * Function to turn off LED.
 * It depends on DIO driver, as it take port number and pin number,
 * then turn off the required pin (LED).
 */
void LED_OFF(uint8 port_number, uint8 pin_number)
{
	DIO_writePin(port_number,pin_number, LOGIC_LOW);
}

/*
 * Description :
 * Function to toggle LED.
 * It depends on DIO driver, as it take port number and pin number,
 * then toggle the required pin (LED).
 */
void LED_TOGGLE(uint8 port_number, uint8 pin_number)
{
	DIO_togglePin(port_number,pin_number);
}

/*
 * Description :
 * Function to check if the LED is on.
*/
uint8 LED_IS_ON(uint8 port_number, uint8 pin_number)
{
	return DIO_readPin(port_number,pin_number);
}

