/*
 * main.c
 *
 *  Created on: Feb 14, 2023
 *      Author: Mahmoud Qotp
 */


#include "uart.h"
#include "common_macros.h"
#include "std_types.h"
#include <util/delay.h>
#include "esp.h"
#include "gpio.h"

/* DDRX
 * PORTX
 * PINX
*/
/* "GET http://mahmoud.freevar.com/status.txt\r\n" */
/*Length = "43" */

int main(void)
{
	/*init*/
	uint8 LEDMode = 12;
	uint8 test;
	_delay_ms(250);
	ESP_init();
	GPIO_setupPinDirection(PORTB_ID,PIN7_ID,PIN_OUTPUT);

	ESP_networkConnect("MQOTP 5528", "90900000");

	ESP_serverConnect("172.107.162.12", "80");

	while(1)
	{
		LEDMode = ESP_receiveDataFromServer("43","GET http://mahmoud.freevar.com/status.txt\r\n");
		if(LEDMode == 1)
		{
			GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_HIGH);
		}
		else if(LEDMode == 0)
		{
			GPIO_writePin(PORTB_ID,PIN7_ID,LOGIC_LOW);

		}
		else
		{
			/*Do Nothing*/
		}
		ESP_serverConnect("172.107.162.12", "80");
	}
}
