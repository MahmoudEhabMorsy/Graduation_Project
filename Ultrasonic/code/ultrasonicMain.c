/*
 ================================================================================================
 Name        : ultrasonicMain.c

 Author      : Abdelrahman Hesham

 Description : Measure distance using ultrasonic and display it on an LCD.

 Created on  : Jun 27, 2022
 ================================================================================================
 */
#include "ultrasonic.h"
#include "lcd.h"
#include  <util/delay.h>
#include  <avr/interrupt.h>

int main()
{
	uint16 LCD_distance; /*distance shown on the LCD screen*/
	sei(); /*enabling global interrupt*/
	LCD_init(); /*initializing LCD*/
	Ultrasonic_init(); /*initializing Ultrasonic*/
	LCD_displayString("Distance=    cm");

	while(1){
		LCD_distance=Ultrasonic_readDistance(); /*storing the measured distance*/
		LCD_moveCursor(0, 10);
		if(LCD_distance>=100)                  /*LCD handling*/
			LCD_intgerToString(LCD_distance);
		else{
			LCD_intgerToString(LCD_distance);
			LCD_displayCharacter(' ');
		}
	}
}
