/*
 * gps.h
 *
 *  Created on: Dec 17, 2022
 *      Author: Mahmoud Qotp
 */

#ifndef GPS_H_
#define GPS_H_
#include "std_types.h"

void GPS_init();

void GPS_getCoordinates(float64 *a_latitude, float64 *a_longitude);

#endif /* GPS_H_ */
