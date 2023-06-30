/************************************************************************
 *																		*
 * [FILE NAME]:		bmp180.c											*
 *																		*
 * [AUTHOR]:		Ahmed Y Kaead										*
 *																		*
 * [DATE CREATED]:	13/04/2023											*
 *																		*
 * [DESCRIPTION]:	BMP180 - source file for BMP180 Module				*
 *																		*
 ************************************************************************/

#include "../../MCAL/TWI/twi.h"
#include "bmp180.h"
#include <util/delay.h>
#include "../../UTILITIES/common_macros.h"


/* Calibration Data */
sint16 AC1 = 0, AC2 = 0, AC3 = 0, B1 = 0;
sint16 B2 = 0, MB = 0, MC = 0, MD = 0;
uint16 AC4 = 0, AC5 = 0, AC6 = 0;

/* Variables used in the below functions */
sint32 X1 = 0, X2 = 0, B5 = 0, UT = 0;
sint32 X3 = 0, B3 = 0, B6 = 0, P = 0, UP = 0;
uint32 B4 = 0, B7 = 0;
void delay(void);
void BMP180_ReadCalb(void) {

	uint8_t Callib_Data[22] = { 0 };
	uint16_t Callib_Start = 0xAA;

	for (int i = 0; i < 22; i++) {
		TWI_Start_Wait(BMP180_ADDRESS_W);// To write
		_delay_us(10);
		TWI_WriteByte(Callib_Start + i);
		_delay_us(10);
		TWI_Repeated_start(BMP180_ADDRESS_R);	// To read
		_delay_us(10);
		Callib_Data[i] = TWI_ReadByteWithNACK();
		_delay_us(10);
		TWI_Stop();
		_delay_us(10);
	}

	AC1 = ((Callib_Data[0] << 8) | Callib_Data[1]);
	AC2 = ((Callib_Data[2] << 8) | Callib_Data[3]);
	AC3 = ((Callib_Data[4] << 8) | Callib_Data[5]);
	AC4 = ((Callib_Data[6] << 8) | Callib_Data[7]);
	AC5 = ((Callib_Data[8] << 8) | Callib_Data[9]);
	AC6 = ((Callib_Data[10] << 8) | Callib_Data[11]);
	B1 = ((Callib_Data[12] << 8) | Callib_Data[13]);
	B2 = ((Callib_Data[14] << 8) | Callib_Data[15]);
	MB = ((Callib_Data[16] << 8) | Callib_Data[17]);
	MC = ((Callib_Data[18] << 8) | Callib_Data[19]);
	MD = ((Callib_Data[20] << 8) | Callib_Data[21]);

}

uint32 Get_UP(void) {
	// calculate the value to write to the BMP180 control register based on the oversampling setting
	uint8 datatowrite = 0x34 + (OSS << 6);
	// array to store the raw pressure data
	uint8 Pressure_RAW[3] = { 0 };

	uint32 data = 0;

	// start the I2C communication with BMP180 by sending its address
	TWI_Start(BMP180_ADDRESS_W);
	delay();
	// send the address of the BMP180 control register to initiate the pressure measurement
	TWI_WriteByte(0xF4);
	delay();
	// send the value calculated above to start the measurement with the selected oversampling setting
	TWI_WriteByte(datatowrite);
	delay();
	// stop the I2C communication with BMP180
	TWI_Stop();
	_delay_ms(5);



	// start the I2C communication with BMP180 in read mode by sending its address with the read bit set
	// read the MSB of the raw pressure data and acknowledge the read
	TWI_Start_Wait(BMP180_ADDRESS_W);
	delay();
	TWI_WriteByte(0xF6);
	delay();
	TWI_Repeated_start(BMP180_ADDRESS_R);
	delay();// To read
	Pressure_RAW[0] = TWI_ReadByteWithNACK();
	delay();
	TWI_Stop();
	delay();
	// read the middle byte of the raw pressure data and acknowledge the read
	TWI_Start_Wait(BMP180_ADDRESS_W);
	delay();
	TWI_WriteByte(0xF7);
	delay();
	TWI_Repeated_start(BMP180_ADDRESS_R);
	delay();// To read
	Pressure_RAW[1] = TWI_ReadByteWithNACK();
	delay();
	TWI_Stop();
	delay();
	// read the LSB of the raw pressure data and don't acknowledge the read
	TWI_Start_Wait(BMP180_ADDRESS_W);
	delay();
	TWI_WriteByte(0xF8);
	delay();
	TWI_Repeated_start(BMP180_ADDRESS_R);
	delay();// To read
	Pressure_RAW[2] = TWI_ReadByteWithNACK();
	delay();
	TWI_Stop();
	// stop the I2C communication with BMP180

	// combine the raw pressure data into a single 24-bit value and shift it right to adjust for the oversampling setting

	data |= ((uint32_t) Pressure_RAW[0] << 16);
	data |= ((uint32_t) Pressure_RAW[1] << 8);
	data |= (uint32_t) Pressure_RAW[2];
	data = data >> (8 - OSS);
	//division by 2 power (8-oss which is in datasheet (0,1))

	return data;
}

