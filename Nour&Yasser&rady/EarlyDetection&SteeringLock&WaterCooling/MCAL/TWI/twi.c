/******************************************************************************
 *
 * Module: TWI(I2C)
 *
 * File Name: twi.h
 *
 * Description: Source file for the TWI(I2C) AVR driver
 *
 *******************************************************************************/

#include "twi.h"

#include "../../CommonDef//common_macros.h"

#include "twi_config.h"
#include "twi_map.h"
/*======================================================================*
 * [Function Name]:	TWI_init()											*
 * [Description]:	Function responsible for initialize the TWI driver. *
 * 																		*
 * [Args]							*
 * [Return]															*
 *======================================================================*/

void TWI_init(void) {
	/* Bit Rate Configuration */
#if BIT_RATE >= MINIMUM_BIT_RATE
	TWBR = BIT_RATE;
#else
#error "Invalid I2C bit rate configuration. Minimum bit rate allowed is 10."
#endif
	/* Prescaler Configuration */
#if PRESCALER_1 == PRESCALER
	CLEAR_BIT(TWSR, TWPS1);
	CLEAR_BIT(TWSR, TWPS0);
#elif PRESCALER_4 == PRESCALER
	CLEAR_BIT(TWSR, TWPS1);
	SET_BIT(TWSR, TWPS0);
#elif PRESCALER_16 == PRESCALER
	SET_BIT(TWSR, TWPS1);
	CLEAR_BIT(TWSR, TWPS0);
#elif PRESCALER_64 == PRESCALER
	SET_BIT(TWSR, TWPS1);
	SET_BIT(TWSR, TWPS0);
#else
#error "Invalid I2C prescaler configuration"
#endif
	/* Slave Address Configuration */
#if SLAVE_ADDRESS >= MINIMUM_ADDRESS && SLAVE_ADDRESS <= MAXIMUM_ADDRESS
	TWAR = (SLAVE_ADDRESS << 1);

#else
#error "Invalid I2C slave address configuration (out of range)."
#endif
#if ENABLE_GENERAL_CALL == GENERAL_CALL
	SET_BIT(TWAR, TWGCE);
#elif DISABLE_GENERAL_CALL == GENERAL_CALL
	CLEAR_BIT(TWAR, TWGCE);
#else
#error "Invalid general call configuration"
#endif
	/* Enable I2C Peripheral */
	SET_BIT(TWCR, TWEN);
}
/*======================================================================*
 * [Function Name]:	TWI_start()											*
 * [Description]:	Function responsible for start the TWI communication. *
 * 																		*
 * [Args]		uint8 slave_write_adress						*
 * [Return]															*
 *======================================================================*/

uint8 TWI_Start(uint8 slave_write_adress) {
	uint8 status;

	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	status = TWI_getStatus();
	if (status != TWI_START) /* Check weather start condition transmitted successfully or not? */
		return 0;
	TWDR = slave_write_adress; /* If yes then write SLA+W in TWI data register */
	TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	status = TWI_getStatus();
	if (status == TWI_MT_SLA_W_ACK) /* Check weather SLA+W transmitted & ack received or not? */
		return 1; /* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	if (status == TWI_MT_SLA_W_NACK) /* Check weather SLA+W transmitted & nack received or not? */
		return 2; /* If yes then return 2 to indicate nack received i.e. device is busy */
	else
		return 3; /* Else return 3 to indicate SLA+W failed */
}

/*======================================================================*
 * [Function Name]:	TWI_Repeated_start()									*
 * [Description]:	Function responsible for re-start the TWI communication.*
 * 																			*
 * [Args]		uint8 slave_write_adress									*
 * [Return]																	*
 *======================================================================*/
