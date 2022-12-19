/*=======================================================================
 =																		=
 = [FILE NAME]:		adc_testcase.c										=
 =																		=
 = [AUTHOR]:		Ahmed Yasser										=
 =																		=
 = [DATE CREATED]:	17/12/2022											=
 =																		=
 = [DESCRIPTION]:	Test case for ADC driver with LM35 Temp sensor		=
 =																		=
 =======================================================================*/

#include "io.h"
#include "lm35_driver.h"
#include "adc.h"
#include "interrupts.h"
#include "lcd.h"


void LCD_displayTemp(uint8 temperature)
{
	LCD_moveCursor(1,10);
	if(100 <= temperature)
	{
		LCD_intgerToString(temperature);
	}
	else if((10 <= temperature) && (100 > temperature))
	{
		LCD_intgerToString(temperature);
		LCD_displayCharacter(' ');
	}
	else if((0 <= temperature) && (10 > temperature))
	{
		LCD_intgerToString(temperature);
		LCD_displayCharacter('    ');
	}
	else
	{

	}
}

int main(void)
{
	uint8 temperature;

	sei();

	LCD_init();

	ADC_ConfigType ADC_configuration = {IREF_REG,F_CPU_128,CHANNEL0,ENABLE_ADC,ENABLE_INT};
	ADC_init(&ADC_configuration);

	LCD_displayStringRowColumn(0,2,"ADC TEST LM32");
	LCD_displayStringRowColumn(1,3,"Temp = ");
	LCD_displayStringRowColumn(1,13,"C");

	while(1)
	{
		temperature = LM35_getTemperature();

		LCD_displayTemp(temperature);
	}
	return 0;
}





