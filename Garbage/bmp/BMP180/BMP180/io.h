#ifndef IO_H_
#define IO_H_
#include"std_types.h"
 /*-----------------------------------------------------------------------*
 |                                  DIO                                   |
 *-----------------------------------------------------------------------*/
#define PORTA (*(volatile uint8*)0x3B)
#define DDRA (*(volatile uint8*)0x3A)
#define PINA (*(volatile uint8*)0x39)

#define PORTB (*(volatile uint8*)0x38)
#define DDRB (*(volatile uint8*)0x37)
#define PINB (*(volatile uint8*)0x36)

#define PORTC (*(volatile uint8*)0x35)
#define DDRC (*(volatile uint8*)0x34)
#define PINC (*(volatile uint8*)0x33)

#define PORTD (*(volatile uint8*)0x32)
#define DDRD (*(volatile uint8*)0x31)
#define PIND (*(volatile uint8*)0x30)

 /*-----------------------------------------------------------------------*
 |                                   ADC                                  |
 *-----------------------------------------------------------------------*/
#define ADMUX   (*(volatile uint8*)0x27)

#define MUX0      0
#define MUX1      1
#define MUX2      2
#define MUX3      3
#define MUX4      4
#define ADLAR     5
#define REFS0     6
#define REFS1     7


#define ADCSRA  (*(volatile uint8*)0x26)

#define ADPS0     0
#define ADPS1     1
#define ADPS2     2
#define ADIE      3
#define ADIF      4
#define ADATE     5
#define ADSC      6
#define ADEN      7


#define ADCH    (*(volatile uint8*)0x25)

#define ADCL    (*(volatile uint8*)0x24)


#endif
