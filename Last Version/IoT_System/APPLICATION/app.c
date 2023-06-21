/*
 * app.c
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

tyreState t_frontLeftTyre = {FRONT_LEFT_TYRE, 0, 0}; /*Initially*/
uint8 dummy_Byte = 0;

ISR(INT1_vect)
{
	/*Receive Tyre Data*/

	/*First, Receive Tyre ID*/
	t_frontLeftTyre.tyre = SPI_sendReceiveByte(dummy_Byte);

	/*Second, Receive Tyre Temperature Value*/
	for (uint8 i = 0; i < TEMPERATURE_VARIABLE_LENGTH; i++) {
		dummy_Byte = SPI_sendReceiveByte(dummy_Byte);
		t_frontLeftTyre.Temperature = (t_frontLeftTyre.Temperature | (dummy_Byte << (i * 8)));
	}

	/*Third, Receive Tyre Pressure Value*/
	for (uint8 i = 0; i < PRESSURE_VARIABLE_LENGTH; i++) {
		dummy_Byte = SPI_sendReceiveByte(dummy_Byte);
		t_frontLeftTyre.Pressure = (t_frontLeftTyre.Pressure | (dummy_Byte << (i * 8)));
	}
}
/*End of Dummy Code Segment*/

void app_Init(void)
{
	/*INT1 init Function*/
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD |= (1<<PD3); // Pull Up Resistor
	/*Trigger INT1 with the falling edge*/
	MCUCR |= (1<<ISC11);
	MCUCR &=~  (1 << ISC10);
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	/* End of INT1 init Function*/
	/* Initialize the LCD Driver */

	_delay_ms(260);
	LCD_init();

	SPI_initSlave();
	LCD_displayString("Test1");

	GPS_init();

	_delay_ms(260);
	_delay_ms(260);

	LCD_clearScreen();
	sei();
}


void app_Start(void)
{
	LCD_clearScreen();

	GPS_sendingCoordinatesTask();

	BMP180_sendingDataTask();
}

uint8 GPS_sendingCoordinatesTask(void)
{
	cli();
	GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
	sei();
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
	ESP_sendTiresState(CAR_ID, t_frontLeftTyre.Temperature, t_frontLeftTyre.Pressure);
}
