/*
 * led.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef ECUAL_LED_LED_H_
#define ECUAL_LED_LED_H_

#include "../../MCAL/DIO/gpio.h"
#include "../../UTILITIES/common_macros.h"

#define LED_PIN PIN5_ID
#define LED_PORT PORTA_ID

void LED_init(uint8 port_number, uint8 pin_number);

void LED_ON(uint8 port_number, uint8 pin_number);

void LED_OFF(uint8 port_number, uint8 pin_number);

void LED_TOGGLE(uint8 port_number, uint8 pin_number);

uint8 LED_IS_ON(uint8 port_number, uint8 pin_number);

#endif /* ECUAL_LED_LED_H_ */
