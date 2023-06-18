/*
 * APP.c
 *
 *  Created on: Apr 16, 2023
 *      Author: HP
 */


#include "../ECUAL/LCD/lcd.h"
#include "../MCAL/DIO/dio.h"
#include "../ECUAL/BMP/bmp180.h"
#include <util/delay.h>

#define EDS_TEMP_LOW	20
#define EDS_TEMP_HIGH	40
#define EDS_PRESS_LOW	600
#define EDS_PRESS_HIGH	800
#define LED_PORT		PORTA_ID
#define BUZZER_PORT		PORTC_ID
#define LED_PIN			PIN4_ID
#define BUZZER_PIN		PIN6_ID


void EDS_displayTemp(uint32 temperature)
{
	LCD_moveCursor(1,7);
	if ((1000 <= temperature) || (0 > temperature))
	{
		LCD_displayString("ERR");
	}
	else if(100 <= temperature)
	{
		LCD_intgerToString(temperature);
	}
	else if((10 <= temperature) && (100 > temperature))
	{
		LCD_intgerToString(temperature);
		LCD_displayString(" ");
	}
	else if((0 <= temperature) && (10 > temperature))
	{
		LCD_intgerToString(temperature);
		LCD_displayString("  ");
	}
}

void EDS_displayPress(uint32 pressure)
{
	LCD_moveCursor(0,8);
	if ((10000 <= pressure) || (0 > pressure))
	{
		LCD_displayString("ERR");
		LCD_displayString(" ");
	}
	else if((1000 <= pressure) && (10000 > pressure))
	{
		LCD_intgerToString(pressure);
	}
	else if((100 <= pressure) && (1000 > pressure))
	{
		LCD_intgerToString(pressure);
		LCD_displayString(" ");
	}
	else if((10 <= pressure) && (100 > pressure))
	{
		LCD_intgerToString(pressure);
		LCD_displayString("  ");
	}
	else if((0 <= pressure) && (10 > pressure))
	{
		LCD_intgerToString(pressure);
		LCD_displayString("   ");
	}
}

void LED_Buzzer_init(void)
{
	DIO_setupPinDirection(LED_PORT,LED_PIN,PIN_OUTPUT);
	DIO_setupPinDirection(BUZZER_PORT,BUZZER_PIN,PIN_OUTPUT);
	DIO_setupPinDirection(PORTA_ID,PIN1_ID,PIN_OUTPUT);
	DIO_writePin(LED_PORT,LED_PIN,LOGIC_LOW);
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
	DIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
}

void EDS_ActionValid(void)
{
	DIO_writePin(LED_PORT,LED_PIN,LOGIC_LOW);
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_LOW);
}

void EDS_ActionInvalid(void)
{
	DIO_writePin(LED_PORT,LED_PIN,LOGIC_HIGH);
	DIO_writePin(BUZZER_PORT,BUZZER_PIN,LOGIC_HIGH);
}

void EDS_Detection(uint32 temperature, uint32 pressure)
{
	if ((temperature < EDS_TEMP_LOW) || (temperature > EDS_TEMP_HIGH) || (pressure < EDS_PRESS_LOW) || (pressure > EDS_PRESS_HIGH))
	{
		EDS_ActionInvalid();
	}
	else
	{
		EDS_ActionValid();
	}
}

//void main(void)
//{
//	uint32 temperature = 0;
//	uint32 pressure = 0;
//
//	LED_Buzzer_init();
//	_delay_ms(100);
//	LCD_init();
//	_delay_ms(100);
//	TWI_init();
//	_delay_ms(100);
//	BMP180_Start();
//	_delay_ms(100);
//
//	LCD_displayStringRowColumn(0,0,"Press = ");
//	_delay_ms(100);
//	LCD_displayStringRowColumn(0,13,"hPa");
//	_delay_ms(100);
//	LCD_displayStringRowColumn(1,0,"Temp = ");
//	_delay_ms(100);
//	LCD_displayStringRowColumn(1,11,"C");
//	_delay_ms(100);
//
//	while(1)
//	{
//		temperature = BMP180_calculateTemperature();
//		_delay_ms(100);
//		pressure = BMP180_calculatePressure();
//		_delay_ms(100);
//		EDS_displayTemp(temperature);
//		_delay_ms(100);
//		EDS_displayPress(pressure);
//		_delay_ms(100);
//		EDS_Detection(temperature,pressure);
//		_delay_ms(1000);
//	}
//}
