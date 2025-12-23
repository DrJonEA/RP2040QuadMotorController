/*
 * Arduino.h
 *
 *  Created on: 23 Dec 2025
 *      Author: jondurrant
 */

#ifndef EXP_PID_PORT_AUTOTUNEPID_ARDUINO_H_
#define EXP_PID_PORT_AUTOTUNEPID_ARDUINO_H_

#include "pico/stdlib.h"
#include "math.h"

#define PI M_PI

//float constrain(float x, float a, float b);
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

long map(long x, long in_min, long in_max, long out_min, long out_max);

unsigned long millis();



#endif /* EXP_PID_PORT_AUTOTUNEPID_ARDUINO_H_ */
