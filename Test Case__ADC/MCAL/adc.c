/*=======================================================================
 =																		=
 = [FILE NAME]:		adc.c												=
 =																		=
 = [AUTHOR]:		Ahmed Yasser										=
 =																		=
 = [DATE CREATED]:	07/11/2022											=
 =																		=
 = [DESCRIPTION]:	ADC - Source file for ADC Module					=
 =																		=
 =======================================================================*/
 
#include "adc.h"
#include "io.h"
#include "interrupts.h"
/*------------------------------------------------------------------------------
 |                          Global Variables                                   |
 ------------------------------------------------------------------------------*/

volatile uint16 g_adcResult = 0;
volatile uint16 g_adc_value = 0;

 /*------------------------------------------------------------------------------
 |                          ISR's Definitions                                  |
 ------------------------------------------------------------------------------*/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = g_adc_value;
}
 /*-----------------------------------------------------------------------*
 |                         Function Definitions                          |
 *-----------------------------------------------------------------------*/

/*======================================================================*
 * [Function Name]:	ADC_init()											*
 * [Description]:	Function responsible for initialize the ADC driver. *
 * 																		*
 * [Args]			const ADC_ConfigType * Config_Ptr					*
 * [Return]			void												*
 *======================================================================*/
 void ADC_init(const ADC_ConfigType * Config_Ptr)
{
	 /************************** ADMUX Description **************************
	  * REFS0:1 	= 2	User internal reference voltage 2.56v.
	  * ADLAR 		= 0 Right adjusted.
	  * MUX0:4		= Channel select temporary for initialization.
	  ***********************************************************************/
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr ->ref_volt) << REFS0);
	ADMUX = ADMUX |	((Config_Ptr ->channel) << MUX0);

	 /************************** ADCSRA Description **************************
	  * ADEN  	= 1 Enable ADC.
	  * ADATE 	= 0 Disable auto trigger.
	  * ADIE  	= 1 Enable Interrupt.
	  * ADPS0:2  = 7 Use prescaler with division factor = 128
	  * 			  F_CPU = 16 MHz, then ADC CLK = F_CPU/128
	  * 			  Then ADC_CLK = 125 KHz.
	  ***********************************************************************/
	ADCSRA = (ADCSRA & 0x7F) | ((Config_Ptr ->enable_op) << ADEN);
	ADCSRA = (ADCSRA & 0xF7) | ((Config_Ptr ->interrupt) << ADIE);
	ADCSRA = (ADCSRA & 0xF8) | ((Config_Ptr ->prescaler) << ADPS0);
//	ADCSRA = (ADCSRA & 0xEF);
}


 /*=====================================================================*
  * [Function Name]:	ADC_selectChannel()								*
  * [Description]:		Function used to select the channel.			*
  * 																	*
  * [Args]			uint8 channel_num									*
  * [Return]		void												*
  *=====================================================================*/
 void ADC_selectChannel(uint8 channel_num)
 {
	 /* insert channel number */
		ADMUX = (ADMUX & 0xE0) | (channel_num & 0x07);
 }


 /*=====================================================================*
  * [Function Name]:	ADC_readChannel()								*
  * [Description]:		Function responsible for read analog data from 	*
  * 					a certain ADC channel and convert it to digital *
  * 					using the ADC driver.							*
  * 																	*
  * [Args]				void											*
  * [Return]			void											*
  *=====================================================================*/
void ADC_readChannel(void)
{
	g_adc_value = 0;

	/* start conversion */
	ADCSRA = (ADCSRA & 0xBF) | (1<<ADSC);

	/* Store data in adc_value */
	g_adc_value = ADCL;
	g_adc_value = g_adc_value | (ADCH << 8);
}



