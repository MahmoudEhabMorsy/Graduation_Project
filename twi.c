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

#include "common_macros.h"

#include "twi_config.h"
#include "twi_map.h"

void TWI_init(void)
{
   /* Bit Rate Configuration */
#if BIT_RATE >= MINIMUM_BIT_RATE
	TWBR = BIT_RATE;
#else
#error "Invalid I2C bit rate configuration. Minimum bit rate allowed is 10."
#endif
	/* Prescaler Configuration */
#if PRESCALER_1 == PRESCALER
	CLR_BIT(TWSR, TWPS1);
	CLR_BIT(TWSR, TWPS0);
#elif PRESCALER_4 == PRESCALER
	CLR_BIT(TWSR, TWPS1);
	SET_BIT(TWSR, TWPS0);
#elif PRESCALER_16 == PRESCALER
	SET_BIT(TWSR, TWPS1);
	CLR_BIT(TWSR, TWPS0);
#elif PRESCALER_64 == PRESCALER
	SET_BIT(TWSR, TWPS1);
	SET_BIT(TWSR, TWPS0);
#else
#error "Invalid I2C prescaler configuration"
#endif
	/* Slave Address Configuration */
#if SLAVE_ADDRESS >= MINIMUM_ADDRESS && SLAVE_ADDRESS <= MAXIMUM_ADDRESS
	TWAR = (SLAVE_ADDRESS<<1);
	
#else
#error "Invalid I2C slave address configuration (out of range)."
#endif
#if ENABLE_GENERAL_CALL == GENERAL_CALL
	SET_BIT(TWAR, TWGCE);
#elif DISABLE_GENERAL_CALL == GENERAL_CALL
	CLR_BIT(TWAR, TWGCE);
#else
#error "Invalid general call configuration"
#endif
	/* Enable I2C Peripheral */
	SET_BIT(TWCR, TWEN);
	return NO_ERROR;
}

void TWI_start(void)
{
    /* 
	 * Clear the TWINT flag before sending the start bit TWINT=1
	 * send the start bit by TWSTA=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
    
    /* Wait for TWINT flag set in TWCR Register (start bit is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

void TWI_stop(void)
{
    /* 
	 * Clear the TWINT flag before sending the stop bit TWINT=1
	 * send the stop bit by TWSTO=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

void TWI_writeByte(uint8 data)
{
    /* Put data On TWI data Register */
    TWDR = data;
    /* 
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}

uint8 TWI_readByteWithACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable sending ACK after reading or receiving data TWEA=1
	 * Enable TWI Module TWEN=1 
	 */ 
    TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_readByteWithNACK(void)
{
	/* 
	 * Clear the TWINT flag before reading the data TWINT=1
	 * Enable TWI Module TWEN=1 
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}

uint8 TWI_getStatus(void)
{
    uint8 status;
    /* masking to eliminate first 3 bits and get the last 5 bits (status bits) */
    status = TWSR & 0xF8;
    return status;
}
