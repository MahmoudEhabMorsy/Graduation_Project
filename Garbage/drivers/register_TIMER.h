 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: register.h
 *
 * DesTIMSKcription: Commonly used Macros
 *
 * Author: Mahmoud Khaled
 *
 *******************************************************************************/

#ifndef REGISTER_H_
#define REGISTER_H_

#include "std_types.h"

/***************************************************************/
/*                     TIMER general Register
/***************************************************************/

#define TIMSK *((volatile uint8*) 0x59 ) //8-bit register
#define TIFR  *((volatile uint8*) 0x58 ) //8-bit register


/***************************************************************/
/*                     TIMER0 Register
/***************************************************************/ 

#define TCCR0 *((volatile uint8*) 0x53 ) //8-bit register 
#define TCNT0 *((volatile uint8*) 0x52 ) //8-bit register 
#define OCR0 *((volatile uint8*) 0x5C ) //8-bit register

/*   TCCR0  bits   */
#define CS00  0
#define CS01  1
#define CS02  2                         // (CS00&CS01&CS02) for prescaler
#define WGM01 3
#define COM00 4
#define COM01 5
#define WGM00 6
#define FOC0  7
/*   TIMSK  bits   */
#define TOIE0  0
#define OCIE0  1
/*   TIFR  bits   */
#define TOV0  0
#define OCF0  1


/***************************************************************/
/*                     TIMER1 Register
/***************************************************************/

#define TCCR1A *((volatile uint8*) 0x4F ) //8-bit register
#define TCCR1B *((volatile uint8*) 0x4E ) //8-bit register
#define TCNT1H *((volatile uint8*) 0x4D ) //8-bit register
#define TCNT1L *((volatile uint8*) 0x4C ) //8-bit register
#define OCR1AH *((volatile uint8*) 0x4B ) //8-bit register
#define OCR1AL *((volatile uint8*) 0x4A ) //8-bit register
#define OCR1BH *((volatile uint8*) 0x49 ) //8-bit register
#define OCR1BL *((volatile uint8*) 0x48  ) //8-bit register
/*   TCCR1A  bits   */
#define WGM10  0
#define WGM11  1
#define FOC1B  2
#define FOC1A  3
#define COM1B0 4
#define COM1B1 5                 // Bit 5:4 – COM1B1:0: Compare Output Mode for Channel B
#define COM1A0 6
#define COM1A1 7                 //Bit 7:6 – COM1A1:0: Compare Output Mode for Channel A

/*   TCCR1B  bits   */
#define CS10  0
#define CS11  1
#define CS12  2
#define WGM12  3
#define WGM13 4
#define ICES1 6
#define ICNC1 7

/*   TIMSK  bits   */
#define TOIE1  2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5

/*   TIFR  bits   */
#define TOV1  2
#define OCF1B  3
#define OCF1A  4
#define ICF1  5


/***************************************************************/
/*                     TIMER2 Register
/***************************************************************/

#define TCCR2 *((volatile uint8*) 0x45 ) //8-bit register
#define TCNT2 *((volatile uint8*) 0x44 ) //8-bit register
#define OCR2 *((volatile uint8*) 0x43 ) //8-bit register

/*   TCCR0  bits   */
#define CS20  0
#define CS21  1
#define CS22  2                         // (CS00&CS01&CS02) for prescaler
#define WGM21 3
#define COM20 4
#define COM21 5
#define WGM20 6
#define FOC2  7
/*   TIMSK  bits   */
#define TOIE2  6
#define OCIE2  7
/*   TIFR  bits   */
#define TOV2  6
#define OCF2  7

#endif
