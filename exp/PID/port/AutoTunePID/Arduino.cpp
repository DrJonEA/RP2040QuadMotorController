/*
 * Arduino.cpp
 *
 *  Created on: 23 Dec 2025
 *      Author: jondurrant
 */
#include "Arduino.h"
#include "stdio.h"

long map(long x, long in_min, long in_max, long out_min, long out_max){
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned long millis(){
	unsigned long now = to_ms_since_boot (get_absolute_time());
	//printf("%lu\n", now);
	return now;
}



