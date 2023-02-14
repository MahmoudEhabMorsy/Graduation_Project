/*
 * esp.c
 *
 *  Created on: Feb 14, 2023
 *      Author: Mahmoud Qotp
 */

#include "esp.h"

void ESP_init(void)
{
	uint8 chr;

	/*Initialize UART*/
	UART_init(115200);

	/*Disable Echo*/
	UART_sendString("ATE0\r\n");

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

	/*Station Mode*/
	UART_sendString("AT+CWMODE=1\r\n");
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
}

uint8 ESP_networkConnect(uint8 *Username, uint8 *Password)
{
	/*connect to Wi-Fi*/
	/*AT+CWJAP_CUR="WiFi_Name","WiFi_Pass"*/
	UART_sendString("AT+CWJAP_CUR=\"");
	UART_sendString(Username);
	UART_sendString("\",\"");
	UART_sendString(Password);
	UART_sendString("\"\r\n");

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
}

void ESP_serverConnect(uint8 *IP, uint8 *Port)
{
	/*connect to server*/
	/*8: AT+CIPSTART="mode","IP",Port*/
	/*TCP Mode By Default*/
	UART_sendString("AT+CIPSTART=\"TCP\",\"");
	UART_sendString(IP);
	UART_sendString("\",");
	UART_sendString(Port);
	UART_sendString("\r\n");

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
}

/* "GET http://mahmoud.freevar.com/status.txt\r\n" */
/*Length = "43" */
uint8 ESP_receiveDataFromServer(uint8 *stringLength, uint8 *String)
{
	uint8 arr[20], i;
	uint8 *tempLength, *Value;
	UART_sendString("AT+CIPSEND=");
	UART_sendString(stringLength);
	UART_sendString("\r\n");

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

	UART_sendString(String);

	/*+IPD, 1:0CLOSED*/
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

	i = 0;
	while (i < 20)
	{
		/*Number of Sent Data*/
		arr[i] = UART_receiveByte();
		if (arr[i] == 'C')
		{
			arr[i + 1] = '\0';
			break;
		}
		i++;
	}
	strtok(arr,","); /* nermy 7etta fel zebala */
	tempLength = strtok(NULL,":");
	Value = strtok(NULL,"C");
	return(*Value - '0');
}
