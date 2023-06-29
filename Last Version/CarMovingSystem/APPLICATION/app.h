/*
 * app.h
 *
 *  Created on: Jun 29, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef APPLICATION_APP_H_
#define APPLICATION_APP_H_

/*******************************************************************************
*                           Application Dependency                             *
*******************************************************************************/
#include "../ECUAL/MOTOR/motor_rc.h"
#include "../ECUAL/HC05/hc05.h"


/*******************************************************************************
*                            Functions Prototypes                              *
*******************************************************************************/
void app_Init(void);

void app_Start(void);


#endif /* APPLICATION_APP_H_ */
