/*
 * esp.c
 *
 *  Created on: Feb 14, 2023
 *      Author: Mahmoud Qotp
 */

#include "esp.h"

/*Interrupt Service Routine Segment*/

volatile tireState t_frontLeftTire = {FRONT_LEFT_TIRE, 0, 0}; /*Initially*/
volatile uint8 dummy_Byte = 0;
volatile uint8 BMP_Data = BMP_DATA_IS_NOT_READY;

ISR(INT1_vect)
{

	/*Receive Tire Data*/
	/*First, Receive Tire ID*/
	t_frontLeftTire.tire = SPI_sendReceiveByte(dummy_Byte);

	/*Second, Receive Tire Temperature Value*/
	for (uint8 i = 0; i < TEMPERATURE_VARIABLE_LENGTH; i++) {
		dummy_Byte = SPI_sendReceiveByte(dummy_Byte);
		t_frontLeftTire.Temperature = (t_frontLeftTire.Temperature | (dummy_Byte << (i * 8)));
	}

	/*Third, Receive Tire Pressure Value*/
	for (uint8 i = 0; i < PRESSURE_VARIABLE_LENGTH; i++) {
		dummy_Byte = SPI_sendReceiveByte(dummy_Byte);
		t_frontLeftTire.Pressure = (t_frontLeftTire.Pressure | (dummy_Byte << (i * 8)));
	}

	BMP_Data = BMP_DATA_IS_READY;
}

/*End of Interrupt Service Routine Segment*/

