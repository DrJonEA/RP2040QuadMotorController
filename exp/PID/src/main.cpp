/***
 * Demo
 * Jon Durrant
 * 9-Jan-2025
 */


#include "pico/stdlib.h"
#include "stdio.h"
#include "math.h"

extern "C"{
#include "pico/status_led.h"
}

#include "Motor.h"
#include "MotorPID.h"
#include "QuadController.h"

#include "AutoTunePID.h"
#include "MotorAutoPid.h"


int manual(){
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

 	bool rc = status_led_init();
    hard_assert(rc);
    colored_status_led_set_on_with_color(0xFF0000);

    Motor motor;
       motor.init(
   		MTR1_PWR_A,
   		MTR1_PWR_B,
   		MTR1_ENC_A,
   		MTR1_ENC_B
   		);

	float setpoint = M_PI;//*2;
	AutoTunePID pid(0.0, 1.0, TuningMethod::LambdaTuning);
	pid.setSetpoint(setpoint); // Set the desired setpoint
   	pid.setLambda(0.7); // Set lambda parameter for Lambda Tuning
   	pid.setOscillationMode(OscillationMode::Half); // Set oscillation mode to Half (default steps = 20)
   	pid.setOperationalMode(OperationalMode::Normal); // Start in Tune mode for auto-tuning
   	pid.setManualGains(
   			0.583223 - 0.1,
			0.910594,
			0.047390);
	pid.enableOutputFilter(0.2); // Reduce PWM noise
	pid.enableAntiWindup(true);  // Handle load changes

   	for (;;){
   		// Read the current input from the sensor
   		float currentInput = motor.getRADPS();

   		// Update the PID controller with the current input
   		pid.update(currentInput);

   		// Get the computed output from the PID controller
   		float output = pid.getOutput();

   		// Apply the output to the actuator (e.g., PWM signal to a motor or heater)
   		motor.setThrottle(output);

   		// Print debugging information to the serial monitor
   		printf("Input: %.2f Output: %.2f Kp: %f Ki: %f Kd: %f Mode: ",
   				currentInput,
   				output,
   				pid.getKp(),
   				pid.getKi(),
   				pid.getKd()
   				);

   		// Print the current operational mode
   		switch (pid.getOperationalMode()) {
   		case OperationalMode::Normal:
   			printf("Normal\n");
   			break;
   		case OperationalMode::Reverse:
   			printf("Reverse\n");
   			break;
   		case OperationalMode::Hold:
   			printf("Hold\n");
   			break;
   		case OperationalMode::Preserve:
   			printf("Preserve\n");
   			break;
   		case OperationalMode::Tune:
   			printf("Tune\n");
   			break;
   		case OperationalMode::Auto:
   			printf("Auto\n");
   			break;
   		}

   		// Small delay to maintain a consistent sample time
   		sleep_ms(50);
   	}
}

/***
 * Main
 * @return
 */
int autoPid( void ){
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

 	bool rc = status_led_init();
    hard_assert(rc);
    colored_status_led_set_on_with_color(0x0000FF);

    Motor motor;
    motor.init(
		MTR4_PWR_A,
		MTR4_PWR_B,
		MTR4_ENC_A,
		MTR4_ENC_B
		);

    float setpoint = M_PI;//*4;
    AutoTunePID pid(0.0, 1.0, TuningMethod::LambdaTuning);
    pid.setSetpoint(setpoint); // Set the desired setpoint
	pid.setLambda(0.7); // Set lambda parameter for Lambda Tuning
	pid.setOscillationMode(OscillationMode::Half); // Set oscillation mode to Half (default steps = 20)
	pid.setOperationalMode(OperationalMode::Tune); // Start in Tune mode for auto-tuning
	pid.enableOutputFilter(0.2); // Reduce PWM noise
	pid.enableAntiWindup(true);  // Handle load changes

	for (;;){
		// Read the current input from the sensor
		float currentInput = motor.getRADPS();

		// Update the PID controller with the current input
		pid.update(currentInput);

		// Get the computed output from the PID controller
		float output = pid.getOutput();

		// Apply the output to the actuator (e.g., PWM signal to a motor or heater)
		motor.setThrottle(output);

		// Print debugging information to the serial monitor
		printf("Input: %.2f Output: %.2f Kp: %f Ki: %f Kd: %f Mode: ",
				currentInput,
				output,
				pid.getKp(),
				pid.getKi(),
				pid.getKd()
				);

		// Print the current operational mode
		switch (pid.getOperationalMode()) {
		case OperationalMode::Normal:
			printf("Normal\n");
			break;
		case OperationalMode::Reverse:
			printf("Reverse\n");
			break;
		case OperationalMode::Hold:
			printf("Hold\n");
			break;
		case OperationalMode::Preserve:
			printf("Preserve\n");
			break;
		case OperationalMode::Tune:
			printf("Tune\n");
			break;
		case OperationalMode::Auto:
			printf("Auto\n");
			break;
		}

		// Small delay to maintain a consistent sample time
		sleep_ms(100);
	}

}



/***
 * Main
 * @return
 */
