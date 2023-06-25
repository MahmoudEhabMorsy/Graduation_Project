/************************************************************************
 *																		*
 * [FILE NAME]:		NODE_main											*
 *																		*
 * [AUTHOR]:		Ahmed Y Kaead, Nour Atef, Rady Magdy				*
 *																		*
 * [DATE CREATED]:	03/05/2023											*
 *																		*
 * [DESCRIPTION]:	Node that responsible for measuring pressure,		*
 * 					temperatur, and distance							*
 *																		*
 ************************************************************************/

#include "../ECUAL/BMP/bmp180.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/DIO/dio.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../MCAL/SPI/spi.h"

void delay_1(uint8 secs)
{
	uint8 i = 0;
	while(i < secs)
	{
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		i++;
	}
}
unsigned int counter_Bytes=4;

typedef enum state{
	SAFE, MODERATE, SEVERE
}STATE;

#define PRESSURE_SEVERE				100000
#define PRESSURE_MODERATE			10000
#define PRESSURE_SAFE				300
#define SLL_FLAG_PORT				PORTB_ID
#define SLL_FLAG_PIN				PIN7_ID
#define TEMPERATURE_SEVERE			45
#define TEMPERATURE_MODERATE		28
#define TEMPERATURE_SAFE			0

uint32 g_temperature = 0;
uint32 g_pressure = 0;
uint16 g_rpm = 0;

STATE P_state = SAFE;
STATE T_state = SAFE;










void Temp_state(void)
{
	if (g_temperature >= TEMPERATURE_SEVERE)
	{
		T_state = SEVERE;
	}
	else if ((g_temperature >= TEMPERATURE_MODERATE) && (g_temperature < TEMPERATURE_SEVERE))
	{
		T_state = MODERATE;
	}
	else if ((g_temperature >= TEMPERATURE_SAFE) && (g_temperature < TEMPERATURE_MODERATE))
	{
		T_state = SAFE;
	}
}

void Press_state(void)
{
	if (g_pressure >= PRESSURE_SEVERE)
	{
		P_state = SEVERE;
	}
	else if ((g_pressure >= PRESSURE_MODERATE) && (g_pressure < PRESSURE_SEVERE))
	{
		P_state = MODERATE;
	}
	else if ((g_pressure >= PRESSURE_SAFE) && (g_pressure < PRESSURE_MODERATE))
	{
		P_state = SAFE;
	}
}




int main()
{
	TWI_init();
	BMP180_Start();
	//	WSS_Init();

	//DIO_setupPinDirection(SLL_FLAG_PORT, SLL_FLAG_PIN, PIN_OUTPUT);

	DDRD |= (1<<6); /*Configure PD6 as Output pin*/
	PORTD |= (1<<6); /*Initiate it to be VCCed*/

	uint8 send_Byte=0;
	/* Initialize the SPI driver as Master */
	SPI_initMaster();
	SREG |= (1<<7);
	//SREG = (1<<7);
	/* Delay until MC2 finish its initialization task */
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	/* Send the string to MC2 */

	/*Required Steps:
	 * 1- Interrupt Signal */

	/*We may add delay_1 10 seconds to test*/
	//delay_1(3); /*Delay for 10 seconds*/

	


	while (1) {
		g_temperature=33;
		g_pressure=1234;
		//g_temperature = BMP180_calculateTemperature();
		//g_pressure = BMP180_calculatePressure();
		/*We Put 0 on PD6 so it triggers interrupt on MC2*/
		PORTD &= ~(1 << 6);
		//_delay_us(1); /*Delay until SPI is initiated on MC2*/
		//PORTD |= (1 << 6);
		/*FRONT_LEFT_TIRE is an enum configurated at bmp180.h*/
		SPI_sendReceiveByte(FRONT_LEFT); /*Wheel ID*/
		/**/
		for (uint8 i = 0; i < counter_Bytes; i++) {
			send_Byte = (g_temperature >> (i * 8));
			SPI_sendReceiveByte(send_Byte);
		}

		for (uint8 i = 0; i < counter_Bytes; i++) {
			send_Byte = (g_pressure >> (i * 8));
			SPI_sendReceiveByte(send_Byte);

		}
		
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		_delay_ms(250);
		PORTD |= (1 << 6);

	}
}
