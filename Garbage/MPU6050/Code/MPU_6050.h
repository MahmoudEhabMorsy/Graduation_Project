#ifndef MPU6050_H_
#define MPU6050_H_

#include "twi.h"
#include "MPU_6050_regs.h"
#include "util/delay.h"		/* Include delay header file */
#include "dio.h"
/******************Global Varialbles********************/
float32 Acc_Read_x,Acc_Read_y,Acc_Read_z;
float32 Gyro_Read_x,Gyro_Read_y,Gyro_Read_z;
float32 temp;
/*********************************************************/

#define MPU6050_WRITE_ADDRESS   (0xD0)
#define MPU6050_READ_ADDRESS    (0xD1)
#define FULL_SCALE_FACTOR	    (0x18)
#define ACCEL_SENSTIVITY_FACTOR (16384)
#define GYRO_SENSTIVITY_FACTOR  (16.4)

//Gyroscope sample rate
#define GYRO_SAMPLE_RATE_1KHZ 0x07
#define GYRO_SAMPLE_RATE_2KHZ 0x03
#define GYRO_SAMPLE_RATE_4KHZ 0x01
//MPU clock source
#define MPU_CLK_INTERNAL_8KHZ 0x00
#define GYRO_X_AXIS_REF 0x01
#define GYRO_Y_AXIS_REF 0x02   //Recommended by data sheet
#define GYRO_Z_AXIS_REF 0x03
//frequncy
#define MPU_FREQ_1KHZ 0x01
#define MPU_FREQ_8KHZ 0x00

// MPU6050 Out data
typedef struct
{
	float32 Acc_x;
	float32 Acc_y;
	float32 Acc_z;
	float32 Gyro_x;
	float32 Gyro_y;
	float32 Gyro_z;
	float32 Temperature;
}MPU6050_Data;

void MPU6050_Init(void);
void MPU_Start(void);
void MPU6050_READ(volatile MPU6050_Data *Data_Ptr);
#endif /* MPU6050_H_ */
