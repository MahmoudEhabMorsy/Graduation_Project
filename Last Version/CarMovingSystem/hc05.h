/*
 * hc05.h
 *
 *  Created on: Feb 24, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef HC05_H_
#define HC05_H_

/*Includes*/
#include <util/delay.h>
#include "uart.h"
#include "gpio.h"
#include "std_types.h"

/*Definitions*/
#define HC05_COMMANDS_BAUD_RATE 38400
#define DEFAULT_BAUD_RATE 115200
#define AT_COMMAND_CHECK_MODE (const uint8*)"AT\r\n"
#define AT_COMMAND_RESET_MODULE (const uint8*)"AT+RESET\r\n"
#define AT_COMMAND_SET_BAUD_RATE (const uint8*)"AT+UART=115200,1,0\r\n"
#define AT_COMMAND_CONNECT_FIXED_ADDRESS (const uint8*)"AT+CMODE=0\r\n"
#define AT_COMMAND_TO_SET_ROLE_AS_SLAVE (const uint8*)"AT+ROLE=0\r\n"
#define AT_COMMAND_TO_SET_ROLE_AS_MASTER (const uint8*)"AT+ROLE=1\r\n"
#define AT_COMMAND_CONNECT_TO_SLAVE_1 (const uint8*)"AT+BIND=IP\r\n"
#define AT_COMMAND_BIND_TO_SLAVE_2 (const uint8*)"AT+BIND=0022:06:019208\r\n"
#define AT_COMMAND_LINK_TO_SLAVE_2 (const uint8*)"AT+LINK=0022:06:019208\r\n"
#define AT_COMMAND_CONNECT_TO_SLAVE_3 (const uint8*)"AT+BIND=IP\r\n"
#define AT_COMMAND_CONNECT_TO_SLAVE_4 (const uint8*)"AT+BIND=IP\r\n"
#define VCC_PIN PIN7_ID
#define EN_PIN 	PIN2_ID
#define VCC_PORT PORTD_ID
#define EN_PORT PORTD_ID

/*Types definitions*/
typedef enum
{
	SLAVE,
	MASTER
}role;

/*Function Prototypes*/
void delay(uint8 seconds);

void HC05_init(role Role);

void HC05_sendByte(uint8 byteToSend);

uint8 HC05_receiveByte(void);

#endif /* HC05_H_ */
