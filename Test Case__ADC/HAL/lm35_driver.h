/*=======================================================================
 =																		=
 = [FILE NAME]:		lm35_driver.h										=
 =																		=
 = [AUTHOR]:		Ahmed Yasser										=
 =																		=
 = [DATE CREATED]:	17/12/2022											=
 =																		=
 = [DESCRIPTION]:	LM35 - Header file for LM35 Module					=
 =																		=
 =======================================================================*/

#ifndef LM35_DRIVER_H_
#define LM35_DRIVER_H_

#define LM35_SENESOR_CHANNEL			2
#define LM35_SENSOR_RESOLUTION			0.01


uint8 LM35_getTemperature(void);

#endif /* LM35_DRIVER_H_ */
