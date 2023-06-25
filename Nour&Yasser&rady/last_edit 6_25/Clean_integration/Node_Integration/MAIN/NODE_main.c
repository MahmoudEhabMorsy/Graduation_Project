
/*******************************************************************************
 *                                   Includes                                  *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../CommonDef/common_macros.h"
#include "../MCAL/TWI/twi.h"
#include "../MCAL/DIO/dio.h"
#include "../MCAL/TIMER/timer.h"
#include "../ECUAL/BMP/bmp180.h"
#include "../ECUAL/WATERPUMP/waterpump.h"
#include "../ECUAL/ULTRASONIC/ultrasonic.h"
#include "../ECUAL/LED/led.h"
#include "../ECUAL/BUZZER/buzzer.h"



/*******************************************************************************
 *                                 Enumerations                                *
 *******************************************************************************/

/* System states depending on Pressure and Temperature (BMP180) */
typedef enum
{
	SAFE,
	MODERATE,
	SEVERE
} STATE;

/* Ranges for distance (Ultrasonic) */
typedef enum
{
	SAFE_DISTANCE, /*More Than 40 CMs*/
	LOW_RISK_DISTANCE, /*Between 40 and 30 CMs*/
	MODERATE_RISK_DISTANCE, /*Between 30 and 20 CMs*/
	HIGH_RISK_DISTANCE, /*Between 20 and 10 CMs*/
	EXTREME_RISK_DISTANCE /*Less Than or Equal to 10 CMs*/
} t_ULTRASONIC_INTERVAL;



/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/

/* Pressure and Temperature Ranges (Minimum Value) */
#define PRESSURE_SEVERE				700		/* Severe Pressure Range: 700 - MAX */
#define PRESSURE_MODERATE			500		/* Moderate Pressure Range: 500 - 700 */
#define PRESSURE_SAFE				300		/* Safe Pressure Range: 300 - 500 */
#define TEMPERATURE_SEVERE			40		/* Severe Temperature Range: 40 - Max */
#define TEMPERATURE_MODERATE		20		/* Moderate Temperature Range: 20 - 40 */
#define TEMPERATURE_SAFE			0		/* Safe Temperature Range: 0 - 20 */

/* Ultrasonic Ranges */
#define LOW_RISK_DISTANCE_UPPER_LIMIT		(40u)
#define LOW_RISK_DISTANCE_LOWER_LIMIT		(30u)
#define MODERATE_RISK_DISTANCE_UPPER_LIMIT	(30u)
#define MODERATE_RISK_DISTANCE_LOWER_LIMIT	(20u)
#define HIGH_RISK_DISTANCE_UPPER_LIMIT		(20u)
#define HIGH_RISK_DISTANCE_LOWER_LIMIT		(10u)
#define EXTREME_RISK_DISTANCE_UPPER_LIMIT	(10u)



/*******************************************************************************
 *                              Pin Configurations                             *
 *******************************************************************************/

/* Steering Lock System Flag which is sent to Car Node */
#define SLS_FLAG_PORT_ID			PORTD_ID
#define SLS_FLAG_PIN_ID				PIN2_ID

/* Early Detection System/Steering Lock System LED and Buzzer */
#define BMP_LED_PORT_ID				PORTD_ID
#define BMP_LED_PIN_ID				PIN3_ID
#define BMP_BUZZER_PORT_ID			PORTD_ID
#define BMP_BUZZER_PIN_ID			PIN4_ID

/* Automatic Parking System LED and Buzzer */
#define WARNING_FRONT_PORT_ID						PORTA_ID
#define	WARNING_FRONT_LOW_RISK_LED_PIN_ID			PIN4_ID
#define WARNING_FRONT_MODERATE_RISK_LED_PIN_ID		PIN5_ID
#define WARNING_FRONT_HIGH_RISK_LED_PIN_ID			PIN6_ID
#define WARNING_FRONT_BUZZER_PIN_ID					PIN7_ID



