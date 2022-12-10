/*=======================================================================
 =																		=
 = [FILE NAME]:		adc.h												=
 =																		=
 = [AUTHOR]:		Ahmed Yasser										=
 =																		=
 = [DATE CREATED]:	07/11/2022											=
 =																		=
 = [DESCRIPTION]:	ADC - Header file for ADC Module					=
 =																		=
 =======================================================================*/
 
#ifndef ADC_H_
#define ADC_H_



#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
 
#define IREF 					3
/* ADC_REF_VOLT_VALUE is the voltage value itself. */
#define ADC_REF_VOLT_VALUE   	2.56
#define F_CPU_128 				7
#define ADC_MAXIMUM_VALUE    	1023

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern Public global variables to be used by other modules */
extern volatile uint16 g_adcResult;

 /*-----------------------------------------------------------------------*
 |                           Type Declarations                           |
 *-----------------------------------------------------------------------*/
 
 /* type used to set reference voltage for ADC port
 * if set to 00 -> External AREF, Internal Vref turned off
 * if set to 01 -> AVCC at AREF pin (5V)
 * if set t0 11 -> Internal 2.56V Voltage Reference at AREF pin
 */
typedef uint8 ADC_ReferenceVolatge;


/* type used to set prescaler of ADC */
typedef uint16 ADC_Prescaler;


/* type used to set channel of ADC */
typedef enum{
	CHANNEL0,CHANNEL1,CHANNEL2,CHANNEL3,CHANNEL4,CHANNEL5
}ADC_Channel;


/* type used to enable/disable ADC */
typedef enum{
	DISABLE_ADC,ENABLE_ADC
}ADC_Enable;


/* type used to enable/disable ADC Interrupts */
typedef enum{
	DISABLE_INT,ENABLE_INT
}ADC_Interrupts;


typedef struct{
 ADC_ReferenceVolatge ref_volt;
 ADC_Prescaler prescaler;
 ADC_Channel channel;
 ADC_Enable enable_op;
 ADC_Interrupts interrupt;
}ADC_ConfigType;

 /*-----------------------------------------------------------------------*
 |                          Function Prototypes                          |
 *-----------------------------------------------------------------------*/

/*======================================================================*
 * [Function Name]:	ADC_init()											*
 * [Description]:	Function responsible for initialize the ADC driver. *
 * 																		*
 * [Args]			const ADC_ConfigType * Config_Ptr					*
 * [Return]			void												*
 *======================================================================*/
void ADC_init(const ADC_ConfigType * Config_Ptr);

/*======================================================================*
 * [Function Name]:	ADC_selectChannel()									*
 * [Description]:		Function used to select the channel.			*
 * 																		*
 * [Args]			uint8 channel_num									*
 * [Return]		void													*
 *======================================================================*/
void ADC_selectChannel(uint8 channel_num);


/*======================================================================*
 * [Function Name]:		ADC_readChannel()								*
 * [Description]:		Function responsible for read analog data from 	*
 * 						a certain ADC channel and convert it to digital *
 * 						using the ADC driver.							*
 * 																		*
 * [Args]				void											*
 * [Return]				void											*
 *======================================================================*/
void ADC_readChannel(void);

#endif /* ADC_H_ */
