/*
 * led.c
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Qotp
 */


#include "led.h"

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
	switch(port_number)
	{
	case 0:
		TOGGLE_BIT(PORTA,pin_number);
		break;
	case 1:
		TOGGLE_BIT(PORTB,pin_number);
		break;
	case 2:
		TOGGLE_BIT(PORTC,pin_number);
		break;
	case 3:
		TOGGLE_BIT(PORTD,pin_number);
		break;
	}
}

/*
 * Description :
 * Function to check if the LED is on.
*/
uint8 LED_IS_ON(uint8 port_number, uint8 pin_number)
{
	switch(port_number)
	{
	case 0:
		if(BIT_IS_SET(PORTA,pin_number))
		{
			return 1;
		}
		break;
	case 1:
		if(BIT_IS_SET(PORTB,pin_number))
		{
			return 1;
		}
		break;
	case 2:
		if(BIT_IS_SET(PORTC,pin_number))
		{
			return 1;
		}
		break;
	case 3:
		if(BIT_IS_SET(PORTD,pin_number))
		{
			return 1;
		}
		break;
	}
	return 0;
}

/*
 * Description :
 * Function to test LED driver.
 * It uses every function implemented in the driver to check that it works correctly.
 */
void LED_test(void)
{
	LED_init(PORTA_ID,PIN0);
	LED_ON(PORTA_ID,PIN0);
	_delay_ms(250);
	_delay_ms(250);
	LED_OFF(PORTA_ID,PIN0);
	_delay_ms(250);
	_delay_ms(250);
	LED_TOGGLE(PORTA_ID,PIN0);
	_delay_ms(250);
	LED_TOGGLE(PORTA_ID,PIN0);
	_delay_ms(250);
	LED_TOGGLE(PORTA_ID,PIN0);
	_delay_ms(250);
	LED_TOGGLE(PORTA_ID,PIN0);
	_delay_ms(250);
	LED_TOGGLE(PORTA_ID,PIN0);
	_delay_ms(250);
	_delay_ms(250);
	if(LED_IS_ON(PORTA_ID,PIN0))
	{
		LED_OFF(PORTA_ID,PIN0);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
	}
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

}
