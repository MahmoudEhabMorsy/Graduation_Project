/*
 * esp.h
 *
 *  Created on: Feb 14, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef ESP_H_
#define ESP_H_

#include "../../UTILITIES/std_types.h"
#include "../../MCAL/UART/uart.h"
#include <string.h>
#include <util/delay.h>
#include "../../MCAL/SPI/spi.h"
#include "../../MCAL/DIO/dio.h"
#include "../../UTILITIES/utilities.h"
#include "../../MCAL/INTERRUPTS/interrupts.h"


#define ESP_VCC_PIN PIN6_ID
#define ESP_PORT PORTD_ID

#define DISABLE_ECHO (const uint8*)"ATE0\r\n"
#define STATION_MODE (const uint8*)"AT+CWMODE=1\r\n"
#define MAXIMUM_LENGTH (6u)
#define BAUD_RATE (115200u)
#define DEFAULT_APP_BAUD_RATE (9600u)
#define SERVER_IP (const uint8*) "34.122.187.191"

/*Application Specific Segment*/
#define TEMPERATURE_VARIABLE_LENGTH 4
#define PRESSURE_VARIABLE_LENGTH 4
#define BMP_DATA_IS_NOT_READY 0
#define BMP_DATA_IS_READY 1

typedef enum
{
	FRONT_LEFT_TIRE, FRONT_RIGHT_TIRE, REAR_LEFT_TIRE, REAR_RIGHT_TIRE
}wheeL_ID;

typedef struct
{
	wheeL_ID tire;
	sint32 Temperature;
	sint32 Pressure;
}tireState;

void ESP_preInit(void);
/*End of "Application Specific Segment"*/
void ESP_init(void);

void ESP_deInit(void);

void ESP_networkConnect(const uint8 *Username, const uint8 *Password);

void ESP_serverConnect(const uint8 *IP,const uint8 *Port);

void ESP_serverDisconnect(void);

void ESP_sendGETRequest(uint8 *GET_Request);

void ESP_readDataFromServer(uint8 *GET_Request, uint8 *Value);

void ESP_writeDataToServer(uint8 *API_Key ,uint8 *fieldNumber,uint8 *Value);

void ESP_sendCoordinatesToServer(const uint8* car_id, uint8 *longitude, uint8 *latitude);

//void ESP_sendTiresState(const uint8* car_id, sint32 Temperature, sint32 Pressure);
void ESP_sendTiresState(const uint8* car_id);

void ESP_sendDataToServer(uint8 *JSON_Request);


#endif /* ESP_H_ */
