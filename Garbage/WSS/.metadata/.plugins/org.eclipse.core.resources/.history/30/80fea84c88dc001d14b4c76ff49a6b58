

#include "common_macros.h"
#include "lcd.h"
#include <util/delay.h>
#include "dio.h"
#include "a3144_wss.h"
#include "interrupts.h"



void LCD_displayRPM(uint32 rpm)
{
	LCD_moveCursor(0,7);
	if(100000 <= rpm)
	{
		LCD_intgerToString(rpm);
	}
	else if((10000 <= rpm) && (100000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter(' ');
	}
	else if((1000 <= rpm) && (10000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter('  ');
	}
	else if((100 <= rpm) && (1000 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter('   ');
	}
	else if((10 <= rpm) && (100 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter('    ');
	}
	else if((0 <= rpm) && (10 > rpm))
	{
		LCD_intgerToString(rpm);
		LCD_displayCharacter('     ');
	}
}




int main(void)
{
	uint16 rpm = 0;
	LCD_init();
	LCD_clearScreen();

	LCD_displayStringRowColumn(0,0,"TEST1");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);


	WSS_Init();

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"TEST2");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	INT0_Init();
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"TEST3");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"BEFORE SEI");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	sei();

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"A3A3A3A3A");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"TEST4");
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);
	_delay_ms(250);

	while(1)
	{
//		rpm = BMP180_calculatePressure();
		rpm = WSS_getRPM();
		LCD_intgerToString(rpm);
//		LCD_displayRPM(rpm);
//		EDS_Detection(temperature,pressure);
		_delay_ms(500);
	}
	return 0;
}
