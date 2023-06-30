/*
 * interrupts.h
 *
 *  Created on: Jun 20, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef MCAL_INTERRUPTS_INTERRUPTS_H_
#define MCAL_INTERRUPTS_INTERRUPTS_H_

#include "../../UTILITIES/std_types.h"
#include "../DIO/dio.h"

#define MCUCR    (*(volatile uint8*)(0x55))
#define ISC11 3
#define ISC10 2

#define GICR    (*(volatile uint8*)(0x5B))
#define INT1 7

#define SREG (*(volatile uint8*)(0x5F))


#define _VECTOR(N) __vector_ ## N

#  define __INTR_ATTRS used, externally_visible

# define sei()  __asm__ __volatile__ ("sei" ::: "memory")

# define cli()  __asm__ __volatile__ ("cli" ::: "memory")

								/* ISR Macro */
#  define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#define INT1_vect			_VECTOR(2)

void INT1_Init(void);

#endif /* MCAL_INTERRUPTS_INTERRUPTS_H_ */
