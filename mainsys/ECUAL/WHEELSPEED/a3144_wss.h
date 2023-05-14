/*=======================================================================
 =																		=
 = [FILE NAME]:		a3144.h												=
 =																		=
 = [AUTHOR]:		Ahmed Y Kaead , Nour Atef , Rady Magdy				=
 =																		=
 = [DATE CREATED]:	28/02/2023  										=
 =																		=
 = [DESCRIPTION]:	WSS - wheel speed header source file				=
 =																		=
 =======================================================================*/

#ifndef A3144_WSS_H_
#define A3144_WSS_H_

#include "../../CommonDef/std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PULSEPERREVOLUTION 			1

#define INT0_PORT_ID				PORTD_ID
#define INT0_PIN_ID					PIN2_ID

/*-----------------------------------------------------------------------*
 |                          Function Prototypes                          |
 *-----------------------------------------------------------------------*/

/*======================================================================*
 * [Function Name]:	WSS_timeCounter()									*
 * [Description]:	Function called by timer interrupt every one second *
 * 					to set one second timer flag 						*
 * 																		*
 * [Args]			void												*
 * [Return]			void												*
 *======================================================================*/
void WSS_timeCounter(void);

/*======================================================================*
 * [Function Name]:	WSS_Init()											*
 * [Description]:	Function to initialize WSS module.				 	*
 * 																		*
 * [Args]			void												*
 * [Return]			void												*
 *======================================================================*/
void INT0_Init(void);

/*======================================================================*
 * [Function Name]:	WSS_Init()											*
 * [Description]:	Function to initialize WSS module.				 	*
 * 																		*
 * [Args]			void												*
 * [Return]			void												*
 *======================================================================*/
void WSS_Init(void);

/*======================================================================*
 * [Function Name]:	WSS_getRPM()										*
 * [Description]:	Function to calculate wheel speed in RPM based on	*
 * 					number of pulses counted in one second then convert	*
 * 					it to number of one complete cycles in one minute	*
 * 					which means RPM										*
 * 																		*
 * [Args]			void												*
 * [Return]			RPM value											*
 *======================================================================*/
uint16 WSS_getRPM(void);


#endif /* A3144_WSS_H_ */