/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

tyreState g_BMP180_readings = {0,0,0}; /* Wheel ID, Pressure and Temperature sent from BMP180 */
uint16 g_distance = 0; /* Measured by Ultrasonic */
STATE g_pressure_state = SAFE;
STATE g_temperature_state = SAFE;
t_ULTRASONIC_INTERVAL ultrasonicInterval = SAFE_DISTANCE;



/*******************************************************************************
 *                            Function Declarations                            *
 *******************************************************************************/

void timercallBckFunc(void);
void warning(uint16 Distance);
void Parking_LED_init(void);
void Parking_LED_default(void);
void Temp_state(void);
void Press_state(void);
void Action_severe(void);
void Action_moderate(void);
void Action_safe(void);
void Detection_LED_init(void);


/*******************************************************************************
 *                              Function Definitions                           *
 *******************************************************************************/

void timercallBckFunc(void)
{
	static uint8 counter=0;

	switch(ultrasonicInterval)
	{
	case LOW_RISK_DISTANCE:
		//we need to make the buzzer on for 400ms and off for 100ms
		//to make it on for 100ms we need the timer to overflow 6 times
		//to make it off for 100ms we need the timer to overflow 6 times
		//so the buzzer will toggle when counter is 24
		Parking_LED_default();
		//	Buzzer_on(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
		//	LED_ON(WARNING_FRONT_PORT_ID,WARNING_FRONT_LOW_RISK_LED_PIN_ID);

		if(counter == 24)
		{
			BUZZER_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
			LED_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_LOW_RISK_LED_PIN_ID);
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
		Parking_LED_default();

		//	Buzzer_on(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
		//	LED_ON(WARNING_FRONT_PORT_ID,WARNING_FRONT_MODERATE_RISK_LED_PIN_ID);

		if(counter > 18)
		{
			counter = 0;
		}
		if(counter == 18)
		{
			BUZZER_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
			LED_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_MODERATE_RISK_LED_PIN_ID);
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
		Parking_LED_default();
		//	Buzzer_on(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
		//	LED_ON(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);

		if(counter > 12)
		{
			counter = 0;
		}
		if(counter == 12)
		{
			BUZZER_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
			LED_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);
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
		Parking_LED_default();
		//	Buzzer_on(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
		//	LED_ON(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);

		if(counter > 6)
		{
			counter = 0;
		}
		if(counter == 6)
		{
			BUZZER_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
			LED_TOGGLE(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);
			counter = 0;
		}
		else
		{
			counter++;
		}
		break;

	default:
		Parking_LED_default();
		BUZZER_OFF(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
		counter = 0;
		break;
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

void Parking_LED_init(void)
{
	LED_init(WARNING_FRONT_PORT_ID,WARNING_FRONT_LOW_RISK_LED_PIN_ID);
	LED_init(WARNING_FRONT_PORT_ID,WARNING_FRONT_MODERATE_RISK_LED_PIN_ID);
	LED_init(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);
	BUZZER_init(WARNING_FRONT_PORT_ID,WARNING_FRONT_BUZZER_PIN_ID);
}

void Parking_LED_default(void)
{
	LED_OFF(WARNING_FRONT_PORT_ID,WARNING_FRONT_LOW_RISK_LED_PIN_ID);
	LED_OFF(WARNING_FRONT_PORT_ID,WARNING_FRONT_MODERATE_RISK_LED_PIN_ID);
	LED_OFF(WARNING_FRONT_PORT_ID,WARNING_FRONT_HIGH_RISK_LED_PIN_ID);
}

void Temp_state(void){
	if (g_BMP180_readings.temperature >= TEMPERATURE_SEVERE)
	{
		g_temperature_state = SEVERE;
	}
	else if ((g_BMP180_readings.temperature >= TEMPERATURE_MODERATE) && (g_BMP180_readings.temperature < TEMPERATURE_SEVERE))
	{
		g_temperature_state = MODERATE;
	}
	else if ((g_BMP180_readings.temperature >= TEMPERATURE_SAFE) && (g_BMP180_readings.temperature < TEMPERATURE_MODERATE))
	{
		g_temperature_state = SAFE;
	}
}

void Press_state(void)
{
	if (g_BMP180_readings.pressure >= PRESSURE_SEVERE)
	{
		g_pressure_state = SEVERE;
	}
	else if ((g_BMP180_readings.pressure >= PRESSURE_MODERATE) && (g_BMP180_readings.pressure < PRESSURE_SEVERE))
	{
		g_pressure_state = MODERATE;
	}
	else if ((g_BMP180_readings.pressure >= PRESSURE_SAFE) && (g_BMP180_readings.pressure < PRESSURE_MODERATE))
	{
		g_pressure_state = SAFE;
	}
}

void Action_severe(void)
{
	BUZZER_ON(BMP_BUZZER_PORT_ID,BMP_BUZZER_PIN_ID);
	LED_ON(BMP_LED_PORT_ID,BMP_LED_PIN_ID);
	if (g_temperature_state == SEVERE || g_temperature_state == MODERATE)
	{
		WATERPUMP_on();
	}
	else
	{
		WATERPUMP_off();
	}
	DIO_writePin(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, LOGIC_HIGH);
	//	_delay_ms(5);
	//	DIO_writePin(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, LOGIC_LOW);
}

void Action_moderate(void)
{
	BUZZER_ON(BMP_BUZZER_PORT_ID,BMP_BUZZER_PIN_ID);
	LED_ON(BMP_LED_PORT_ID,BMP_LED_PIN_ID);
	if (g_temperature_state == SEVERE || g_temperature_state == MODERATE)
	{
		WATERPUMP_on();
	}
	else
	{
		WATERPUMP_off();

	}
	DIO_writePin(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, LOGIC_LOW);
}

void Action_safe(void)
{
	BUZZER_OFF(BMP_BUZZER_PORT_ID,BMP_BUZZER_PIN_ID);
	LED_OFF(BMP_LED_PORT_ID,BMP_LED_PIN_ID);
	WATERPUMP_off();
	DIO_writePin(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, LOGIC_LOW);
}

void Detection_LED_init(void)
{
	LED_init(BMP_BUZZER_PORT_ID,BMP_BUZZER_PIN_ID);
	BUZZER_init(BMP_LED_PORT_ID,BMP_LED_PIN_ID);
}

int main()
{
	Timer_configuration Timer0_Configuration={Timer0,Normal,TIMER_INITIAL_VALUE,NO_COMPARE_VALUE,Prescaler_1024,timercallBckFunc};

	_delay_ms(250);
	TWI_init();
	BMP180_Start();

	Detection_LED_init();
	Parking_LED_init();

	Timer_init(&Timer0_Configuration);
	DIO_setupPinDirection(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, PIN_OUTPUT);

	Ultrasonic_init(); /*initializing Ultrasonic*/
	WATERPUMP_init();

	sei();

	while(1)
	{
		Temp_state();
		Press_state();
		if (g_pressure_state == SEVERE || g_temperature_state == SEVERE)
		{
			Action_severe();
		}
		else if (g_pressure_state == MODERATE || g_temperature_state == MODERATE)
		{
			Action_moderate();
		}
		else if (g_pressure_state == SAFE || g_temperature_state == SAFE)
		{
			Action_safe();
		}
		else
		{
			BUZZER_OFF(BMP_BUZZER_PORT_ID,BMP_BUZZER_PIN_ID);
			WATERPUMP_off();
		}

		g_distance = Ultrasonic_readDistance(); /*storing the measured distance*/
		warning(g_distance);

		BMP180_calculate(&g_BMP180_readings);
		_delay_ms(1000);
	}
	return 0;

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
