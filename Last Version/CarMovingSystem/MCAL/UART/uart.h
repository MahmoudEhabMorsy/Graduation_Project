 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Mahmoud Qotp
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "../../UTILITIES/std_types.h"
#include "../../UTILITIES/common_macros.h" 

/*******************************************************************************
*                              Memory Mapping                                  *
*******************************************************************************/
							/* USART IO Data Register */
#define UDR   		(*((volatile uint8 *) (0x2C)))

					/* USART Control and Status Register A */
#define UCSRA 		(*((volatile uint8 *) (0x2B)))

/* UCSRA Bits */
#define MPCM 0
#define U2X 1
#define PE 2
#define DOR 3
#define FE 4
#define UDRE 5
#define TXC 6
#define RXC 7

				 	 /* USART Control and Status Register B */
#define UCSRB 		(*((volatile uint8 *) (0x2A)))

/* UCSRB Bits */
#define TXB8 0
#define RXB8 1
#define UCSZ2 2
#define TXEN 3
#define RXEN 4
#define UDRIE 5
#define TXCIE 6
#define RXCIE 7

						/* USART Baud Rate Register Low Byte */
#define UBRRL 		(*((volatile uint8 *) (0x29)))

					 /* USART Control and Status Register C */
#define UCSRC 		(*((volatile uint8 *) (0x40)))

/* UCSRC Bits */
#define UCPOL 0
#define UCSZ0 1
#define UCSZ1 2
#define USBS 3
#define UPM0 4
#define UPM1 5
#define UMSEL 6
#define URSEL 7


					/* USART Baud Rate Register for the 4 MSBs UBRR[11:8]*/
#define UBRRH 		(*((volatile uint8 *) (0x40)))


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_receiveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */
