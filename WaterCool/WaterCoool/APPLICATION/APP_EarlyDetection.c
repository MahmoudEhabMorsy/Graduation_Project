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

#define TEMP_LOW		20
#define TEMP_HIGH		40
#define PRESS_LOW		600
#define PRESS_HIGH		800
#define LED_PORT		PORTD_ID
#define BUZZER_PORT		PORTD_ID
#define LED_PIN			PIN3_ID
#define BUZZER_PIN		PIN4_ID


void LCD_displayTemp(uint32 temperature)
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

void LCD_displayPress(uint32 pressure)
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
	if ((temperature < TEMP_LOW) || (temperature > TEMP_HIGH) || (pressure < PRESS_LOW) || (pressure > PRESS_HIGH))
	{
		EDS_ActionInvalid();
	}
	else
	{
		EDS_ActionValid();
	}
}

int main(void)
{
	uint32 temperature = 0;
	uint32 pressure = 0;

	LED_Buzzer_init();
	LCD_init();
	TWI_init();
	BMP180_Start();

	LCD_displayStringRowColumn(0,0,"Press = ");
	LCD_displayStringRowColumn(0,13,"hPa");
	LCD_displayStringRowColumn(1,0,"Temp = ");
	LCD_displayStringRowColumn(1,11,"C");

	while(1)
	{
		temperature = BMP180_calculateTemperature();
		pressure = BMP180_calculatePressure();
		LCD_displayTemp(temperature);
		LCD_displayPress(pressure);
		EDS_Detection(temperature,pressure);
		_delay_ms(1000);
	}
	return 0;
}
