/*
 * hc05.c
 *
 *  Created on: Feb 24, 2023
 *      Author: Mahmoud Qotp
*/
#include "hc05.h"

void delay(uint8 seconds)
{
	uint16 i = 0;
	uint16 quarterSeconds = seconds*4;
	while(i < quarterSeconds)
	{
		_delay_ms(250);
		i++;
	}
}

/*Operating UART: 115200*/
void HC05_init(role Role)
{
	UART_init(HC05_COMMANDS_BAUD_RATE);
	DIO_setupPinDirection(EN_PORT,EN_PIN,PIN_OUTPUT);
	DIO_setupPinDirection(VCC_PORT,VCC_PIN,PIN_OUTPUT);
	DIO_writePin(EN_PORT,EN_PIN,LOGIC_LOW);
	DIO_writePin(VCC_PORT,VCC_PIN,LOGIC_LOW);

	/*To start Command Mode:
	 * Initially: VCC -> LOW, EN -> LOW
	 * 1- SWITCH OFF VCC
	 * 2- WRITE 1 ON EN PIN
	 * 3- SET VCC
	 * 4- SEND COMMANDS BY UART
	 * 5- SWITCH OFF EN PIN
	 * 6- SWITCH OFF VCC
	 * 7- SWITCH ON VCC
	 * OR 5,6,7- RESET MODULE
	 * */

	/*OPEN COMMAND MODE*/
	_delay_ms(3);
	DIO_writePin(EN_PORT,EN_PIN,LOGIC_HIGH);
	_delay_ms(5);
	DIO_writePin(VCC_PORT,VCC_PIN,LOGIC_HIGH);
	delay(1); /*Optimized.*/
	DIO_writePin(EN_PORT,EN_PIN,LOGIC_LOW);
	delay(2); /*Optimized.*/

	/*"AT+UART=115200,1,0\r\n"*/
	UART_sendString(AT_COMMAND_SET_BAUD_RATE);

	/*AT+PSWD=9999\r\n*/
	UART_sendString("AT+PSWD=1234\r\n");

	/*AT+CMODE=0*/
	UART_sendString(AT_COMMAND_CONNECT_FIXED_ADDRESS);

	/*AT+ROLE=Role\r\n*/
	switch(Role)
	{
	case SLAVE:
		UART_sendString(AT_COMMAND_TO_SET_ROLE_AS_SLAVE);
		break;
	case MASTER:
		UART_sendString(AT_COMMAND_TO_SET_ROLE_AS_MASTER);
		UART_sendString(AT_COMMAND_BIND_TO_SLAVE_2);
		UART_sendString(AT_COMMAND_LINK_TO_SLAVE_2);
		break;
	default:
		/*Default is Slave*/
		UART_sendString(AT_COMMAND_TO_SET_ROLE_AS_SLAVE);
		break;
	}

	/*Case of Master:*/
	/*AT+BIND=IP*/
	/*AT+ADDR? -> return your address*/
	/*AT+BIND? -> returns IP that you are connected to*/


	/*CLOSE COMMAND MODE*/

	UART_sendString(AT_COMMAND_RESET_MODULE);
	while(1)
	{
		if(UART_receiveByte() == 'O')
		{
			if(UART_receiveByte() == 'K')
			{
				break;
			}
		}
	}
	UART_init(DEFAULT_BAUD_RATE);
}

/*Master Function to send data*/
void HC05_sendByte(uint8 byteToSend)
{
	UART_sendByte(byteToSend);
}

/*Slave Function to receive data*/
uint8 HC05_receiveByte(void)
{
	uint8 receivedChar = UART_receiveByte();
	return receivedChar;
}
/*LATER: Master Function to request data*/
