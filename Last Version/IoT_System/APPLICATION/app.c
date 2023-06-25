/*
 * app.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

#define GPS_IS_CONNECTED 0
#define ESP01_IS_CONNECTED 1

void app_Init(void)
{
	/* Initialize the LCD Driver */
		DIO_setupPinDirection(SLL_FLAG_PORT, SLL_FLAG_PIN, PIN_OUTPUT);
	DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_HIGH);
	
		DIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);
	DIO_writePin(PORTA_ID,PIN0_ID,GPS_IS_CONNECTED);
	



	GPS_init();



	ESP_preInit();
	sei();
}

void app_Start(void)
{
	
	GPS_sendingCoordinatesTask();

	BMP180_sendingDataTask();

	


}

uint8 GPS_sendingCoordinatesTask(void)
{
	/*Dummy While Loop*/
	GPS_reInit();

	DIO_writePin(PORTA_ID,PIN0_ID,GPS_IS_CONNECTED);
	_delay_us(1);
	GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);

	if(GPS_DataValidation == VALID_GPS_DATA)
	{




		DIO_writePin(PORTA_ID,PIN0_ID,ESP01_IS_CONNECTED);
		_delay_us(1);
		ESP_init();

		ESP_networkConnect(SSID, PASSWORD);

		ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command


		ESP_sendCoordinatesToServer(CAR_ID,t_GPS_Coordinates.Longitude,t_GPS_Coordinates.Latitude);







	}
	else
	{

	}
	return GPS_DataValidation;
}


void BMP180_sendingDataTask(void)
{
	/*TIRES STATE PART*/

		DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_LOW);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);


	DIO_writePin(PORTA_ID,PIN0_ID,ESP01_IS_CONNECTED);
	_delay_us(1);
	ESP_init();

	ESP_networkConnect(SSID, PASSWORD);


	ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command


	ESP_sendTiresState(CAR_ID);





}
