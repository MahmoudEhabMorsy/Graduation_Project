/*=======================================================================
 =									=
 = [FILE NAME]:		adc_testcase.c					=
 =									=
 = [AUTHOR]:		Ahmed Yasser					=
 =									=
 = [DATE CREATED]:	17/12/2022					=
 =									=
 = [DESCRIPTION]:	Test case for ADC driver with LM35 Temp sensor	=
 =									=
 =======================================================================*/

#include "io.h"
#include "lm35_driver.h"
#include "adc.h"
#include "interrupts.h"
#include "lcd.h"

/*
 * Function used to convert the temperature into
 * strings on the LCD
 */
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

	/* Enable global interrupts */
	sei();

	/* Initializing LCD */
	LCD_init();

	/* Initializing ADC */
	ADC_ConfigType ADC_configuration = {IREF_REG,F_CPU_128,CHANNEL0,ENABLE_ADC,ENABLE_INT};
	ADC_init(&ADC_configuration);

	/* Static display contents */
	LCD_displayStringRowColumn(0,2,"ADC TEST LM32");
	LCD_displayStringRowColumn(1,3,"Temp = ");
	LCD_displayStringRowColumn(1,13,"C");

	while(1)
	{
		/* Getting temperature value from the sensor */
		temperature = LM35_getTemperature();

		/* Displaying temperature value on the LCD */
		LCD_displayTemp(temperature);
	}
	return 0;
}





