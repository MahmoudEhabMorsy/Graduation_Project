/*
 * app.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

//uint8 GPS_CallibrationState = GPS_CALLIBRATION_FAILED;
//uint8 ESP_ConnectionState = ESP_CONNECTION_FAILED;


void app_Init(void)
{
	/*LEDs Initialization to Indicate the state of each task*/
	LED_init(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
	LED_init(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
	LED_init(GPS_CALLIBRATION_SUCCESS_INDICATION_PORT, GPS_CALLIBRATION_SUCCESS_INDICATION_PIN);
	LED_init(GPS_CALLIBRATION_FAIL_INDICATION_PORT, GPS_CALLIBRATION_FAIL_INDICATION_PIN);

	GPS_init();
	ESP_preInit();
	sei();
}

void app_Start(void)
{
	GPS_sendingCoordinatesTask();

	BMP180_sendingDataTask();
}

void GPS_sendingCoordinatesTask(void)
{
	GPS_reInit();

	GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);

	if(GPS_DataValidation == VALID_GPS_DATA)
	{
		LED_ON(GPS_CALLIBRATION_SUCCESS_INDICATION_PORT,GPS_CALLIBRATION_SUCCESS_INDICATION_PIN);
		LED_OFF(GPS_CALLIBRATION_FAIL_INDICATION_PORT,GPS_CALLIBRATION_FAIL_INDICATION_PIN);

		ESP_init();

		if(ESP_networkConnect(SSID, PASSWORD))
		{
			if(ESP_serverConnect(SW_TEAM_SERVER_IP, PORT))
			{
				ESP_sendCoordinatesToServer(CAR_ID,t_GPS_Coordinates.Longitude,t_GPS_Coordinates.Latitude);

				LED_ON(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
				LED_OFF(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
			}

			else
			{
				LED_OFF(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
				LED_ON(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
			}
		}

		else
		{
			LED_OFF(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
			LED_ON(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
		}
	}

	else
	{
		LED_OFF(GPS_CALLIBRATION_SUCCESS_INDICATION_PORT,GPS_CALLIBRATION_SUCCESS_INDICATION_PIN);
		LED_ON(GPS_CALLIBRATION_SUCCESS_INDICATION_PORT,GPS_CALLIBRATION_FAIL_INDICATION_PIN);
	}
}


void BMP180_sendingDataTask(void)
{
	ESP_requestingData();

	ESP_init();

	if(ESP_networkConnect(SSID, PASSWORD))
	{
		if(ESP_serverConnect(SW_TEAM_SERVER_IP, PORT))
		{
			ESP_sendTiresState(CAR_ID);

			LED_ON(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
			LED_OFF(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
		}

		else
		{
			LED_OFF(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
			LED_ON(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
		}
	}

	else
	{
		LED_OFF(ESP_CONNECTION_SUCCESS_INDICATION_PORT,ESP_CONNECTION_SUCCESS_INDICATION_PIN);
		LED_ON(ESP_CONNECTION_FAIL_INDICATION_PORT,ESP_CONNECTION_FAIL_INDICATION_PIN);
	}
}
