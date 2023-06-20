/*
 ================================================================================================
 Name        : ultrasonicMain.c


 Description : Measure distance using ultrasonic and display it on an LCD.

 ================================================================================================
 */
#include "../ECUAL/ULTRASONIC/ultrasonic.h"
#include "../ECUAL/LCD/lcd.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "../ECUAL/BUZZER/buzzer.h"
#include "../ECUAL/LED/led.h"
#include "../MCAL/TIMER/timer.h"
#include "../UTILITIES/common_macros.h"
#include <avr/io.h>

#define LOW_RISK_DISTANCE_UPPER_LIMIT (40u)
#define LOW_RISK_DISTANCE_LOWER_LIMIT (30u)
#define MODERATE_RISK_DISTANCE_UPPER_LIMIT (30u)
#define MODERATE_RISK_DISTANCE_LOWER_LIMIT (20u)
#define HIGH_RISK_DISTANCE_UPPER_LIMIT (20u)
#define HIGH_RISK_DISTANCE_LOWER_LIMIT (10u)
#define EXTREME_RISK_DISTANCE_UPPER_LIMIT (10u)


void warning(uint16 Distance);

typedef enum
{
	SAFE_DISTANCE, /*More Than 40 CMs*/
	LOW_RISK_DISTANCE, /*Between 40 and 30 CMs*/
	MODERATE_RISK_DISTANCE, /*Between 30 and 20 CMs*/
	HIGH_RISK_DISTANCE, /*Between 20 and 10 CMs*/
	EXTREME_RISK_DISTANCE /*Less Than or Equal to 10 CMs*/
} t_ULTRASONIC_INTERVAL;

t_ULTRASONIC_INTERVAL ultrasonicInterval;

/*void timercallBckFunc(void)
{	static uint8 counter=0;

	switch(ultrasonicInterval)
	{
	case LOW_RISK_DISTANCE:
	//we need to make the buzzer on for 400ms and off for 100ms
	//to make it on for 100ms we need the timer to overflow 6 times
	//to make it off for 100ms we need the timer to overflow 6 times
	//so the buzzer will toggle when counter is 24
		if(counter == 24)
		{
			Buzzer_toggle();
			LED_TOGGLE(LED_PORT,LED_PIN);
			counter = 0;
		}
		else
		{
			counter++;
		}
		break;

	case MODERATE_RISK_DISTANCE:
	//we need to make the buzzer toggle each 300ms
	//so it will toggle when counter is 18
	if(counter > 18)
	{
		counter = 0;
	}
		if(counter == 18)
		{
			Buzzer_toggle();
			LED_TOGGLE(LED_PORT,LED_PIN);
			counter = 0;
		}
		else
		{
			counter++;
		}
		break;

	case HIGH_RISK_DISTANCE:
	//we need to make the buzzer toggle each 200ms
	//so it will toggle when counter is 12
	if(counter > 12)
	{
		counter = 0;
	}
		if(counter == 12)
		{
			Buzzer_toggle();
			LED_TOGGLE(LED_PORT,LED_PIN);
			counter = 0;
		}
		else
		{
			counter++;
		}
		break;

	case EXTREME_RISK_DISTANCE:
	//we need to make the buzzer toggle each 100ms
	//so it will toggle when counter is 6
	if(counter > 6)
	{
		counter = 0;
	}
		if(counter == 6)
		{
			Buzzer_toggle();
			LED_TOGGLE(LED_PORT,LED_PIN);
			counter = 0;
		}
		else
		{
			counter++;
		}
		break;

	default:
		Buzzer_off();
		LED_OFF(LED_PORT,LED_PIN);
		counter = 0;
		break;
	}
}
*/
//Timer_configuration Timer0_Configuration={Timer0,Normal,TIMER_INITIAL_VALUE,NO_COMPARE_VALUE,Prescaler_1024,timercallBckFunc};


int main()
{

	uint16 LCD_distance; /*distance shown on the LCD screen*/
	LCD_init(); /*initializing LCD*/
	Ultrasonic_init(); /*initializing Ultrasonic*/
	//Buzzer_init();
	//LED_init();
	LCD_displayString(" Distance=    cm");
	//Timer_init(&Timer0_Configuration);
	sei(); /*enabling global interrupt*/
	while(1)
	{
		LCD_distance = Ultrasonic_readDistance(); /*storing the measured distance*/
		LCD_moveCursor(0, 10);
		if(LCD_distance >= 100)                  /*LCD handling*/
			LCD_intgerToString(LCD_distance);
		else
		{
			LCD_intgerToString(LCD_distance);
			LCD_displayCharacter(' ');
		}
		warning(LCD_distance); /*warning function*/
	}
}


void warning(uint16 Distance)
{
	if(Distance <= LOW_RISK_DISTANCE_UPPER_LIMIT && Distance > LOW_RISK_DISTANCE_LOWER_LIMIT)
	{
		ultrasonicInterval = LOW_RISK_DISTANCE;
		Timer_reset(Timer0);
	}
	else if(Distance <= MODERATE_RISK_DISTANCE_UPPER_LIMIT && Distance > MODERATE_RISK_DISTANCE_LOWER_LIMIT)
	{
		ultrasonicInterval = MODERATE_RISK_DISTANCE;
		Timer_reset(Timer0);
	}
	else if(Distance <= HIGH_RISK_DISTANCE_UPPER_LIMIT && Distance > HIGH_RISK_DISTANCE_LOWER_LIMIT)
	{
		ultrasonicInterval = HIGH_RISK_DISTANCE;
		Timer_reset(Timer0);
	}
	else if(Distance <= EXTREME_RISK_DISTANCE_UPPER_LIMIT)
	{
		ultrasonicInterval = EXTREME_RISK_DISTANCE;
		Timer_reset(Timer0);
	}
	else
	{
		ultrasonicInterval = SAFE_DISTANCE;
		Timer_reset(Timer0);
	}
}
