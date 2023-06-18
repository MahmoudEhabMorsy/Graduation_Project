/*
 * dio.c
 *
 *  Created on: 9 Nov 2022
 *      Author: MR.MAHMOUD
 */

#include"dio.h"
#include "../../UTILITIES/common_macros.h"
void DIO_setupPinDirection(uint8 port_number, uint8 pin_number, uint8 direction){
/*
 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
 */
	if ((pin_number >= NUM_OF_PINS_PER_PORT) || (port_number >= NUM_OF_PORTS))
	{
		
	}
	else
	{
		/* Setup the pin direction*/
		switch (port_number)
		{
		case PORTA_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRA, pin_number);
			}
			else
			{
				CLEAR_BIT(DDRA, pin_number);
			}
			break;
		case PORTB_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRB, pin_number);
			}
			else
			{
				CLEAR_BIT(DDRB, pin_number);
			}
			break;
		case PORTC_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRC, pin_number);
			}
			else
			{
				CLEAR_BIT(DDRC, pin_number);
			}
			break;
		case PORTD_ID:
			if (direction == PIN_OUTPUT)
			{
				SET_BIT(DDRD, pin_number);
			}
			else
			{
				CLEAR_BIT(DDRD, pin_number);
			}
			break;
		}
	}

}
void DIO_writePin(uint8 port_number, uint8 pin_number, uint8 value){

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 */
	if ((pin_number >= NUM_OF_PINS_PER_PORT) || (port_number >= NUM_OF_PORTS))
	{
	}
	else
	{
		/* Write the pin value*/
		switch (port_number)
		{
		case PORTA_ID:
			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTA, pin_number);
			}
			else
			{
				CLEAR_BIT(PORTA, pin_number);
			}
			break;
		case PORTB_ID:
			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTB, pin_number);
			}
			else
			{
				CLEAR_BIT(PORTB, pin_number);
			}
			break;
		case PORTC_ID:
			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTC, pin_number);
			}
			else
			{
				CLEAR_BIT(PORTC, pin_number);
			}
			break;
		case PORTD_ID:
			if (value == LOGIC_HIGH)
			{
				SET_BIT(PORTD, pin_number);
			}
			else
			{
				CLEAR_BIT(PORTD, pin_number);
			}
			break;
		}
	}
}
uint8 DIO_readPin(uint8 port_number, uint8 pin_number){
	uint8 pin_value = LOGIC_LOW;

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 */
	if ((pin_number >= NUM_OF_PINS_PER_PORT) || (port_number >= NUM_OF_PORTS))
	{
	
	}
	else
	{
		/* Read the pin value*/
		switch (port_number)
		{
		case PORTA_ID:
			if (BIT_IS_SET(PINA, pin_number))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTB_ID:
			if (BIT_IS_SET(PINB, pin_number))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTC_ID:
			if (BIT_IS_SET(PINC, pin_number))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		case PORTD_ID:
			if (BIT_IS_SET(PIND, pin_number))
			{
				pin_value = LOGIC_HIGH;
			}
			else
			{
				pin_value = LOGIC_LOW;
			}
			break;
		}
	}

	return pin_value;
}
void DIO_setupPortDirection(uint8 port_number, GPIO_PortDirectionType direction)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if (port_number >= NUM_OF_PORTS)
	{
	}
	else
	{
		/* Setup the port direction*/
		switch (port_number)
		{
		case PORTA_ID:
			DDRA = direction;
			break;
		case PORTB_ID:
			DDRB = direction;
			break;
		case PORTC_ID:
			DDRC = direction;
			break;
		case PORTD_ID:
			DDRD = direction;
			break;
		}
	}
}

/*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void DIO_writePort(uint8 port_number, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 */
	if (port_number >= NUM_OF_PORTS)
	{
	}
	else
	{
		/* Write the port value*/
		switch (port_number)
		{
		case PORTA_ID:
			PORTA = value;
			break;
		case PORTB_ID:
			PORTB = value;
			break;
		case PORTC_ID:
			PORTC = value;
			break;
		case PORTD_ID:
			PORTD = value;
			break;
		}
	}
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 DIO_readPort(uint8 port_number)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 */
	if (port_number >= NUM_OF_PORTS)
	{
		
	}
	else
	{
		/* Read the port value*/
		switch (port_number)
		{
		case PORTA_ID:
			value = PINA;
			break;
		case PORTB_ID:
			value = PINB;
			break;
		case PORTC_ID:
			value = PINC;
			break;
		case PORTD_ID:
			value = PIND;
			break;
		}
	}

	return value;
}
void DIO_togglePin(uint8 port_num, uint8 pin_num)
{
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		switch(port_num)
		{
		case PORTA_ID:
			TOGGLE_BIT(PORTA,pin_num);
			break;

		case PORTB_ID:
			TOGGLE_BIT(PORTB,pin_num);
			break;
		case PORTC_ID:
			TOGGLE_BIT(PORTC,pin_num);
			break;
		case PORTD_ID:
			TOGGLE_BIT(PORTD,pin_num);
			break;
		}
	}
}
