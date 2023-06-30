/*
 * waterpump.h
 *
 *  Created on: May 11, 2023
 *      Author: HP
 */

#ifndef ECUAL_WATERPUMP_WATERPUMP_H_
#define ECUAL_WATERPUMP_WATERPUMP_H_

#define PUMP_PORT				PORTA_ID
#define PUMP_PIN				PIN0_ID

void WATERPUMP_init(void);
void WATERPUMP_on(void);
void WATERPUMP_off(void);

#endif /* ECUAL_WATERPUMP_WATERPUMP_H_ */
