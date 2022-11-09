/*
 * dio.h
 *
 *  Created on: 9 Nov 2022
 *      Author: MR.MAHMOUD
 */

#ifndef DIO_H_
#define DIO_H_
void DIO_setupPinDirection(char port_number,char pin_number,char direction);
void DIO_writePin(char port_number,char pin_number,char value);
char DIO_readPin(char port_number,char pin_number);


#endif /* DIO_H_ */