int Oldmain( void ){
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

 	bool rc = status_led_init();
    hard_assert(rc);
    colored_status_led_set_on_with_color(0x00FF00);


    MotorPID motors[4];

    motors[0].init(
    		MTR1_PWR_A,
			MTR1_PWR_B,
			MTR1_ENC_A,
			MTR1_ENC_B
			);
    motors[1].init(
    		MTR2_PWR_A,
			MTR2_PWR_B,
			MTR2_ENC_A,
			MTR2_ENC_B
			);
    motors[2].init(
    		MTR3_PWR_A,
			MTR3_PWR_B,
			MTR3_ENC_A,
			MTR3_ENC_B
			);
    motors[3].init(
    		MTR4_PWR_A,
			MTR4_PWR_B,
			MTR4_ENC_A,
			MTR4_ENC_B
			);

    motors[0].configPID(0.01, 0.0, 0.0);
    float target = M_PI;//*2;
    motors[0].setSpeedRadPS(target,  true);
    //motors[0].throttle16(35000);
    float p, i, d, pid;
    printf("%s, %s, %s, %s, %s, %s\n",
    		"rps",
			"target",
			"pid",
			"p", "i", "d"
    		);
    for (;;){
    	pid = motors[0].doPID(&p, &i, &d);
    	printf("%f, %f, %f, %f, %f, %f\n",
    			motors[0].getRADPS(),
    			target,
    			pid,
    			p, i, d
				);
    	sleep_ms(250);
    }

	for (;;){
		for (int i=0xFFFF; i > 15000; i-=5000){
			printf("Setting to %d\n", i);
			for (int m=0; m < 4; m++){
				motors[m].throttle16(i);
			}
			colored_status_led_set_state(false);
			sleep_us(200);
			colored_status_led_set_on_with_color(i);
			for (int i=0; i < 10; i++){
				for (int m=0; m < 4; m++){
					printf("%d Count %u, %.2f\n", m, motors[m].getCWCount(), motors[m].getRADPS());
				}
				sleep_ms(100);
			}
		}
		for (int i=0xFFFF; i > 15000; i-=5000){
			printf("Setting to %d\n", i);
			for (int m=0; m < 4; m++){
				motors[m].throttle16(i, false);
			}
			colored_status_led_set_state(false);
			sleep_us(200);
			colored_status_led_set_on_with_color(i);
			for (int i=0; i < 10; i++){
				for (int m=0; m < 4; m++){
					printf("%d Count %u, %.2f\n", m, motors[m].getCWCount(), motors[m].getRADPS());
				}
				sleep_ms(100);
			}
		}
	}


    return 0;
}

void autoMotor(MotorAutoPid &motor){


	float setpoint = M_PI*4;
	motor.setSpeedRadPS(setpoint, false);
	motor.tunePID();
	float kp, ki, kd;
	for (;;){
		float pid = motor.doPID();
		/*
		printf("%.2f %.2f, %.2f, pid = %.2f\n",
				motor.getRADPS()/setpoint,
				setpoint,
				motor.getRADPS(),
				pid);
		*/
		if (motor.tuneComplete()){
			motor.getKPID(kp, ki, kd);
			printf("PID(%f, %f, %f)\n", kp, ki, kd);
			return;
		}
		sleep_ms(100);
	}

}




int main(){
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

 	bool rc = status_led_init();
    hard_assert(rc);
    colored_status_led_set_on_with_color(0x00FF00);

	//autoPid();


	MotorAutoPid motors[4];

	    motors[0].init(
	    		MTR1_PWR_A,
				MTR1_PWR_B,
				MTR1_ENC_A,
				MTR1_ENC_B
				);
	    motors[1].init(
	    		MTR2_PWR_A,
				MTR2_PWR_B,
				MTR2_ENC_A,
				MTR2_ENC_B
				);
	    motors[2].init(
	    		MTR3_PWR_A,
				MTR3_PWR_B,
				MTR3_ENC_A,
				MTR3_ENC_B
				);
	    motors[3].init(
	    		MTR4_PWR_A,
				MTR4_PWR_B,
				MTR4_ENC_A,
				MTR4_ENC_B
				);

	    for (int i=0; i < 4; i++){
	    	autoMotor(motors[i]);
	    	motors[i].setThrottle(0, true);
	    }

	    for (int i=0; i < 4; i++){
	    	if (i/2 == 0){
	    		motors[i].setSpeedRadPS(M_PI*4, true);
	    	} else {
	    		motors[i].setSpeedRadPS(M_PI*4, true);
	    	}
	    	float kp, ki, kd;
	    	motors[i].getKPID(kp, ki, kd);
			printf("Motor %d PID(%f, %f, %f)\n",i, kp, ki, kd);
	    }
	    for (;;){
		    for (int i=0; i < 4; i++){
		    	motors[i].doPID();
		    	printf("%d: %.2f == %.2f ",
		    			i,
						motors[i].getTargetSpeedRadPS(),
						motors[i].getRADPS());
		    	if (motors[i].isFault()){
		    		printf("FAULT\n");
		    	} else {
		    		printf("OK\n");
		    	}
		    }
		    sleep_ms(100);
	    }

}
