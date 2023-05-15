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

#ifndef ECUAL_ULTRASONIC_ULTRASONIC_H_
#define ECUAL_ULTRASONIC_ULTRASONIC_H_


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#include "../../CommonDef/std_types.h"
#define CPUFREQ 			8



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


#endif /* ECUAL_ULTRASONIC_ULTRASONIC_H_ */
