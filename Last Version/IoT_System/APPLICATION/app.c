/*
 * app.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

void app_Init(void)
{
	/* Initialize the LCD Driver */

	_delay_ms(260);
	LCD_init();

	LCD_displayString("Test1");

	//GPS_init();

	_delay_ms(260);
	_delay_ms(260);

	LCD_clearScreen();

	ESP_preInit();
	sei();
}

void app_Start(void)
{
//	GPS_sendingCoordinatesTask();
//
//	LCD_displayString("GPS_Task Passed");
//	_delay_ms(260);
//	_delay_ms(260);
	LCD_clearScreen();
	BMP180_sendingDataTask();
	//LCD_displayString("BMP180 Passed");
	_delay_ms(260);
	_delay_ms(260);
}

uint8 GPS_sendingCoordinatesTask(void)
{
	/*Dummy While Loop*/
	while(GPS_DataValidation != VALID_GPS_DATA)
	{
		GPS_reInit();
		cli();
		GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
		sei();
	}/*End of Dummy While Loop*/
	if(GPS_DataValidation == VALID_GPS_DATA)
	{
		LCD_displayString("Valid Reading");
		_delay_ms(260);

		GPS_deInit();

		ESP_init();

		ESP_networkConnect(SSID, PASSWORD);

		ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command


		ESP_sendCoordinatesToServer(CAR_ID,t_GPS_Coordinates.Longitude,t_GPS_Coordinates.Latitude);

		ESP_deInit();

		GPS_reInit();

		LCD_clearScreen();
	}
	else if(GPS_DataValidation == VOID_GPS_DATA)
	{
		LCD_displayString("Void Reading");
		_delay_ms(260);
		LCD_clearScreen();
	}
	else
	{
		LCD_displayString("Incorrect Reading");
		_delay_ms(260);
		LCD_clearScreen();
	}

	LCD_displayStringRowColumn(0,0,"Lat: ");
	LCD_displayStringRowColumn(1,0,(const uint8*)t_GPS_Coordinates.Latitude);
	LCD_displayStringRowColumn(2,0,"Lon: ");
	LCD_displayStringRowColumn(3,0,(const uint8*)t_GPS_Coordinates.Longitude);

	_delay_ms(260);
	_delay_ms(260);
	return GPS_DataValidation;
}


void BMP180_sendingDataTask(void)
{
	/*TIRES STATE PART*/
	//GPS_deInit();

	ESP_init();

	ESP_networkConnect(SSID, PASSWORD);

	ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command

	ESP_sendTiresState(CAR_ID);

	LCD_moveCursor(2,0);
	LCD_displayString("Temp: ");
	LCD_intgerToString(t_frontLeftTire.Temperature);

	LCD_moveCursor(3,0);
	LCD_displayString("Pres: ");
	LCD_intgerToString(t_frontLeftTire.Pressure);
	_delay_ms(260);
	_delay_ms(260);

	ESP_deInit();
}
