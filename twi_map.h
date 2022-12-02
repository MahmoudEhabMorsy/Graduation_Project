/**********************************************************************************************************
*
*	File name: 		PORT.h
*
*	Author: 		Mahmoud Abdellatif Basiony
*	
*	Date:		  	12/2/2022
*	
*	Description:	Memory Map for TWI/I2C	
*
***********************************************************************************************************/
#ifndef MCAL_TWI_TWI_MAP_H_
#define MCAL_TWI_TWI_MAP_H_

/**********************************************************************************************************/
/*  							             REGISTERS ADDRESSES							              */
/**********************************************************************************************************/
#define TWCR 								*((volatile uint8 *)0x56)
#define TWDR 								*((volatile uint8 *)0x23)
#define TWAR								*((volatile uint8 *)0x22)
#define TWSR 								*((volatile uint8 *)0x21)
#define TWBR 								*((volatile uint8 *)0x20)
/**********************************************************************************************************/



/**********************************************************************************************************/
/* 					                         TWCR REGISTER BITS		                					   */
/**********************************************************************************************************/
#define TWINT										7
#define TWEA										6
#define TWSTA										5
#define TWSTO										4
#define TWWC										3
#define TWEN										2
#define BIT1										1
#define TWIE										0
/**********************************************************************************************************/


/**********************************************************************************************************/
/* 					                          TWSR REGISTER BITS						            	   */
/**********************************************************************************************************/

#define TWPS1										1
#define TWPS0										0
/**********************************************************************************************************/



/**********************************************************************************************************/
/* 					                           TWAR REGISTER BITS		                			     */
/**********************************************************************************************************/

#define TWGCE										0
/**********************************************************************************************************/




/**********************************************************************************************************/
/* 					                           TWDR REGISTER BITS	                        						   */
/**********************************************************************************************************/

#define TWD0										0
/**********************************************************************************************************/

/**********************************************************************************************************/
/* 					                              BIT RATE RANGE						   	   */
/**********************************************************************************************************/
#define MINIMUM_BIT_RATE							10
/**********************************************************************************************************/


/**********************************************************************************************************/
/* 					                	        PRESCALER 							   	   */
/**********************************************************************************************************/
#define PRESCALER_1									1
#define PRESCALER_4									4
#define PRESCALER_16								16
#define PRESCALER_64								64
/**********************************************************************************************************/


/**********************************************************************************************************/
/* 					                            SLAVE ADDRESS RANGE							   */
/**********************************************************************************************************/
#define MINIMUM_ADDRESS								0x01
#define MAXIMUM_ADDRESS								0x77  //MAX  127 device
/**********************************************************************************************************/
/**********************************************************************************************************/
/* 					           GENERAL CALL - BROADCASTING						   */
/**********************************************************************************************************/
#define ENABLE_GENERAL_CALL							0
#define DISABLE_GENERAL_CALL						1
/**********************************************************************************************************/
#endif /*MCAL_TWI_TWI_MAP_H_*/