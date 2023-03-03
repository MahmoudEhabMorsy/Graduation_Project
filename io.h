/*=======================================================================
 =																		                                                    =
 = [FILE NAME]:		io.h																																																			=
 =																																																																		 			=
 = [AUTHOR]:		Ahmed Y Kaead , Mahmoud Ehab																														=
 =																																																																			 		=
 = [DATE CREATED]:	02/12/2022  																																									=
 =																																																																				 	=
 = [DESCRIPTION]:	AVR atrmega 32 io header file.																						 	=
 =																																																																				 	=
 =======================================================================*/

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

/*-----------------------------------------------------------------------*
 |                    	    External Interrupts                           |
 *-----------------------------------------------------------------------*/
#define GICR    (*(volatile uint8*)0x5B)

#define IVCE     0
#define IVSEL    1
#define INT2     5
#define INT1     6
#define INT0     7


#define GIFR    (*(volatile uint8*)0x5A)

#define INTF2     5
#define INTF1     6
#define INTF0     7


#define MCUCR    (*(volatile uint8*)0x55)

#define ISC00     0
#define ISC01     1
#define ISC10     2
#define ISC11     3
#define SM0	      4
#define SM1       5
#define SM2       6
#define SE        7


#define MCUCSR    (*(volatile uint8*)0x54)

#define PORF      0
#define EXTRF     1
#define BORF      2
#define WDRF      3
#define JTRF	     4
#define ISC2      6
#define JTD       7

#endif
