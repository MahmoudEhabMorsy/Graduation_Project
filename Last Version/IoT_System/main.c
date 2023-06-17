
#include "uart.h"
#include "lcd.h"

#include "gps.h"

#define SSID (const uint8*) "MQOTP"
#define PASSWORD (const uint8*) "90900000"

#define THINGSPEAK_SERVER_IP (const uint8*) "184.106.153.149"
#define THINGSPEAK_SERVER_URL (const uint8*) "api.thingspeak.com"
#define SW_TEAM_SERVER_IP (const uint8*) "34.122.187.191"

#define IP (const uint8*) "34.122.187.191"
#define PORT (const uint8*) "80"
#define API_KEY (const uint8*) "E3F314CY3VJGPB74"
#define CAR_ID (const uint8*) "63d5343990599fb5c8ce4c48"

uint32 Temperature = 37; // DUMMY
uint32 Pressure = 1200; //DUMMY

int main(void)
{
	/*Initialization*/
	GPS_Coordinates t_GPS_Coordinates;
	uint8 GPS_DataValidation;

	LCD_init();
	_delay_ms(260);
	LCD_displayString("Test1");
	GPS_init();
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
	LCD_clearScreen();


	/*Super Loop*/
	while(1)
	{
		// Receive Temperature and Pressure Values.


		/*GPS PART*/
		LCD_clearScreen();
		GPS_DataValidation = GPS_getCoordinates(&t_GPS_Coordinates);
		if(GPS_DataValidation == VALID_GPS_DATA)
		{
			LCD_displayString("Valid Reading");
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
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
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			LCD_clearScreen();
		}
		else
		{
			LCD_displayString("Incorrect Reading");
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			_delay_ms(260);
			LCD_clearScreen();
		}
		LCD_displayStringRowColumn(0,0,"Lat: ");
		LCD_displayStringRowColumn(1,0,(char*)t_GPS_Coordinates.Latitude);
		LCD_displayStringRowColumn(2,0,"Lon: ");
		LCD_displayStringRowColumn(3,0,(char*)t_GPS_Coordinates.Longitude);
		_delay_ms(260);
		_delay_ms(260);
	}

	/*TIRES STATE PART*/
	ESP_sendTiresState(CAR_ID, Temperature, Pressure);

}