uint8 TWI_Repeated_start(uint8 slave_write_adress) {
	uint8 status;

	/*
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

	/* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	status = TWI_getStatus();
	if (status != TWI_REP_START) /* Check weather start condition transmitted successfully or not? */
		return 0;
	TWDR = slave_write_adress; /* If yes then write SLA+W in TWI data register */
	TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	status = TWI_getStatus();
	if (status == TWI_MT_SLA_R_ACK) /* Check weather SLA+W transmitted & ack received or not? */
		return 1; /* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	if (status == TWI_MT_SLA_W_NACK) /* Check weather SLA+W transmitted & nack received or not? */
		return 2; /* If yes then return 2 to indicate nack received i.e. device is busy */
	else
		return 3; /* Else return 3 to indicate SLA+W failed */
}
/*======================================================================*
 * [Function Name]:	TWI_Start_Wait()									*
 * [Description]:	Function responsible for Start the TWI communication and wait if there is problem.*
 * 																			*
 * [Args]		uint8 slave_write_adress									*
 * [Return]																	*
 *======================================================================*/
void TWI_Start_Wait(char slave_write_address) /* I2C start wait function */
{
	uint8 status; /* Declare variable */
	while (1) {
		TWCR = (1 << TWSTA) | (1 << TWEN) | (1 << TWINT); /* Enable TWI, generate start condition and clear interrupt flag */
		while (BIT_IS_CLEAR(TWCR, TWINT))
			; /* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
		if (status != TWI_START) /* Check weather start condition transmitted successfully or not? */
			continue; /* If no then continue with start loop again */
		TWDR = slave_write_address; /* If yes then write SLA+W in TWI data register */
		TWCR = (1 << TWEN) | (1 << TWINT); /* Enable TWI and clear interrupt flag */
		while (BIT_IS_CLEAR(TWCR, TWINT))
			; /* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8; /* Read TWI status register with masking lower three bits */
		if (status != TWI_MT_SLA_W_ACK) /* Check weather SLA+W transmitted & ack received or not? */
		{
			TWI_Stop(); /* If not then generate stop condition */
			continue; /* continue with start loop again */
		}
		break; /* If yes then break loop */
	}
}
/*======================================================================*
 * [Function Name]:	TWI_stop()									*
 * [Description]:	Function responsible for stop the TWI communication *
 * 																*
 * [Args]		void											*
 * [Return]			void										*
 *======================================================================*/
void TWI_Stop(void) {
	/*
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}
/*======================================================================*
 * [Function Name]:	TWI_writeByte()									*
 * [Description]:	Function responsible for sending 1 byte *
 * 																*
 * [Args]		uint8 data											*
 * [Return]			void										*
 *======================================================================*/
void TWI_WriteByte(uint8 data) {
	/* Put data On TWI data Register */
	TWDR = data;
	/*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register(data is send successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
}
/*======================================================================*
 * [Function Name]:	TWI_readByteWithACK()									*
 * [Description]:	Function responsible for reading 1 byte with ack *
 * 																*
 * [Args]				void									*
 * [Return]			uint8 data										*
 *======================================================================*/
uint8 TWI_ReadByteWithACK(void) {
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}
/*======================================================================*
 * [Function Name]:	TWI_readByteWithNACK()									*
 * [Description]:	Function responsible for reading 1 byte with NACK *
 * 																*
 * [Args]				void									*
 * [Return]			uint8 data										*
 *======================================================================*/
uint8 TWI_ReadByteWithNACK(void) {
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
	TWCR = (1 << TWINT) | (1 << TWEN);
	/* Wait for TWINT flag set in TWCR Register (data received successfully) */
	while (BIT_IS_CLEAR(TWCR, TWINT))
		;
	/* Read Data */
	return TWDR;
}
/*======================================================================*
 * [Function Name]:	TWI_getStatus()									*
 * [Description]:	FET STATUS from TWSR register *
 * 																*
 * [Args]													*
 * [Return]			uint8 status									*
 *======================================================================*/
uint8 TWI_getStatus(void) {
	uint8 status;
	/* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
	status = TWSR & 0xF8;
	return status;
}
