/*=======================================================================
 =																		=
 = [FILE NAME]:		lm35_driver.c										=
 =																		=
 = [AUTHOR]:		Ahmed Yasser										=
 =																		=
 = [DATE CREATED]:	17/12/2022											=
 =																		=
 = [DESCRIPTION]:	LM35 - Source file for LM35 Module					=
 =																		=
 =======================================================================*/
#include <util/delay.h>
#include "adc.h"
#include "lm35_driver.h"
#include "std_types.h"

uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

	ADC_selectChannel(LM35_SENESOR_CHANNEL);

	ADC_readChannel();

	_delay_ms(5);

	temp_value =(uint8)(((uint32)g_adcResult*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE * LM35_SENSOR_RESOLUTION));

	return temp_value;
}
