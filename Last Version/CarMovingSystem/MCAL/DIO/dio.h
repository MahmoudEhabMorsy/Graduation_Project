/*
 * dio.h
 *
 *  Created on: 9 Nov 2022
 *      Author: MR.MAHMOUD
 */

#ifndef DIO_H_
#define DIO_H_
#include "../../UTILITIES/std_types.h"

/*******************************************************************************
*                              Memory Mapping                                  *
*******************************************************************************/
#define PORTA (*(volatile uint8*)(0x3B))
#define DDRA (*(volatile uint8*)(0x3A))
#define PINA (*(volatile uint8*)(0x39))

#define PORTB (*(volatile uint8*)(0x38))
#define DDRB (*(volatile uint8*)(0x37))
#define PINB (*(volatile uint8*)(0x36))

#define PORTC (*(volatile uint8*)(0x35))
#define DDRC (*(volatile uint8*)(0x34))
#define PINC (*(volatile uint8*)(0x33))

#define PORTD (*(volatile uint8*)(0x32))
#define DDRD (*(volatile uint8*)(0x31))
#define PIND (*(volatile uint8*)(0x30))
 /*******************************************************************************
  *                                Definitions                                  *
  *******************************************************************************/

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

  /*******************************************************************************
   *                               Types Declaration                             *
   *******************************************************************************/
typedef enum
{
	PIN_INPUT, PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT, PORT_OUTPUT = 0xFF
}GPIO_PortDirectionType;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DIO_setupPinDirection(uint8 port_number, uint8 pin_number, uint8 direction);

void DIO_writePin(uint8 port_number, uint8 pin_number, uint8 value);

uint8 DIO_readPin(uint8 port_number, uint8 pin_number);

void DIO_setupPortDirection(uint8 port_number, GPIO_PortDirectionType direction);

void DIO_writePort(uint8 port_number, uint8 value);

uint8 DIO_readPort(uint8 port_number);

void DIO_togglePin(uint8 port_num, uint8 pin_num);

#endif 