uint32 Get_UT(void) {
	uint32 data = 0;

	uint8 datatowrite = 0x2E;
	// array to store the raw pressure data
	uint8 Temperature_RAW[2] = { 0 };
	// start the I2C communication with BMP180 by sending its address
	TWI_Start(BMP180_ADDRESS_W);
	delay();
	// send the address of the BMP180 control register to initiate the temperature measurement
	TWI_WriteByte(0xF4);
	delay();
	// send the value calculated above to start the measurement
	TWI_WriteByte(datatowrite);
	delay();
	// stop the I2C communication with BMP180
	TWI_Stop();

	_delay_ms(5);
	// start the I2C communication with BMP180 in read mode by sending its address with the read bit set
	// read the MSB of the raw temperature data and acknowledge the read
	TWI_Start_Wait(BMP180_ADDRESS_W);
	delay();
	TWI_WriteByte(0xF6);
	delay();
	TWI_Repeated_start(BMP180_ADDRESS_R);
	delay();// To read
	Temperature_RAW[0] = TWI_ReadByteWithNACK();
	delay();
	TWI_Stop();
	delay();
	// read the middle byte of the raw pressure data and acknowledge the read
	// read the LSB of the raw temperature data and don't acknowledge the read
	TWI_Start_Wait(BMP180_ADDRESS_W);
	delay();
	TWI_WriteByte(0xF7);
	delay();
	TWI_Repeated_start(BMP180_ADDRESS_R);
	delay();// To read
	Temperature_RAW[1] = TWI_ReadByteWithNACK();
	delay();
	TWI_Stop();
	// stop the I2C communication with BMP180

	data |= ((uint32_t) Temperature_RAW[0] << 8);
	data |= (uint32_t) Temperature_RAW[1];
	return data;
}

sint32 BMP180_calculateTemperature(void) {

	float32 temperature = 0;

	UT = Get_UT();

	X1 = ((UT - AC6) * (AC5 / (pow(2, 15))));
	X2 = (MC * (pow(2, 11))) / (X1 + MD);
       	B5 = X1 + X2;
	temperature = (B5 + 8) / (pow(2, 4));
	return temperature / 10.0;
}

sint32 BMP180_calculatePressure(void) {
	UP = Get_UP();

	X1 = ((UT - AC6) * (AC5 / (pow(2, 15))));
	X2 = (MC * (pow(2, 11))) / (X1 + MD);
	B5 = X1 + X2;
	B6 = B5 - 4000;
	X1 = (B2 * (B6 * B6 / (pow(2, 12)))) / (pow(2, 11));
	X2 = AC2 * B6 / (pow(2, 11));
	X3 = X1 + X2;
	B3 = (((AC1 * 4 + X3) << OSS) + 2) / 4;
	X1 = AC3 * B6 / (pow(2, 13));
	X2 = (B1 * (B6 * B6 / (pow(2, 12)))) / (pow(2, 16));
	X3 = ((X1 + X2) + 2) / (pow(2, 2));
	B4 = (AC4 * (uint32) (X3 + 32768)) / (pow(2, 15));
	B7 = ((uint32) UP - B3) * (50000 >> OSS);

	if (B7 < 0x80000000) {
		P = (B7 * 2) / B4;
	} else {
		P = (B7 / B4) * 2;
	}
	X1 = (P / (pow(2, 8))) * (P / (pow(2, 8)));
	X1 = (X1 * 3038) / (pow(2, 16));
	X2 = (-7357 * P) / (pow(2, 16));
	P = P + (X1 + X2 + 3791) / (pow(2, 4));

	P = P / 100;

	return P;
}

void BMP180_calculate(tyreState * readings) {
	readings->temperature = BMP180_calculateTemperature();
	readings->pressure = BMP180_calculatePressure();
	readings->wheel = FRONT_LEFT;
}

void BMP180_Start(void) {
	BMP180_ReadCalb();
}

void delay(void){
	_delay_us(10);
}
