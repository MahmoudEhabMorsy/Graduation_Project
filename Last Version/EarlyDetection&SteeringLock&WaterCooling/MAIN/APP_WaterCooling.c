///*
// * APP.c
// *
// *  Created on: Apr 16, 2023
// *      Author: HP
// */
//
//
//#include "../ECUAL/LCD/lcd.h"
//#include "../MCAL/DIO/dio.h"
//#include "../ECUAL/BMP/bmp180.h"
//#include "../ECUAL/keypad/keypad.h"
//#include <util/delay.h>
//
//#define WCS_TEMP_HIGH	30
//#define LED_PORT		PORTA_ID
//#define PUMP_PORT		PORTD_ID
//#define LED_PIN			PIN4_ID
//#define PUMP_PIN		PIN4_ID
//#define PRESSED			1
//#define NOT_PRESSED		0
//
//uint32 temperature = 0;
//
//void WCS_displayTemp(uint32 temperature)
//{
//	LCD_moveCursor(1,7);
//	if ((1000 <= temperature) || (0 > temperature))
//	{
//		LCD_displayString("ERR");
//	}
//	else if(100 <= temperature)
//	{
//		LCD_intgerToString(temperature);
//	}
//	else if((10 <= temperature) && (100 > temperature))
//	{
//		LCD_intgerToString(temperature);
//		LCD_displayString(" ");
//	}
//	else if((0 <= temperature) && (10 > temperature))
//	{
//		LCD_intgerToString(temperature);
//		LCD_displayString("  ");
//	}
//}
//
//void WaterPump_init(void)
//{
//	DIO_setupPinDirection(PUMP_PORT,PUMP_PIN,PIN_OUTPUT);
//	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_LOW);
//}
//
//void LED_init(void)
//{
//	DIO_setupPinDirection(LED_PORT,LED_PIN,PIN_OUTPUT);
//	DIO_writePin(LED_PORT,LED_PIN,LOGIC_LOW);
//}
//
//void WCS_ActionValid(void)
//{
//	DIO_writePin(LED_PORT,LED_PIN,LOGIC_LOW);
//	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_LOW);
//	LCD_displayStringRowColumn(0,11,"OFF");
//}
//
//void WCS_ActionInvalid(void)
//{
//	DIO_writePin(LED_PORT,LED_PIN,LOGIC_HIGH);
////	DIO_writePin(PUMP_PORT,PUMP_PIN,LOGIC_HIGH);
//	LCD_displayStringRowColumn(0,11,"ON ");
//}
//
//void WCS_Detection(uint32 temperature)
//{
//	if (temperature > WCS_TEMP_HIGH)
//	{
//		WCS_ActionInvalid();
//	}
//	else
//	{
//		WCS_ActionValid();
//	}
//}
//
//void WCS_KEYPAD_init(void)
//{
//	DIO_setupPinDirection(PORTC_ID,PIN2_ID,PIN_INPUT);
//	DIO_setupPinDirection(PORTC_ID,PIN3_ID,PIN_INPUT);
//}
//
//void WCS_ControlTemp(uint8 key)
//{//c2,c3
//	if(key == 16){
////		_delay_ms(500);
//		temperature++;
//	}
//	else if(key == 15){
////		_delay_ms(500);
//		temperature--;
//	}
//}
//
////void main(void)
////{
////	unsigned char key = 0;
////
////	DIO_setupPinDirection(PORTA_ID,PIN1_ID,PIN_OUTPUT);
////	DIO_writePin(PORTA_ID,PIN1_ID,LOGIC_LOW);
////
////	WCS_KEYPAD_init();
////	LED_init();
////	WaterPump_init();
////	LCD_init();
////	//TWI_init();
////	//BMP180_Start();
////
////	LCD_displayStringRowColumn(0,0,"Water Pump ");
////	LCD_displayStringRowColumn(1,0,"Temp = ");
////	LCD_displayStringRowColumn(1,11,"C");
////
////	while(1)
////	{
////    	key = KEYPAD_getPressedKey();
////		WCS_ControlTemp(key);
//////		temperature = BMP180_calculateTemperature();
////		WCS_displayTemp(temperature);
////		WCS_Detection(temperature);
////		_delay_ms(200);
////	}
////}
////
