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
#include "../ECUAL/LED/led.h"
#include "../ECUAL/GPS/gps.h"
#include "../ECUAL/ESP01/esp.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define SSID (const uint8*) "Mahmoud"
#define PASSWORD (const uint8*) "12345678"

#define THINGSPEAK_SERVER_IP (const uint8*) "184.106.153.149"
#define THINGSPEAK_SERVER_URL (const uint8*) "api.thingspeak.com"
#define SW_TEAM_SERVER_IP (const uint8*) "34.122.187.191"

#define IP (const uint8*) "34.122.187.191"
#define PORT (const uint8*) "80"
#define API_KEY (const uint8*) "E3F314CY3VJGPB74"
#define CAR_ID (const uint8*) "63d5343990599fb5c8ce4c48"


#define GPS_CALLIBRATION_SUCCEED 0
#define GPS_CALLIBRATION_FAILED 1

#define ESP_CONNECTION_SUCCEED 0
#define ESP_CONNECTION_FAILED 1

#define ESP_CONNECTION_SUCCESS_INDICATION_PORT PORTA_ID
#define ESP_CONNECTION_SUCCESS_INDICATION_PIN PIN1_ID

#define ESP_CONNECTION_FAIL_INDICATION_PORT PORTA_ID
#define ESP_CONNECTION_FAIL_INDICATION_PIN PIN2_ID

#define GPS_CALLIBRATION_SUCCESS_INDICATION_PORT PORTA_ID
#define GPS_CALLIBRATION_SUCCESS_INDICATION_PIN PIN3_ID

#define GPS_CALLIBRATION_FAIL_INDICATION_PORT PORTA_ID
#define GPS_CALLIBRATION_FAIL_INDICATION_PIN PIN5_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void app_Init(void);
void app_Start(void);
void GPS_sendingCoordinatesTask(void);
void BMP180_sendingDataTask(void);

#endif /* APPLICATION_APP_H_ */
