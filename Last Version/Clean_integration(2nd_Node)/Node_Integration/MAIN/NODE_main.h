#ifndef NODE_MAIN_H_
#define NODE_MAIN_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "../MCAL/TWI/twi.h"
#include "../MCAL/DIO/dio.h"
#include "../MCAL/TIMER/timer.h"
#include "../ECUAL/BMP/bmp180.h"
#include "../ECUAL/WATERPUMP/waterpump.h"
#include "../ECUAL/ULTRASONIC/ultrasonic.h"
#include "../MCAL/SPI/spi.h"
#include "../ECUAL/LED/led.h"
#include "../ECUAL/BUZZER/buzzer.h"
#include "../UTILITIES/common_macros.h"

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

/* Test Cases */
typedef enum
{
	TEST_DEFAULT,
	TEST_SAFE,
	TEST_MODERATE,
	TEST_SEVERE
} TEST_CASE;



/*******************************************************************************
 *                                 Definitions                                 *
 *******************************************************************************/

/* Pressure and Temperature Ranges (Minimum Value) */
#define PRESSURE_SEVERE				10000	/* Severe Pressure Range: 700 - MAX */
#define PRESSURE_MODERATE			2000	/* Moderate Pressure Range: 500 - 700 */
#define PRESSURE_SAFE				300		/* Safe Pressure Range: 300 - 500 */
#define TEMPERATURE_SEVERE			40		/* Severe Temperature Range: 40 - Max */
#define TEMPERATURE_MODERATE		30		/* Moderate Temperature Range: 20 - 40 */
#define TEMPERATURE_SAFE			0		/* Safe Temperature Range: 0 - 20 */

/* Ultrasonic Ranges */
#define LOW_RISK_DISTANCE_UPPER_LIMIT		(20u)
#define LOW_RISK_DISTANCE_LOWER_LIMIT		(15u)
#define MODERATE_RISK_DISTANCE_UPPER_LIMIT	(15u)
#define MODERATE_RISK_DISTANCE_LOWER_LIMIT	(10u)
#define HIGH_RISK_DISTANCE_UPPER_LIMIT		(10u)
#define HIGH_RISK_DISTANCE_LOWER_LIMIT		(5u)
#define EXTREME_RISK_DISTANCE_UPPER_LIMIT	(5u)



/*******************************************************************************
 *                              Pin Configurations                             *
 *******************************************************************************/

#define INTERRUPT_2_PORT_ID			PORTB_ID
#define INTERRUPT_2_PIN_ID			PIN2_ID

#define INTERRUPT_SIGNAL_PORT_ID	PORTC_ID
#define INTERRUPT_SIGNAL_PIN_ID		PIN2_ID

/* Steering Lock System Flag which is sent to Car Node */
#define SLS_FLAG_PORT_ID			PORTD_ID
#define SLS_FLAG_PIN_ID				PIN2_ID

/*FLAG TO RECIEVE SIGNAL FROM ANOTHER NODE IN ORDER TO 
ACTIVATE THE FLAG THAT INITIATE AN INTERRUPT ON THE OTHER NODE FOR SPI COMMUNICATION*/
#define SLL_FLAG_PORT				PORTD_ID    
#define SLL_FLAG_PIN				PIN7_ID     

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



#endif /* NODE_MAIN_H_ */