void ESP_preInit(void)
{
	INT1_Init();
	SPI_initSlave();
}
void ESP_init(void)
{
//	GPIO_setupPinDirection(ESP_PORT, ESP_VCC_PIN, PIN_OUTPUT);
//	GPIO_writePin(ESP_PORT, ESP_VCC_PIN, LOGIC_HIGH);
	/*Initialize UART*/
	UART_init(BAUD_RATE);

	/*Disable Echo*/
	UART_sendString(DISABLE_ECHO);

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
	UART_sendString(STATION_MODE);
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

void ESP_deInit(void)
{
	DIO_writePin(ESP_PORT, ESP_VCC_PIN, LOGIC_LOW);
	UART_init(DEFAULT_APP_BAUD_RATE);
}
void ESP_networkConnect(const uint8 *Username, const uint8 *Password)
{
	/*connect to Wi-Fi*/
	/*AT+CWJAP_CUR="WiFi_Name","WiFi_Pass"*/
	UART_sendString((const uint8*)"AT+CWJAP_CUR=\"");
	UART_sendString(Username);
	UART_sendString((const uint8*)"\",\"");
	UART_sendString(Password);
	UART_sendString((const uint8*)"\"\r\n");

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

void ESP_serverConnect(const uint8 *IP, const uint8 *Port)
{
	uint8 c;
	/*connect to server*/
	/*8: AT+CIPSTART="mode","IP",Port*/
	/*TCP Mode By Default*/
	UART_sendString((const uint8*)"AT+CIPSTATUS\r\n");

	while(1)
	{
		if(UART_receiveByte() == ':')
		{
			c = UART_receiveByte();
			break;
		}
	}

	if(c == '3')
	{
		UART_sendString((const uint8*)"AT+CIPCLOSE\r\n");
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

	UART_sendString((const uint8*)"AT+CIPSTART=\"TCP\",\"");
	UART_sendString(IP);
	UART_sendString((const uint8*)"\",");
	UART_sendString(Port);
	UART_sendString((const uint8*)"\r\n");

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

/* String = "GET http://mahmoud.freevar.com/status.txt\r\n" */
/* Value = is the return */
/*Still need work.*/

void ESP_sendGETRequest(uint8 *GET_Request)
{
	uint8 stringLength[MAXIMUM_LENGTH];
	uint8 integerLength = strlen(GET_Request);
	intToStr(integerLength,stringLength);

	uint8 arr[20], i;
	uint8 *tempLength;
	UART_sendString((const uint8*)"AT+CIPSEND=");
	UART_sendString(stringLength);
	UART_sendString((const uint8*)"\r\n");

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

	UART_sendString(GET_Request);

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

}
void ESP_readDataFromServer(uint8 *GET_Request, uint8 *Value)
{
	uint8 stringLength[MAXIMUM_LENGTH];
	uint8 integerLength = strlen(GET_Request);
	intToStr(integerLength,stringLength);

	uint8 arr[20], i;
	uint8 *tempLength;
	UART_sendString((const uint8*)"AT+CIPSEND=");
	UART_sendString(stringLength);
	UART_sendString((const uint8*)"\r\n");

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

	UART_sendString(GET_Request);

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
	strtok(arr,",");
	tempLength = strtok(NULL,":");
	Value = strtok(NULL,"C"); //Try to avoid Segmentation Fault
}



/* "GET /update?api_key=E3F314CY3VJGPB74&field1=20\r\n" */
/* "POST "*/
/*Length = "48" */
/*GET Function*/
void ESP_writeDataToServer(uint8 *API_Key ,uint8 *fieldNumber,uint8 *Value)
{
	uint8 stringLength[MAXIMUM_LENGTH];
	uint8 integerLength = strlen("GET /update?api_key=&field=\r\n")\
			+ strlen(API_Key) + strlen(Value) + strlen(fieldNumber);
	intToStr(integerLength,stringLength);

	UART_sendString((const uint8*)"AT+CIPSEND=");
	UART_sendString(stringLength);
	UART_sendString((const uint8*)"\r\n");

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

	UART_sendString((const uint8*)"GET /update?api_key=");
	UART_sendString(API_Key);
	UART_sendString((const uint8*)"&field");
	UART_sendString(fieldNumber);
	UART_sendByte('=');
	UART_sendString(Value);
	UART_sendString((const uint8*)"\r\n");

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

/*
AT+CIPSEND=118
POST /api/carconnect HTTP/1.1\r\n
Host:35.192.107.191\r\n
Content-Type:application/json\r\n
Content-Length:14\r\n\r\n
{"test":"3"}\r\n*/


/*NOTE: Content-Length is calculated with \r \n ( add 2 characters )
*/
/*Inputs: Structure of Pressures
 * 		  Structure of Temperatures
 * 		  Structure of Coordinates
 * 		  String Car ID
*/
void ESP_sendCoordinatesToServer(const uint8* car_id, uint8 *longitude, uint8 *latitude)
{
	uint8 requestLength[MAXIMUM_LENGTH];
	uint8 dataBodyLength[MAXIMUM_LENGTH];
	uint16 u16DataBodyLength = strlen(car_id) + strlen(longitude) + strlen(latitude) \
			+ strlen("{\"carID\":\"\",\"longitude\":\"\",\"latitude\":\"\"}\r\n");

	uint16 u16RequestLength = strlen("POST /api/carconnect HTTP/1.1\r\n")\
			+ strlen("Host:35.192.107.191\r\n")\
			+ strlen("Content-Type:application/json\r\n")\
			+ strlen("Content-Length:\r\n\r\n")\
			+ u16DataBodyLength;

	/*
	AT+CIPSEND=118
	POST /api/carconnect HTTP/1.1\r\n
	Host:35.192.107.191\r\n
	Content-Type:application/json\r\n
	Content-Length:14\r\n\r\n
	{\"ID\":\"640005cc524bdbb9e426b4f5\",\"Lon\":\"0.12345\"\"Lat\":63.42145}\r\n
	*/

	intToStr(u16DataBodyLength,dataBodyLength);
	u16RequestLength += strlen(dataBodyLength);
	intToStr(u16RequestLength,requestLength);

	UART_sendString((const uint8*)"AT+CIPSEND=");
	UART_sendString(requestLength);
	UART_sendString((const uint8*)"\r\n");

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

	UART_sendString((const uint8*)"POST /api/carconnect HTTP/1.1\r\n");
	UART_sendString((const uint8*)"Host:");
	UART_sendString(SERVER_IP);
	UART_sendString((const uint8*)"\r\n");
	UART_sendString((const uint8*)"Content-Type:application/json\r\n");
	UART_sendString((const uint8*)"Content-Length:");
	UART_sendString(dataBodyLength);
	UART_sendString((const uint8*)"\r\n");
	UART_sendString((const uint8*)"\r\n");
	UART_sendString((const uint8*)"{\"carID\":\"");
	UART_sendString(car_id);
	UART_sendString((const uint8*)"\",\"longitude\":\"");
	UART_sendString(longitude);
	UART_sendString((const uint8*)"\",\"latitude\":\"");
	UART_sendString(latitude);
	UART_sendString((const uint8*)"\"}\r\n");

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


//void ESP_sendTiresState(const uint8* car_id, sint32 Temperature, sint32 Pressure)
void ESP_sendTiresState(const uint8* car_id)
{
	/*Dummy Code Segment*/
	t_frontLeftTire.Temperature = 34;
	t_frontLeftTire.Pressure = 1123;
	BMP_Data = BMP_DATA_IS_READY;
	/*End of Dummy Code Segment*/

	uint8 Str_Temp[MAXIMUM_LENGTH];
	uint8 Str_Press[MAXIMUM_LENGTH];
	intToStr(t_frontLeftTire.Temperature, Str_Temp);
	intToStr(t_frontLeftTire.Pressure, Str_Press);

	uint8 requestLength[MAXIMUM_LENGTH];
	uint8 dataBodyLength[MAXIMUM_LENGTH];
	uint16 u16DataBodyLength = strlen(car_id) + strlen(Str_Temp) + strlen(Str_Press) \
			+ strlen("{\"carID\":\"\",\"FLTT\":\"\",\"FLTP\":\"\"}\r\n");

	uint16 u16RequestLength = strlen("POST /api/carconnect HTTP/1.1\r\n")\
			+ strlen("Host:35.192.107.191\r\n")\
			+ strlen("Content-Type:application/json\r\n")\
			+ strlen("Content-Length:\r\n\r\n")\
			+ u16DataBodyLength;

	if (BMP_Data == BMP_DATA_IS_READY)
	{
		/*
		AT+CIPSEND=118
		POST /api/carconnect HTTP/1.1\r\n
		Host:35.192.107.191\r\n
		Content-Type:application/json\r\n
		Content-Length:14\r\n\r\n
		{\"ID\":\"640005cc524bdbb9e426b4f5\",\"Lon\":\"0.12345\"\"Lat\":63.42145}\r\n
		*/

		intToStr(u16DataBodyLength,dataBodyLength);
		u16RequestLength += strlen(dataBodyLength);
		intToStr(u16RequestLength,requestLength);

		UART_sendString((const uint8*)"AT+CIPSEND=");
		UART_sendString(requestLength);
		UART_sendString((const uint8*)"\r\n");

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
		UART_sendString((const uint8*)"POST /api/carconnect HTTP/1.1\r\n");
		UART_sendString((const uint8*)"Host:");
		UART_sendString(SERVER_IP);
		UART_sendString((const uint8*)"\r\n");
		UART_sendString((const uint8*)"Content-Type:application/json\r\n");
		UART_sendString((const uint8*)"Content-Length:");
		UART_sendString(dataBodyLength);
		UART_sendString((const uint8*)"\r\n");
		UART_sendString((const uint8*)"\r\n");
		UART_sendString((const uint8*)"{\"carID\":\"");
		UART_sendString(car_id);
		UART_sendString((const uint8*)"\",\"FLTT\":\"");
		UART_sendString(Str_Temp);
		UART_sendString((const uint8*)"\",\"FLTP\":\"");
		UART_sendString(Str_Press);
		UART_sendString((const uint8*)"\"}\r\n");

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
		BMP_Data = BMP_DATA_IS_NOT_READY;
	}
	else
	{
		/*Do nothing*/
	}
}

/*POST JSON REQUEST*/
void ESP_sendDataToServer(uint8 *JSON_Request)
{
	uint8 requestLength[MAXIMUM_LENGTH];
	uint8 dataBodyLength[MAXIMUM_LENGTH];
	uint16 u16DataBodyLength = strlen(JSON_Request);
	uint16 u16RequestLength = strlen("POST /api/carconnect HTTP/1.1\r\n")\
			+ strlen("Host:35.192.107.191\r\n")\
			+ strlen("Content-Type:application/json\r\n")\
			+ strlen("Content-Length:\r\n\r\n")\
			+ u16DataBodyLength;
	/*
	AT+CIPSEND=118
	POST /api/carconnect HTTP/1.1\r\n
	Host:35.192.107.191\r\n
	Content-Type:application/json\r\n
	Content-Length:14\r\n\r\n
	{"test":"3"}\r\n*/
	intToStr(u16DataBodyLength,dataBodyLength);
	u16RequestLength += strlen(dataBodyLength);
	intToStr(u16RequestLength,requestLength);

	UART_sendString((const uint8*)"AT+CIPSEND=");
	UART_sendString(requestLength);
	UART_sendString((const uint8*)"\r\n");

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

	UART_sendString((const uint8*)"POST /api/carconnect HTTP/1.1\r\n");
	UART_sendString((const uint8*)"Host:35.192.107.191\r\n");
	UART_sendString((const uint8*)"Content-Type:application/json\r\n");
	UART_sendString((const uint8*)"Content-Length:");
	UART_sendString(dataBodyLength);
	UART_sendString((const uint8*)"\r\n");
	UART_sendString((const uint8*)"\r\n");
	UART_sendString(JSON_Request);

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
