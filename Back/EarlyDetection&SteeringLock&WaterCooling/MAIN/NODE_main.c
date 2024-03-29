
#include "../ECUAL/BMP/bmp180.h"
//#include "../APPLICATION/APP_EarlyDetection.h"
//#include "../APPLICATION/APP_SteeringLock.h"
//#include "../APPLICATION/APP_WaterCooling.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/DIO/dio.h"
#include "../ECUAL/BUZZER/buzzer.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../ECUAL/WATERPUMP/waterpump.h"

typedef enum state{
	SAFE, MODERATE, SEVERE
}STATE;

#define PRESSURE_SEVERE				100000
#define PRESSURE_MODERATE			10000
#define PRESSURE_SAFE				300
#define SLS_FLAG_PORT				PORTB_ID
#define SLS_FLAG_PIN				PIN7_ID
#define TEMPERATURE_SEVERE			45
#define TEMPERATURE_MODERATE		35
#define TEMPERATURE_SAFE			0

tyreState g_readings = {0,0,0};
uint16 g_rpm = 0;

STATE P_state = SAFE;
STATE T_state = SAFE;


void Temp_state(void)
{
	if (g_readings.temperature >= TEMPERATURE_SEVERE)
	{
		T_state = SEVERE;
	}
	else if ((g_readings.temperature >= TEMPERATURE_MODERATE) && (g_readings.temperature < TEMPERATURE_SEVERE))
	{
		T_state = MODERATE;
	}
	else if ((g_readings.temperature >= TEMPERATURE_SAFE) && (g_readings.temperature < TEMPERATURE_MODERATE))
	{
		T_state = SAFE;
	}
}

void Press_state(void)
{
	if (g_readings.pressure >= PRESSURE_SEVERE)
	{
		P_state = SEVERE;
	}
	else if ((g_readings.pressure >= PRESSURE_MODERATE) && (g_readings.pressure < PRESSURE_SEVERE))
	{
		P_state = MODERATE;
	}
	else if ((g_readings.pressure >= PRESSURE_SAFE) && (g_readings.pressure < PRESSURE_MODERATE))
	{
		P_state = SAFE;
	}
}

void Action_severe(void)
{
	BUZZER_on();
	if (T_state == SEVERE || T_state == MODERATE)
	{
		WATERPUMP_on();
	}
	else
	{
		WATERPUMP_off();
	}
	DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_HIGH);
	_delay_ms(5);
	DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_LOW);
}

void Action_moderate(void)
{
	BUZZER_on();
	if (T_state == SEVERE || T_state == MODERATE)
	{
		WATERPUMP_on();
	}
	else
	{
		WATERPUMP_off();

	}
	DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_LOW);
}

void Action_safe(void)
{
	BUZZER_off();
	WATERPUMP_off();
	DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_LOW);
}



int main()
{

	TWI_init();

//	BUZZER_init();
//	WATERPUMP_init();

//	SREG |= (1<<7);
	BMP180_Start();
	DIO_setupPinDirection(SLS_FLAG_PORT, SLS_FLAG_PIN, PIN_OUTPUT);



	while (1)
	{
//		_delay_ms(8000);
//		BUZZER_on();
//		_delay_ms(2000);
//		DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_HIGH);
//		_delay_ms(8000);
//		BUZZER_off();
//		_delay_ms(2000);
//		DIO_writePin(SLS_FLAG_PORT, SLS_FLAG_PIN, LOGIC_LOW);

		Temp_state();
		Press_state();

		if (P_state == SEVERE || T_state == SEVERE)
		{
			Action_severe();
		}
		else if (P_state == MODERATE || T_state == MODERATE)
		{
			Action_moderate();
		}
		else if (P_state == SAFE || T_state == SAFE)
		{
			Action_safe();
		}
		else
		{
			BUZZER_off();
			WATERPUMP_off();
		}

		// 1) Measure Pressure
		// 1.1) Ranges: SAFE, MODERATE, SEVERE
		// 1) Measure Temperature
		// 2.1) Ranges: SAFE, MODERATE, SEVERE
		// 3) Action_SEVERE
		// 4) Action_MODERATE
		// 5) Action_SAFE
		// 3) Steering Lock
		// 3.1)	if Pressure = SEVERE or Temperature = SEVERE
		// 3.1.1) write signal on GPIO to control unit
		// 3.2)
		// 4) Water Cooling
		// 4.1) if Temperature = MODERATE or SEVERE
		// 4.1.1)
	}
}
