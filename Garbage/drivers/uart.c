#include "uart.h"


void UART_init(void)
{
	/*Initializing UART To 9600 Baud Rate, No Parity and one stop bit on 16MHz Processor Frequency.*/
	/*UCSRA*/
	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/*UCSRB*/
	/* RXEN = 1 for Receiver Enable
	 * TXEN = 1 for Transmitter Enable
	 * UCSZ2 = 0 for 8-bit character size mode*/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/*UCSRC*/
	/*URSEL = 1 for writing in UCSRC register instead of UBRRH
	 * UCSZ0 and UCSZ1 = 1 for 8-bit mode character size */
	UCSRC = (1<<URSEL) | (1<<UCSZ0) | (1<<UCSZ1);

	/*UBRR*/
	UBRRL = 207; /*16 MHz CPU Frequency and 9600 Baud Rate.*/

}

void UART_sendByte(const uint8 data)
{
	while(!(UCSRA & (1<<UDRE))); /*Wait to UDRE Flag to be set when UDR is empty*/
	UDR = data; /*Puts the required data in UDR register and Clears UDRE Flag*/
}

uint8 UART_receiveByte(void)
{
	while(!(UCSRA &(1<<RXC))); /*Wait to RXC Flag to be set when UART receives data*/
	return UDR; /*Return the data received and automatically clear the RXC Flag*/
}

void UART_sendString(const uint8 *str)
{
	/* Looping on function UART_sendByte until sending the NULL character. */
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

void UART_receiveString(uint8 *str)
{
	/* Looping on function UART_receiveByte until receiving the NULL Character. */
	uint8 i = 0;

	/*Receive 1 Byte to have data we can loop on.*/
	str[i] = UART_receiveByte();

	while(str[i] != '\0')
	{
		i++;
		str[i] = UART_receiveByte();
	}

	str[i] = '\0';
}
