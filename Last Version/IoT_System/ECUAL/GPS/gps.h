/*
 * gps.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Mahmoud Qotp
 */

#ifndef GPS_H_
#define GPS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../UTILITIES/std_types.h"
#include "../../MCAL/UART/uart.h"
#include "../../MCAL/DIO/dio.h"

#define GPS_PORT PORTD_ID
#define GPS_VCC_PIN PIN7_ID

#define GPS_DEVICE_SELECTOR_PORT PORTA_ID
#define GPS_DEVICE_SELECTOR_PIN PIN0_ID

#define GPS_CALLIBRATED_SUCCESSFULLY_PORT PORTA_ID
#define GPS_CALLIBRATED_SUCCESSFULLY_PIN PIN3_ID

#define GPS_DID_NOT_CALLIBRATE_SUCCESSFULLY_PORT PORTA_ID
#define GPS_DID_NOT_CALLIBRATE_SUCCESSFULLY_PIN PIN5_ID

#define GPS_IS_CONNECTED LOGIC_LOW

#define VALID_GPS_DATA 0
#define VOID_GPS_DATA 1
#define INCORRECT_GPS_READING_PROCESS 2

typedef struct
{
	uint8 Latitude[14];
	uint8 Longitude[14];
}GPS_Coordinates;


extern GPS_Coordinates t_GPS_Coordinates;
extern uint8 GPS_DataValidation;

void GPS_init(void);

void GPS_deInit(void);

void GPS_reInit(void);

uint8 GPS_getCoordinates(GPS_Coordinates *Coordinates);

#endif /* GPS_H_ */
