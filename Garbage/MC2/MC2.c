/*
 ================================================================================================
 Name        : MC2.c
 Author      : Mohamed Tarek
 Description : MC2 Code in Exercise2
 Date        : 4/11/2014
 ================================================================================================
 */ //in atmega 32 slave spi receiving by interrupt mode in master
#include "spi.h"
#include "lcd.h"
#include <avr/io.h>
//#include <avr/interrupt.h>
#include <util/delay.h>
#include "std_types.h"

#define _VECTOR(N) __vector_ ## N

#  define __INTR_ATTRS used, externally_visible

# define sei()  __asm__ __volatile__ ("sei" ::: "memory")

# define cli()  __asm__ __volatile__ ("cli" ::: "memory")

								/* ISR Macro */
#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#define INT1_vect			_VECTOR(2)

uint32 temp = 0;
uint32 pressure = 0;
//uint8 count_Bypte = 255;
uint8 send_Byte = 0;
unsigned int counter_Bytes=4;

ISR(INT1_vect)
{
	for (int x = 0; x < counter_Bytes; x++) {
		send_Byte = SPI_sendReceiveByte(send_Byte);
		temp = (temp | (send_Byte << (x * 8)));
	}

	for (int x = 0; x < counter_Bytes; x++) {
		send_Byte = SPI_sendReceiveByte(send_Byte);
		pressure = (pressure | (send_Byte << (x * 8)));
	}
}

int main(void) {
	/*INT1 init Function*/
	DDRD  &= (~(1<<PD3));  // Configure INT1/PD3 as input pin
	PORTD |= (1<<PD3); // Pull Up Resistor
	/*Trigger INT1 with the falling edge*/
	MCUCR |= (1<<ISC11);
	MCUCR &=~  (1 << ISC10);
	GICR  |= (1<<INT1);    // Enable external interrupt pin INT1
	/* End of INT1 init Function*/
	/* Initialize the LCD Driver */
	SPI_initSlave();
	LCD_init();
	/* Initialize the SPI driver as Slave */
	SREG |= (1<<7);
	while (1) {
		LCD_intgerToString(temp);
		LCD_displayString(" HI");
		_delay_ms(500);
		LCD_clearScreen();
	}
}

