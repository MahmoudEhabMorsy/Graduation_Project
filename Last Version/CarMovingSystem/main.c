/*
 * main.c
 *
 *  Created on: Jun 29, 2023
 *      Author: Mahmoud Qotp
 */


#include "APPLICATION/app.h"

int main(void)
{
	app_Init();
	while(1)
	{
		app_Start();
	}
}
