
#include "../ECUAL/BMP/bmp180.h"
//#include "../APPLICATION/APP_EarlyDetection.h"
//#include "../APPLICATION/APP_SteeringLock.h"
//#include "../APPLICATION/APP_WaterCooling.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/DIO/dio.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/BUZZER/buzzer.h"
#include "../ECUAL/WATERPUMP/waterpump.h"
#include "../ECUAL/LCD/lcd.h"
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef enum state{
	SAFE, MODERATE, SEVERE
}STATE;

#define PRESSURE_SEVERE				100000
#define PRESSURE_MODERATE			10000
#define PRESSURE_SAFE				300
#define SLL_FLAG_PORT				PORTB_ID
#define SLL_FLAG_PIN				PIN7_ID
#define TEMPERATURE_SEVERE			45
#define TEMPERATURE_MODERATE		30
#define TEMPERATURE_SAFE			0

uint32 g_temperature = 0;
uint32 g_pressure = 0;
uint16 g_rpm = 0;

STATE P_state = SAFE;
STATE T_state = SAFE;

void APP_displayPress(uint32 pressure)
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
/*
void LCD_displayRPM(uint32 rpm)
{
	LCD_moveCursor(2,7);
	if(100000 <= rpm)
	{
		LCD_intgerToString(rpm);
	}
	else if((10000 <= rpm) && (100000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter(' ');
	}
	else if((1000 <= rpm) && (10000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayString("  ");
	}
	else if((100 <= rpm) && (1000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayString("   ");
	}
	else if((10 <= rpm) && (100 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayString("    ");
	}
	else if((0 <= rpm) && (10 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayString("     ");
	}
}*/

void APP_displayTemp(uint32 temperature)
{
	LCD_moveCursor(1,7);
	if ((1000 <= temperature) || (0 > temperature))
	{
		LCD_intgerToString(temperature);
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

void Temp_state(void)
{
	if (g_temperature >= TEMPERATURE_SEVERE)
	{
		T_state = SEVERE;
	}
	else if ((g_temperature >= TEMPERATURE_MODERATE) && (g_temperature < TEMPERATURE_SEVERE))
	{
		T_state = MODERATE;
	}
	else if ((g_temperature >= TEMPERATURE_SAFE) && (g_temperature < TEMPERATURE_MODERATE))
	{
		T_state = SAFE;
	}
}

void Press_state(void)
{
	if (g_pressure >= PRESSURE_SEVERE)
	{
		P_state = SEVERE;
	}
	else if ((g_pressure >= PRESSURE_MODERATE) && (g_pressure < PRESSURE_SEVERE))
	{
		P_state = MODERATE;
	}
	else if ((g_pressure >= PRESSURE_SAFE) && (g_pressure < PRESSURE_MODERATE))
	{
		P_state = SAFE;
	}
}

void Action_severe(void)
{
	BUZZER_on();
	DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_HIGH);
	LCD_displayStringRowColumn(3,10,"FLAG ON");
}

void Action_moderate(void)
{
	BUZZER_on();
	DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_LOW);
	LCD_displayStringRowColumn(3,10,"FLAG OFF");
}

void Action_safe(void)
{
	BUZZER_off();
	DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_LOW);
	LCD_displayStringRowColumn(3,10,"FLAG OFF");
}

/*int main()
{
	WATERPUMP_init();
	while(1)
	{

		WATERPUMP_off();
	}
}*/

int main()
{
	SREG |= (1<<7);
	TWI_init();
	BMP180_Start();
//	WSS_Init();
	LCD_init();
	BUZZER_init();
	WATERPUMP_init();
	DIO_setupPinDirection(SLL_FLAG_PORT, SLL_FLAG_PIN, PIN_OUTPUT);

	LCD_displayStringRowColumn(0,0,"Press = ");
	LCD_displayStringRowColumn(0,13,"hPa");
	LCD_displayStringRowColumn(1,0,"Temp = ");
	LCD_displayStringRowColumn(1,11,"C");
//	LCD_displayStringRowColumn(2,0,"RPM = ");
//	LCD_displayStringRowColumn(2,12,"rpm");

	while (1)
	{
		g_temperature = BMP180_calculateTemperature();
		g_pressure = BMP180_calculatePressure();
//		g_rpm = WSS_getRPM();
		APP_displayTemp(g_temperature);
		APP_displayPress(g_pressure);

		Temp_state();
		Press_state();

		if (P_state == SEVERE || T_state == SEVERE)
		{
			Action_severe();
			WATERPUMP_on();
			LCD_displayStringRowColumn(3,0,"PUMP ON ");
		}
		else if (P_state == MODERATE || T_state == MODERATE)
		{
			Action_moderate();
			WATERPUMP_on();
			LCD_displayStringRowColumn(3,0,"PUMP ON ");
		}
		else if (P_state == SAFE || T_state == SAFE)
		{
			Action_safe();
			WATERPUMP_off();
			LCD_displayStringRowColumn(3,0,"PUMP OFF");
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
	return 0;
}
