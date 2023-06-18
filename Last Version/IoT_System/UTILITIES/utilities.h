/*
 * utilities.h
 *
 *  Created on: Feb 16, 2023
 *      Author: Mahmoud Qotp
 */

#ifndef UTILITIES_H_
#define UTILITIES_H_

#include "std_types.h"


#define NUMBER_OF_DIGITS_AFTERPOINT 5

void intToStrBuffered(sint16 number, uint8 *str, uint8 size);

uint8 intToStr(sint32 number, uint8 *str);

void floatToString(float32 number, uint8 *res);


#endif /* UTILITIES_H_ */
