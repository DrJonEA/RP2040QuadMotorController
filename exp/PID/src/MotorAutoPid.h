/*
 * MotorAutoPid.h
 *
 *  Created on: 23 Dec 2025
 *      Author: jondurrant
 */

#ifndef EXP_PID_SRC_MOTORAUTOPID_H_
#define EXP_PID_SRC_MOTORAUTOPID_H_

#include "Motor.h"
#include "AutoTunePID.h"

#ifndef PID_FAULT_PER //Percentage error places drive into fault mode
#define PID_FAULT_PER 0.2
#endif

#ifndef PID_FAULT_TIME //Time to allow drive to achieve speed in ms
#define PID_FAULT_TIME 1000
#endif

class MotorAutoPid : public Motor {
public:
	MotorAutoPid();
	MotorAutoPid(uint8_t gp_cw,
			uint8_t gp_ccw,
			uint8_t gp_enc_a,
			uint8_t gp_enc_b);
	virtual ~MotorAutoPid();

	void setSpeedRadPS(float rps, bool cw);
	float getTargetSpeedRadPS();

	void configPID(float kP, float kI, float kD);

	float doPID();

	void getKPID(float &kp, float &ki, float &kd);

	void tunePID();
	bool tuneComplete();

	bool isFault();
	void reseFault();

protected:
	void setFault();

	float xTargetRadPS = 0.0;
	AutoTunePID *pPID;

	void pidInit();

	uint32_t xOkTimestamp = 0;
	bool xFault = false;
};

#endif /* EXP_PID_SRC_MOTORAUTOPID_H_ */
