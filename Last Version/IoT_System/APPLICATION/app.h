/*
 * app.h
 *
 *  Created on: Jun 18, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_


/*******************************************************************************
 *                                  Includes                                   *
 *******************************************************************************/
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/GPS/gps.h"
#include "../ECUAL/ESP01/esp.h"
#include "../MCAL/SPI/spi.h"
#include <avr/interrupt.h>


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define SSID (const uint8*) "MQOTP"
#define PASSWORD (const uint8*) "90900000"

#define THINGSPEAK_SERVER_IP (const uint8*) "184.106.153.149"
#define THINGSPEAK_SERVER_URL (const uint8*) "api.thingspeak.com"
#define SW_TEAM_SERVER_IP (const uint8*) "34.122.187.191"

#define IP (const uint8*) "34.122.187.191"
#define PORT (const uint8*) "80"
#define API_KEY (const uint8*) "E3F314CY3VJGPB74"
#define CAR_ID (const uint8*) "63d5343990599fb5c8ce4c48"

#define TEMPERATURE_VARIABLE_LENGTH 4
#define PRESSURE_VARIABLE_LENGTH 4

typedef enum
{
	FRONT_LEFT_TYRE, FRONT_RIGHT_TYRE, REAR_LEFT_TYRE, REAR_RIGHT_TYRE
}wheeL_ID;

typedef struct
{
	wheeL_ID tyre;
	sint32 Temperature;
	sint32 Pressure;
}tyreState;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void app_Init(void);
void app_Start(void);
uint8 GPS_sendingCoordinatesTask(void);
void BMP180_sendingDataTask(void);

#endif /* APPLICATION_APP_H_ */
