#include "MPU6050.h"

void MPU6050_Init(void)
{
    _delay_ms(150);			/* Power up time >100ms */
	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);	/* Start with device write address */
	TWI_WriteByte(SMPLRT_DIV);	/* Write to sample rate register */
	TWI_WriteByte(GYRO_SAMPLE_RATE_1KHZ);		/* 1KHz sample rate */
	TWI_Stop();

	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);
	TWI_WriteByte(PWR_MGMT_1);	/* Write to power management register */
	TWI_WriteByte(GYRO_X_AXIS_REF);		/* X axis gyroscope reference frequency */
	TWI_Stop();

	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);
	TWI_WriteByte(CONFIG);		/* Write to Configuration register */
	TWI_WriteByte(MPU_FREQ_8KHZ);		/* Fs = 8KHz */
	TWI_Stop();

	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);
	TWI_WriteByte(GYRO_CONFIG);	/* Write to Gyro configuration register */
	TWI_WriteByte(FULL_SCALE_FACTOR);		/* Full scale range +/- 2000 degree/C */
	TWI_Stop();

	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);
	TWI_WriteByte(INT_ENABLE);	/* Write to interrupt enable register */
	TWI_WriteByte(0x01);
	TWI_Stop();

}
void MPU_Start(void)
{
	TWI_Start_Wait(MPU6050_WRITE_ADDRESS);		/* I2C start with device write address */
	TWI_WriteByte(ACCEL_XOUT_H);	/* Write start location address from where to read */ 
	TWI_Repeated_Start(MPU6050_READ_ADDRESS);	/* I2C start with device read address */
}
void MPU6050_READ(volatile MPU6050_Data *Data_Ptr)
{
    MPU_Start();
	Acc_Read_x =  (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	Acc_Read_y =  (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	Acc_Read_z =  (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	temp = (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	Gyro_Read_x = (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	Gyro_Read_y = (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithACK());
	Gyro_Read_z = (((int)TWI_ReadByteWithACK()<<8) | (int)TWI_ReadByteWithNACK());
	TWI_Stop();
	/* Divide raw value by sensitivity scale factor to get real values for acceleration */
	Data_Ptr->Acc_x = (Acc_Read_x/ACCEL_SENSTIVITY_FACTOR);
	Data_Ptr->Acc_y = (Acc_Read_y/ACCEL_SENSTIVITY_FACTOR);
	Data_Ptr->Acc_z = (Acc_Read_z/ACCEL_SENSTIVITY_FACTOR);
	/* Divide raw value by sensitivity scale factor to get real values for gyroscope */
	Data_Ptr->Gyro_x = (Gyro_Read_x/GYRO_SENSTIVITY_FACTOR);
	Data_Ptr->Gyro_y = (Gyro_Read_y/GYRO_SENSTIVITY_FACTOR);
	Data_Ptr->Gyro_z = (Gyro_Read_z/GYRO_SENSTIVITY_FACTOR);
	/* Convert temperature in °/c using formula */
	Data_Ptr->Temperature = (temp/340.00)+36.53;

}
