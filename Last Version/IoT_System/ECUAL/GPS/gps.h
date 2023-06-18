/*
 * gps.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Mahmoud Qotp
 */

#ifndef GPS_H_
#define GPS_H_
#include "std_types.h"
#include "gpio.h"

#define GPS_PORT PORTD_ID
#define GPS_VCC_PIN PIN7_ID

#define VALID_GPS_DATA 0
#define VOID_GPS_DATA 1
#define INCORRECT_GPS_READING_PROCESS 2

typedef struct
{
	uint8 Latitude[14];
	uint8 Longitude[14];
}GPS_Coordinates;

void GPS_init(void);

void GPS_deInit(void);

void GPS_reInit(void);

uint8 GPS_getCoordinates(GPS_Coordinates *Coordinates);

#endif /* GPS_H_ */
