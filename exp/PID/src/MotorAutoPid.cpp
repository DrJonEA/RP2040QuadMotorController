/*
 * MotorAutoPid.cpp
 *
 *  Created on: 23 Dec 2025
 *      Author: jondurrant
 */

#include "MotorAutoPid.h"

MotorAutoPid::MotorAutoPid() {
	pidInit();

}

MotorAutoPid::MotorAutoPid(
		uint8_t gp_cw,
		uint8_t gp_ccw,
		uint8_t gp_enc_a,
		uint8_t gp_enc_b) :
		Motor(gp_cw, gp_ccw, gp_enc_a, gp_enc_b){
	pidInit();

}

MotorAutoPid::~MotorAutoPid() {
	// TODO Auto-generated destructor stub
}


void MotorAutoPid::pidInit(){
	pPID = new AutoTunePID(0.0, 1.0, TuningMethod::LambdaTuning);
	pPID->setLambda(0.7); // Set lambda parameter for Lambda Tuning
	pPID->setOscillationMode(OscillationMode::Half); // Set oscillation mode to Half (default steps = 20)
	pPID->setOperationalMode(OperationalMode::Normal);
	pPID->setManualGains(
   			0.583223 - 0.1,
			0.910594,
			0.047390);
	pPID->enableOutputFilter(0.2); // Reduce PWM noise
	//pPID->enableInputFilter(0.8);
	pPID->enableAntiWindup(true);  // Handle load changes
}

void MotorAutoPid::setSpeedRadPS(float rps, bool cw){
	xTargetRadPS = rps;
	setClockwise(cw);

	pPID->setSetpoint(xTargetRadPS);
}

void MotorAutoPid::configPID(float kP, float kI, float kD){
	pPID->setManualGains(
	   			kP,
				kI,
				kD);
}

float MotorAutoPid::doPID(){

	pPID->update(getRADPS());
	float throttle = pPID->getOutput();
	setThrottle(throttle, isClockwise());
	return throttle;
}

void MotorAutoPid::getKPID(float &kp, float &ki, float &kd){
	kp = pPID->getKp();
	ki = pPID->getKi();
	kd = pPID->getKd();
}

float MotorAutoPid::getTargetSpeedRadPS(){
	return xTargetRadPS;
}


void MotorAutoPid::tunePID(){
	pPID->setOperationalMode(OperationalMode::Tune);
}

bool MotorAutoPid::tuneComplete(){
	return  (pPID->getOperationalMode() == OperationalMode::Normal);
}

