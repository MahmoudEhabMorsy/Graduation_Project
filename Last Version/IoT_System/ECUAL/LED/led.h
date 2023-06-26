/*
 * led.h
 *
 *  Created on: Jan 1, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef ECUAL_LED_LED_H_
#define ECUAL_LED_LED_H_

#include "../../MCAL/DIO/dio.h"
#include "../../UTILITIES/common_macros.h"
#include "../../UTILITIES/std_types.h"
#include <util/delay.h>

/*
 * DIO
 * LED_init, LED_ON and LED_OFF functions
 * */
void LED_init(uint8 port_number, uint8 pin_number);

void LED_ON(uint8 port_number, uint8 pin_number);

void LED_OFF(uint8 port_number, uint8 pin_number);

void LED_TOGGLE(uint8 port_number, uint8 pin_number);

uint8 LED_IS_ON(uint8 port_number, uint8 pin_number);

#endif /* ECUAL_LED_LED_H_ */
