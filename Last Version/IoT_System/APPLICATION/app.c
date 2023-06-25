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
	DIO_setupPinDirection(PORTA_ID,PIN0_ID,PIN_OUTPUT);
	DIO_writePin(PORTA_ID,PIN0_ID,GPS_IS_CONNECTED);
	_delay_ms(250);
	LCD_init();

	LCD_displayString("Test1");

	GPS_init();

	_delay_ms(260);
	_delay_ms(260);

	LCD_clearScreen();

//	ESP_preInit();
//	sei();
}

void app_Start(void)
{
//	cli();
	GPS_sendingCoordinatesTask();
	LCD_clearScreen();
	LCD_displayString("GPS_Task Passed");
	_delay_ms(260);
	_delay_ms(260);
	BMP180_sendingDataTask();
	LCD_clearScreen();
	LCD_displayString("BMP180 Passed");
	_delay_ms(260);
	_delay_ms(260);
//	sei();
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);
	_delay_ms(260);

}

uint8 GPS_sendingCoordinatesTask(void)
{
	uint8 timeout = 0;
	/*Dummy While Loop*/
	GPS_reInit();
//	cli();
	DIO_writePin(PORTA_ID,PIN0_ID,GPS_IS_CONNECTED);
	_delay_us(1);
	GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
//	sei();
//	while(timeout < 0xff)
//	{
//		cli();
//		GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
//		sei();
//		if(GPS_DataValidation == VALID_GPS_DATA)
//		{
//			break;
//		}
//		else
//		{
//			/*Do nothing*/
//		}
//		timeout++;
//	}/*End of Dummy While Loop*/

	if(GPS_DataValidation == VALID_GPS_DATA)
	{
		LCD_displayString("Valid Reading");
		_delay_ms(260);

//		GPS_deInit();

//		cli();
		DIO_writePin(PORTA_ID,PIN0_ID,ESP01_IS_CONNECTED);
		_delay_us(1);
		ESP_init();

		ESP_networkConnect(SSID, PASSWORD);

		ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command


		ESP_sendCoordinatesToServer(CAR_ID,t_GPS_Coordinates.Longitude,t_GPS_Coordinates.Latitude);

//		sei();

//		ESP_deInit();

//		GPS_reInit();

		LCD_clearScreen();

		LCD_displayStringRowColumn(0,0,"Lat: ");
		LCD_displayStringRowColumn(1,0,(const uint8*)t_GPS_Coordinates.Latitude);
		LCD_displayStringRowColumn(2,0,"Lon: ");
		LCD_displayStringRowColumn(3,0,(const uint8*)t_GPS_Coordinates.Longitude);

		_delay_ms(260);
		_delay_ms(260);
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
	return GPS_DataValidation;
}


void BMP180_sendingDataTask(void)
{
	/*TIRES STATE PART*/
//	GPS_deInit();

//	cli();
	DIO_writePin(PORTA_ID,PIN0_ID,ESP01_IS_CONNECTED);
	_delay_us(1);
	ESP_init();

	ESP_networkConnect(SSID, PASSWORD);

	ESP_serverConnect(SW_TEAM_SERVER_IP, PORT); //AT Command

	ESP_sendTiresState(CAR_ID);

//	sei();

	LCD_moveCursor(2,0);
	LCD_displayString("Temp: ");
	LCD_intgerToString(t_frontLeftTire.Temperature);

	LCD_moveCursor(3,0);
	LCD_displayString("Pres: ");
	LCD_intgerToString(t_frontLeftTire.Pressure);
	_delay_ms(260);
	_delay_ms(260);

//	ESP_deInit();
}
