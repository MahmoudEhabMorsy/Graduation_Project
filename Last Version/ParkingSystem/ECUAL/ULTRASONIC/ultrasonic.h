/******************************************************************************
 *
 * Module: UltraSonic
 *
 * File Name: UltraSonic.h
 *
 * Description: header  file for the AVR UltraSonic driver
 *
 * Author:
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#include "../../UTILITIES/std_types.h"
#define CPUFREQ 			8

#define FRONT_RIGHT_ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define FRONT_RIGHT_ULTRASONIC_TRIGGER_PIN_ID	 PIN5_ID
#define FRONT_LEFT_ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define FRONT_LEFT_ULTRASONIC_TRIGGER_PIN_ID   PIN6_ID       
#define FRONT_RIGHT_ULTRASONIC_VCC_PORT_ID  PORTC_ID
#define FRONT_RIGHT_ULTRASONIC_VCC_PIN_ID	 PIN0_ID
#define FRONT_LEFT_ULTRASONIC_VCC_PORT_ID  PORTC_ID
#define FRONT_LEFT_ULTRASONIC_VCC_PIN_ID	 PIN1_ID
#define REAR_RIGHT_ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define REAR_RIGHT_ULTRASONIC_TRIGGER_PIN_ID	 PIN5_ID
#define REAR_LEFT_ULTRASONIC_TRIGGER_PORT_ID  PORTB_ID
#define REAR_LEFT_ULTRASONIC_TRIGGER_PIN_ID   PIN6_ID
#define REAR_RIGHT_ULTRASONIC_VCC_PORT_ID  PORTC_ID
#define REAR_RIGHT_ULTRASONIC_VCC_PIN_ID	 PIN0_ID
#define REAR_LEFT_ULTRASONIC_VCC_PORT_ID  PORTC_ID
#define REAR_LEFT_ULTRASONIC_VCC_PIN_ID	 PIN1_ID
#define ULTRASONIC_ECHO_PORT_ID  PORTD_ID
#define ULTRASONIC_ECHO_PIN_ID	 PIN6_ID

#define SOUND_SPEED 34000 /*sound speed in cm*/
#define TIME_OF_INSTRUCTION 0.000001/*time needed to execute on instruction after prescalling*/

typedef enum
{
	FRONT_LEFT,
	FRONT_RIGHT,
	REAR_LEFT,
	REAR_RIGHT
}Ultrasonic_Sensor_ID;

extern Ultrasonic_Sensor_ID g_sensorID;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description :
 * Initialize the ICU driver as required.
 * Setup the ICU call back function
 * Setup the direction for the trigger pin as output pin through the GPIO driver.
 */
void Ultrasonic_init(void);
/*
 * Description :
 * Send the Trigger pulse to the ultrasonic.
 */
void Ultrasonic_Trigger(void);
/*
 * Description :
 * Send the trigger pulse by using Ultrasonic_Trigger function
 * Start the measurements by the ICU from this moment
 */
uint16 Ultrasonic_readDistance(void);
/*
 * Description :
 * This is the call back function called by the ICU driver.
 * This is used to calculate the high time (pulse time) generated by the ultrasonic sensor.
 */
void Ultrasonic_edgeProcessing(void);


#endif /* ULTRASONIC_H_ */
