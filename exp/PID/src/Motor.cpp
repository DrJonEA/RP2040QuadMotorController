/*
 * Motor.cpp
 *
 *  Created on: 18 Dec 2025
 *      Author: jondurrant
 */

#include "Motor.h"
#include <Math.h>

Motor::Motor() {
	// TODO Auto-generated constructor stub
}

Motor::Motor(
		uint8_t gp_cw,
		uint8_t gp_ccw,
		uint8_t gp_enc_a,
		uint8_t gp_enc_b
		) {
	init(gp_cw, gp_ccw, gp_enc_a, gp_enc_b);
}

Motor::~Motor() {
	// TODO Auto-generated destructor stub
}


void Motor::init(
		uint8_t gp_cw,
		uint8_t gp_ccw,
		uint8_t gp_enc_a,
		uint8_t gp_enc_b
		){
	uint sliceNum;
	 xGPCW = gp_cw;
	 xGPCCW = gp_ccw;
	 xGPENCA = gp_enc_a;
	 xGPENCB = gp_enc_b;

	gpio_init(xGPCW);
	gpio_set_function(xGPCW, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGPCW, 0);
	sliceNum = pwm_gpio_to_slice_num(xGPCW);
	pwm_set_enabled(sliceNum, true);

	gpio_init(xGPCCW);
	gpio_set_function(xGPCCW, GPIO_FUNC_PWM);
	pwm_set_gpio_level(xGPCCW, 0);
	sliceNum = pwm_gpio_to_slice_num(xGPCCW);
	pwm_set_enabled(sliceNum, true);

	gpio_init(xGPENCA);
	if (pwm_gpio_to_channel(xGPENCA) != PWM_CHAN_B){
			printf("ERROR - GPIO Must be PWM Channel B\n");
	}
	gpio_set_function(xGPENCA, GPIO_FUNC_PWM);
	gpio_init(xGPENCB);
	if (pwm_gpio_to_channel(xGPENCB) != PWM_CHAN_B){
			printf("ERROR - GPIO Must be PWM Channel B\n");
	}
	gpio_set_function(xGPENCB, GPIO_FUNC_PWM);

	//initCW();
	throttle16(0);
}

void Motor::throttle16(uint16_t x, bool cw){
	if (x == 0){
		xRPS = 0.0;
	}
	if (cw){
		pwm_set_gpio_level(xGPCCW, 0);
		initCW();
		pwm_set_gpio_level(xGPCW, x);
	} else {
		pwm_set_gpio_level(xGPCW, 0);
		initCCW();
		pwm_set_gpio_level(xGPCCW, x);
	}
	getRADPS();
}




void Motor::initCW(){
	uint encSlice = pwm_gpio_to_slice_num(xGPENCA);
	uint cwSlice = pwm_gpio_to_slice_num(xGPCW);
	pwm_config cfg = pwm_get_default_config();
	pwm_init(cwSlice, &cfg, true);
	pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_FALLING);
	pwm_config_set_clkdiv(&cfg, 1);
	pwm_init(encSlice, &cfg, true);
	pwm_set_counter ( encSlice,  0);
	//pwm_set_enabled(slice_num, true);
	xCW = true;
}

void Motor::initCCW(){
	uint encSlice = pwm_gpio_to_slice_num(xGPENCB);
	uint cwSlice = pwm_gpio_to_slice_num(xGPCCW);
	pwm_config cfg = pwm_get_default_config();
	pwm_init(cwSlice, &cfg, true);
	pwm_config_set_clkdiv_mode(&cfg, PWM_DIV_B_FALLING);
	pwm_config_set_clkdiv(&cfg, 1);
	pwm_init(encSlice, &cfg, true);
	pwm_set_counter ( encSlice,  0);
	xCW = false;
}

uint16_t Motor::getCWCount(){
	uint slice_num = pwm_gpio_to_slice_num(xGPENCA);
	return pwm_get_counter (slice_num);
}

uint16_t Motor::getCCWCount(){
	uint slice_num = pwm_gpio_to_slice_num(xGPENCB);
	return pwm_get_counter (slice_num);
}

float Motor::getRADPS(){
	uint slice_num;
	uint32_t now = to_ms_since_boot (get_absolute_time());
	if (xCW){
		slice_num = pwm_gpio_to_slice_num(xGPENCA);
	} else {
		slice_num = pwm_gpio_to_slice_num(xGPENCB);
	}

	uint16_t count = pwm_get_counter (slice_num);
	uint32_t ms = now - xLastTime;

	if (count < 1){
		if (ms > 1000){
			xRPS = 0.0;
		}
		return xRPS;
	}

	 pwm_set_counter ( slice_num,  0);

	 xLastTime = now;
	 float rad = (float)count / (float)MOTOR_ROTATION * 2.0 * M_PI;
	 if (xCW){
		 xRadPos += rad;
	 } else {
		 xRadPos -= rad;
	 }
	 xRPS = rad / (ms / 1000.0);
	 //printf("Count %u, %u ms, %f rad, %f rps\n", count, ms, rad, xRPS);
	 return xRPS;
}

void Motor::setThrottle(float r, bool cw){
	//printf("SetThrottle(%f)\n", r);
	xThrottle = r;
	xCW = cw;
	uint16_t t;
	if (r >= 1.0){
		t = 0xFFFF;
	} else {
		t	= (float)0xFFFF * r;
	}
	throttle16(t, xCW);
}

float Motor::getThrottle(){
	return xThrottle;
}

bool Motor::isClockwise(){
	return xCW;
}

void Motor::setClockwise(bool cw ){
	xCW = cw;
	if (xCW){
		initCW();
	} else {
		initCCW();
	}
}

float Motor::getDeltaRad(bool reset){
	float res = xRadPos;
	if (reset){
		xRadPos = 0.0;
	}
	return res;
}
