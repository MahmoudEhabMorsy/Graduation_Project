//
//
//#include "../CommonDef/common_macros.h"
//#include "../ECUAL/LCD/lcd.h"
//#include <util/delay.h>
//#include "../MCAL/DIO/dio.h"
//#include "../ECUAL/WHEELSPEED/a3144_wss.h"
//#include "../MCAL/TIMER/interrupts.h"
//#include <avr/io.h> //for SREG
//
//#define BUZZER_PORT		PORTC_ID
//#define BUZZER_PIN		PIN6_ID
//
//
//void LCD_displayRPM(uint32 rpm)
//{
//	LCD_moveCursor(0,7);
//	if(100000 <= rpm)
//	{
//		LCD_intgerToString(rpm);
//	}
//	else if((10000 <= rpm) && (100000 > rpm))
//	{
//		LCD_intgerToString(rpm);
//		LCD_displayCharacter(' ');
//	}
//	else if((1000 <= rpm) && (10000 > rpm))
//	{
//		LCD_intgerToString(rpm);
//		LCD_displayCharacter('  ');
//	}
//	else if((100 <= rpm) && (1000 > rpm))
//	{
//		LCD_intgerToString(rpm);
//		LCD_displayCharacter('   ');
//	}
//	else if((10 <= rpm) && (100 > rpm))
//	{
//		LCD_intgerToString(rpm);
//		LCD_displayCharacter('    ');
//	}
//	else if((0 <= rpm) && (10 > rpm))
//	{
//		LCD_intgerToString(rpm);
//		LCD_displayCharacter('     ');
//	}
//}
////
////int main(void)
////{
////	uint16 rpm = 0;
////	SREG |= (1<<7);
////	WSS_Init();
////	LCD_init();
////	Buzzer_init();
////
////	LCD_displayStringRowColumn(0,0,"rpm = ");
////	LCD_displayStringRowColumn(0,12,"rpm");
////
////	while(1)
////	{
//////		rpm = BMP180_calculatePressure();
////		rpm = WSS_getRPM();
////		LCD_displayRPM(rpm);
////		if (rpm > 0)
////		{
////			Buzzer_On();
////		}
//////		EDS_Detection(temperature,pressure);
////		_delay_ms(500);
////	}
////	return 0;
////}
