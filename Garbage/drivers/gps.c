/*
 * gps.c
 *
 *  Created on: Dec 17, 2022
 *      Author: Mahmoud Qotp
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uart.h"
#include "gps.h"

/*Module: ublox NEO-6M GPS module
 * UART Frame specs:
 * 	Baud Rate: 9600 (Default).
 * 	8 Data bits.
 * 	1 Stop bit.
 * 	No Parity.
 * 	No Flow Control.
*/

void GPS_init()
{
	UART_init();
}



void GPS_getCoordinates(float64 *a_latitude, float64 *a_longitude)
{
	uint8 Commas = 0, i;
	uint8 gpsData[55];
	uint8 *a_stringLatitude, *a_latitudeDirection, *a_stringLongitude, *a_longitudeDirection;
	uint8 *dummy;
	/*	uint8 *a_verifier;*/

	/*GPGLL Line Example: $GPGLL,3401.21044,N,11824.67722,W,044840.00,A,D*7F */
	/*$GPGLL,
	 * Latitude multiplied by 100 (Format: ddmm.mmmm),
	 * N or S,
	 * Longitude multiplied by 100 (Format: ddmm.mmmm),
	 * W or E, Time,
	 * Data Validation character: A which represents valid data or V which represents invalid data.*/

	while(1)
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
										if(UART_receiveByte() == 'A') /*Check if the data is valid.*/
										{
											Commas = 0;
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

		/*Extracting Latitude and Longitude values as strings.*/

	strtok(gpsData,","); /*Ignoring GPGLL Identifier*/
	a_stringLatitude = strtok(NULL,","); /*Latitude value as a string*/
	a_latitudeDirection = strtok(NULL,","); /*Latitude direction (N = +ve | S = -ve)*/
	a_stringLongitude = strtok(NULL,","); /*Longitude value as a string*/
	a_longitudeDirection = strtok(NULL,","); /*Longitude direction (E = +ve | W = -ve)*/

		/*Getting the value of latitude as double. Example of the value: 3401.21044*/
		/*Ex: Lat = 34 + (01.21044)/60*/
	*a_latitude = strtod(a_stringLatitude, &dummy);
	*a_latitude = (int)(*a_latitude/100)+((*a_latitude-((int)(*a_latitude/100)*100))/60);
	if(strcmp(a_latitudeDirection, "S") == 0) /*If the latitude direction is south*/
	{
		*a_latitude *= -1;
	}

		/*Getting the value of longitude as double. Example of the value: 11824.67722*/
		/*Ex: Lon = 118 + (24.67722)/60*/
	*a_longitude = strtod(a_stringLongitude, &dummy);
	*a_longitude = (int)(*a_longitude/100)+((*a_longitude-((int)(*a_longitude/100)*100))/60);
	if(strcmp(a_longitudeDirection, "W") == 0) /*If the latitude direction is west*/
	{
		*a_longitude *= -1;
	}
}
