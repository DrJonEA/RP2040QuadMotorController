/*
 * motor.h
 *
 *  Created on: 18 Dec 2025
 *      Author: jondurrant
 */

#ifndef EXP_SRC_MOTOR_H_
#define EXP_SRC_MOTOR_H_

#include "pico/stdlib.h"
#include "stdio.h"
#include "hardware/pwm.h"

#define MOTOR_ROTATION (30*11)

class Motor {
public:
	Motor();
	Motor(
			uint8_t gp_cw,
			uint8_t gp_ccw,
			uint8_t gp_enc_a,
			uint8_t gp_enc_b);
	virtual ~Motor();

	void init(
			uint8_t gp_cw,
			uint8_t gp_ccw,
			uint8_t gp_enc_a,
			uint8_t gp_enc_b
			);


	void throttle16(uint16_t x, bool cw=true);

	uint16_t getCWCount();
	uint16_t getCCWCount();

	float getRADPS();

private:
	void  initCW();
	void initCCW();


	uint8_t xGPCW;
	uint8_t xGPCCW;
	uint8_t xGPENCA;
	uint8_t xGPENCB;
	bool xCW;

	uint32_t xLastTime = 0;
};

#endif /* EXP_SRC_MOTOR_H_ */
