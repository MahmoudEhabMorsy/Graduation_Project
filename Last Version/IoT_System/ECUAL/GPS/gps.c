/*
 * gps.c
 *
 *  Created on: Dec 17, 2022
 *      Author: Mahmoud Qotp
 */

#include "gps.h"
#include <util/delay.h>

/*Module: ublox NEO-6M GPS module
 * UART Frame specs:
 * 	Baud Rate: 9600 (Default).
 * 	8 Data bits.
 * 	1 Stop bit.
 * 	No Parity.
 * 	No Flow Control.
*/

GPS_Coordinates t_GPS_Coordinates;
uint8 GPS_DataValidation = VOID_GPS_DATA;

void GPS_init(void)
{
	DIO_setupPinDirection(GPS_PORT, GPS_VCC_PIN, PIN_OUTPUT);
	DIO_writePin(GPS_PORT, GPS_VCC_PIN, LOGIC_HIGH);
	_delay_us(1);
	UART_init(9600);
}

void GPS_reInit(void)
{
	DIO_writePin(GPS_PORT, GPS_VCC_PIN, LOGIC_HIGH);
	_delay_us(1);
	UART_init(9600);
}
void GPS_deInit(void)
{
	DIO_writePin(GPS_PORT, GPS_VCC_PIN, LOGIC_LOW);
	_delay_us(1);
}


uint8 GPS_getCoordinates(GPS_Coordinates *Coordinates)
{
	uint8 Commas = 0, i, validationChar = 2;
	uint8 gpsData[55];
	uint8 VoidData[] = "VOID.VOID";
	uint8 *a_latitudeDirection, *a_longitudeDirection;
	uint8 *a_stringLat, *a_stringLon;
	uint8 *dummy;
	float64 d_latitude;
	float64 d_longitude;
	/*	uint8 *a_verifier;*/

	/*GPGLL Line Example: $GPGLL,3401.21044,N,11824.67722,W,044840.00,A,D*7F */
	/*$GPGLL,
	 * Latitude multiplied by 100 (Format: ddmm.mmmm),
	 * N or S,
	 * Longitude multiplied by 100 (Format: ddmm.mmmm),
	 * W or E, Time,
	 * Data Validation character: A which represents valid data or V which represents invalid (void) data.*/
	uint16 timeout = 0;
	while(timeout < 65000)
	{
		/*Extracting the GPGLL Line from GPS received data.*/
		gpsData[0] = UART_receiveByte();
		if(gpsData[0] == '$')
		{
			gpsData[1] = UART_receiveByte();
			if(gpsData[1] == 'G')
			{
				gpsData[2] = UART_receiveByte();
				if(gpsData[2] == 'P')
				{
					gpsData[3] = UART_receiveByte();
					if(gpsData[3] == 'G')
					{
						gpsData[4] = UART_receiveByte();
						if(gpsData[4] == 'L')
						{
							gpsData[5] = UART_receiveByte();
							if(gpsData[5] == 'L')
							{
								for (i = 6; i < 55; i++)
								{
									gpsData[i]= UART_receiveByte();
									if (gpsData[i] == ',')
									{
										Commas++;
									}
									if (Commas == 6)
									{
										validationChar = UART_receiveByte();
										if(validationChar == 'A') /*Check if the data is valid.*/
										{
											Commas = 0;

											/*Extracting Latitude and Longitude values as strings.*/
											/*Ignoring GPGLL Identifier*/
											strtok(gpsData,",");

											/*Latitude value as a string*/
											a_stringLat = strtok(NULL,",");

											/*Latitude direction (N = +ve | S = -ve)*/
											a_latitudeDirection = strtok(NULL,",");

											/*Longitude value as a string*/
											a_stringLon = strtok(NULL,",");

											/*Longitude Direction (E = +ve | W = -ve)*/
											a_longitudeDirection = strtok(NULL,",");

											/*Getting the value of latitude as double. Example of the value: 3401.21044*/

											/*Ex: Lat = 34 + (01.21044)/60*/
											d_latitude = strtod(a_stringLat, &dummy);

											d_latitude = (uint32)(d_latitude/100)+((d_latitude-((int)(d_latitude/100)*100))/60);

											if(strcmp(a_latitudeDirection, "S") == 0) /*If the latitude direction is south*/
											{
												d_latitude *= -1;
											}

											/*Getting the value of longitude as double. Example of the value: 11824.67722*/
											/*Ex: Lon = 118 + (24.67722)/60*/
											d_longitude = strtod(a_stringLon, &dummy);

											d_longitude = (uint32)(d_longitude/100)+((d_longitude-((int)(d_longitude/100)*100))/60);

											if(strcmp(a_longitudeDirection, "W") == 0) /*If the latitude direction is west*/
											{
												d_longitude *= -1;
											}

											/*Converting Double values to strings to send them directly.*/
											floatToString(d_latitude,Coordinates->Latitude);
											floatToString(d_longitude,Coordinates->Longitude);

											return VALID_GPS_DATA;
										}
										else if(validationChar == 'V')
										{
											Commas = 0;
											strtok(gpsData,","); /*Ignoring GPGLL Identifier*/
											strcpy(Coordinates->Latitude, "VOID");
											strcpy(Coordinates->Longitude, "VOID");
											return VOID_GPS_DATA;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		timeout++;
	}
	return INCORRECT_GPS_READING_PROCESS;
}
