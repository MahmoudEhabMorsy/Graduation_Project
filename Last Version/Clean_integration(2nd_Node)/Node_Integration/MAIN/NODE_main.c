
/*******************************************************************************
 *                                   Includes                                  *
 *******************************************************************************/


#include "NODE_main.h"






/*******************************************************************************
 *                               Global Variables                              *
 *******************************************************************************/

tyreState g_BMP180_readings = {0,0,0}; /* Wheel ID, Pressure and Temperature sent from BMP180 */
uint16 g_distance = 0; /* Measured by Ultrasonic */
STATE g_pressure_state = SAFE;
STATE g_temperature_state = SAFE;
t_ULTRASONIC_INTERVAL ultrasonicInterval = SAFE_DISTANCE;
TEST_CASE g_testCase = TEST_DEFAULT;

unsigned int counter_Bytes = 4;




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

ISR(INT2_vect)
{
	if (g_testCase == TEST_SEVERE)
	{
		g_testCase = TEST_DEFAULT;
	}
	else
	{
		g_testCase++;
	}
}

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

		//		if(counter > 24)
		//		{
		//			counter = 0;
		//		}
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

void INT2_init(void)
{
	
	DIO_setupPinDirection(INTERRUPT_2_PORT_ID,INTERRUPT_2_PIN_ID,PIN_INPUT)	  // Configure INT2/PB2 as input pin
	DIO_writePin(INTERRUPT_2_PORT_ID,INTERRUPT_2_PIN_ID,LOGIC_HIGH);			  // Enable the internal pull up resistor at PB2 pin
	MCUCSR |= (1<<ISC2);     // Trigger INT2 with the raising edge
	GICR   |= (1<<INT2);	 // Enable external interrupt pin INT2
}

int main()
{
	uint8 send_Byte=0;

	Timer_configuration Timer0_Configuration={Timer0,Normal,TIMER_INITIAL_VALUE,NO_COMPARE_VALUE,Prescaler_1024,timercallBckFunc};

	_delay_ms(250);
	TWI_init();
	BMP180_Start();

	Detection_LED_init();
	Parking_LED_init();

	Timer_init(&Timer0_Configuration);
	DIO_setupPinDirection(SLS_FLAG_PORT_ID, SLS_FLAG_PIN_ID, PIN_OUTPUT);

	DIO_setupPinDirection(SLL_FLAG_PORT, SLL_FLAG_PIN, PIN_INPUT);
	DIO_writePin(SLL_FLAG_PORT, SLL_FLAG_PIN, LOGIC_HIGH);//pull up resistor

	DIO_setupPinDirection(INTERRUPT_SIGNAL_PORT_ID,INTERRUPT_SIGNAL_PIN_ID,PIN_OUTPUT) /*Configure PC2 as Output pin*/
	DIO_writePin(INTERRUPT_SIGNAL_PORT_ID,INTERRUPT_SIGNAL_PIN_ID,LOGIC_HIGH) /*Initiate it to be VCCed*/


	/* Initialize the SPI driver as Master */
	SPI_initMaster();


	Ultrasonic_init(); /*initializing Ultrasonic*/
	WATERPUMP_init();

	INT2_init();
	sei();

	while(1)
	{
		if(!DIO_readPin(SLL_FLAG_PORT,SLL_FLAG_PIN)){
			//PORTC &= ~(1 << 2);
			DIO_writePin(INTERRUPT_SIGNAL_PORT_ID,INTERRUPT_SIGNAL_PIN_ID,LOGIC_LOW) /*TRIGGER INTERRUPT IN THE OTHER NODE*/
			SPI_sendReceiveByte(FRONT_LEFT); /*Wheel ID*/
			/**/
			for (uint8 i = 0; i < counter_Bytes; i++) {
				send_Byte = (g_BMP180_readings.temperature >> (i * 8));
				SPI_sendReceiveByte(send_Byte);
			}

			for (uint8 i = 0; i < counter_Bytes; i++) {
				send_Byte = (g_BMP180_readings.pressure >> (i * 8));
				SPI_sendReceiveByte(send_Byte);
			}
		}
		else
		{
			//PORTC |= (1 << 2);
			DIO_writePin(INTERRUPT_SIGNAL_PORT_ID,INTERRUPT_SIGNAL_PIN_ID,LOGIC_HIGH) /*RESET INTERRUPT TRIGGER FOR THE OTHER NODE*/

			switch(g_testCase)
			{
			case TEST_DEFAULT:
				BMP180_calculate(&g_BMP180_readings);
				break;
			case TEST_SAFE:
				g_BMP180_readings.temperature = 25;
				g_BMP180_readings.pressure = 900;
				break;
			case TEST_MODERATE:
				g_BMP180_readings.temperature = 35;
				g_BMP180_readings.pressure = 3000;
				break;
			case TEST_SEVERE:
				g_BMP180_readings.temperature = 45;
				g_BMP180_readings.pressure = 12000;
				break;
			}

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

			//		_delay_ms(100);
		}
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

