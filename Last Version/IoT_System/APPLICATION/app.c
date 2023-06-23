/*
 * app.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

void app_Init(void)
{
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
	uint32 timeout = 0;
	GPS_reInit();
	cli();

	/*Dummy while loop - for now.*/
	while(timeout < 0xffffffff)
	{
		GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
		if(GPS_DataValidation == VALID_GPS_DATA)
		{
			break;
		}
		else
		{
			/*Do Nothing*/
		}
		timeout++;
	}
	/*End of Dummy While Loop*/

	if(GPS_DataValidation == VALID_GPS_DATA)
	{
		sei();

		GPS_deInit();

		ESP_init();

		ESP_networkConnect(SSID, PASSWORD);

		ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command


		ESP_sendCoordinatesToServer(CAR_ID,t_GPS_Coordinates.Longitude,t_GPS_Coordinates.Latitude);

		ESP_deInit();

		GPS_reInit();
	}
	else
	{
		/*Do Nothing*/
	}
	return GPS_DataValidation;
}


void BMP180_sendingDataTask(void)
{
	GPS_deInit();

	ESP_init();

	ESP_networkConnect(SSID, PASSWORD);

	ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command

	ESP_sendTiresState(CAR_ID);

	ESP_deInit();
}
