/************************************************************************
 *																		*
 * [FILE NAME]:		lcd.h												*
 *																		*
 * [AUTHOR]:		Ahmed Yasser										*
 *																		*
 * [DATE CREATED]:	06/10/2022											*
 *																		*
 * [DESCRIPTION]:	LCD - header file for LCD Module					*
 *																		*
 ************************************************************************/

#ifndef LCD_H_
#define LCD_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/


/* LCD HW Ports and Pins Ids */
#define	LCD_RS_PORT_ID					PORTD_ID
#define	LCD_RS_PIN_ID					PIN0_ID

#define	LCD_ENABLE_PORT_ID				PORTD_ID
#define LCD_ENABLE_PIN_ID				PIN2_ID

#define	LCD_DATA_PORT_ID				PORTC_ID


/* LCD Modes */
#define LCD_TWO_LINES_EIGHT_BITS_MODE  	0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   	0x28


/* LCD Commands */
#define LCD_CLEAR_DISPLAY				0x01
#define LCD_RETURN_HOME					0x02
#define LCD_DISPLAY_OFF_CURSOR_OFF		0x08
#define LCD_DISPLAY_OFF_CURSOR_ON		0x0A
#define LCD_DISPLAY_ON_CURSOR_OFF		0x0C
#define LCD_DISPLAY_ON_CURSOR_ON		0x0E
#define LCD_CURSOR_BLINKING				0x0F
#define LCD_CURSOR_LEFT_BY_ONE_CHAR		0x10
#define LCD_CURSOR_RIGHT_BY_ONE_CHAR	0x14
#define LCD_SHIFT_ALL_LEFT				0x18
#define LCD_SHIFT_ALL_RIGHT				0x1C
#define LCD_CURSOR_BEGIN_FIRST_LINE		0x80
#define LCD_CURSOR_BEGIN_SECOND_LINE	0xC0


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void LCD_init(void);

void LCD_sendCommand(uint8 command);

void LCD_displayCharacter(uint8 data);
void LCD_displayString(uint8 *str);


void LCD_moveCursor(uint8 row, uint8 column);
void LCD_displayStringRowColumn(uint8 row, uint8 column, uint8 *Str);

void LCD_clearScreen();

void LCD_intgerToString(uint16 data);

#endif /* LCD_H_ */
