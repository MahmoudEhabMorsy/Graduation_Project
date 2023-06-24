/*
 ================================================================================================
 Name        : MC1.c
 Author      : Mohamed Tarek
 Description : MC1 Code in Exercise2
 Date        : 4/11/2014
 ================================================================================================
 */

#include "spi.h"
#include <util/delay.h> /* To use the delay functions */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay(uint8 secs)
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

int main(void)
{
	uint32 temp = 2345 ;
	uint32 pressure = 999;
	uint8 send_Byte=0;
	/* Initialize the SPI driver as Master */
	SPI_initMaster();
	//SREG = (1<<7);
	/* Delay until MC2 finish its initialization task */
	_delay_ms(200);
	_delay_ms(200);

	/* Send the string to MC2 */

	/*Required Steps:
	 * 1- Interrupt Signal */
	DDRD |= (1<<6); /*Configure PD6 as Output pin*/
	PORTD |= (1<<6); /*Initiate it to be VCCed*/
	/*We may add delay 10 seconds to test*/
	delay(3); /*Delay for 10 seconds*/

	/*We Put 0 on PD6 so it triggers interrupt on MC2*/
	PORTD &=~ (1<<6);
	_delay_us(1); /*Delay until SPI is initiated on MC2*/
	/*FRONT_LEFT_TIRE is an enum configurated at bmp180.h*/
//	SPI_sendReceiveByte (FRONT_LEFT_TIRE); /*Wheel ID*/
	/**/
	for(uint8 i=0;i<counter_Bytes;i++)
	{
		send_Byte =  (temp>>(i*8));
		SPI_sendReceiveByte ( send_Byte );
	}

	for(uint8 i=0;i<counter_Bytes;i++)
		{
			send_Byte =  (pressure>>(i*8));
			SPI_sendReceiveByte ( send_Byte );
		}




    while(1)
    {

    }
}


