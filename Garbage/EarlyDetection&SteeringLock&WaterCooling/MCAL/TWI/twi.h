 /******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Header file for the TWI(I2C) AVR driver
 *
*******************************************************************************/ 

#ifndef TWI_H_
#define TWI_H_

#include "../../UTILITIES/std_types.h"


/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* I2C Status Bits in the TWSR Register */
#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_W_NACK 0x20 /* Master transmit ( slave address + Write request ) to slave + NACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void TWI_init(void);
uint8 TWI_Start(uint8 slave_write_adress);
uint8 TWI_Repeated_start(uint8 slave_write_adress);
void TWI_Start_Wait(char slave_write_address);			/* I2C start wait function */
void TWI_Stop(void);
void TWI_WriteByte(uint8 data);
uint8 TWI_ReadByteWithACK(void);
uint8 TWI_ReadByteWithNACK(void);
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */