/*
 * buzzer.h
 *
 *  Created on: May 11, 2023
 *      Author: HP
 */

#ifndef ECUAL_BUZZER_BUZZER_H_
#define ECUAL_BUZZER_BUZZER_H_

#define BUZZER_PORT				PORTC_ID
#define BUZZER_PIN				PIN6_ID

void BUZZER_init(void);
void BUZZER_on(void);
void BUZZER_off(void);

#endif /* ECUAL_BUZZER_BUZZER_H_ */
