/*
 * app.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Mahmoud Qotp
 */

#include "app.h"

/*******************************************************************************
*                             Functions Definitions                            *
*******************************************************************************/
void app_Init(void)
{
	delay(1);
	HC05_init(SLAVE);
	DC_Motor_Init();
}

void app_Start(void)
{
	if(u8_severeTiresStateFlag)
	{
		keep_Car_Safe();
	}
	else
	{
		t_carState = move_car();
	}
}
