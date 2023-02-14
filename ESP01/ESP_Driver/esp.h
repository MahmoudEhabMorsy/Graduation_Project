/*
 * esp.h
 *
 *  Created on: Feb 14, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef ESP_H_
#define ESP_H_

#include "std_types.h"
#include "uart.h"
#include <string.h>
#include <util/delay.h>

void ESP_init(void);

uint8 ESP_networkConnect(uint8 *Username, uint8 *Password);

void ESP_serverConnect(uint8 *IP, uint8 *Port);

uint8 ESP_receiveDataFromServer(uint8 *stringLength, uint8 *String);

#endif /* ESP_H_ */
