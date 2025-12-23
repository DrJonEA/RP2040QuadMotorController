/*
 * QuatController.h
 *
 *  Created on: 18 Dec 2025
 *      Author: jondurrant
 */

#ifndef EXP_SRC_QUATCONTROLLER_H_
#define EXP_SRC_QUATCONTROLLER_H_

#define UART0_TX 28
#define UART0_RX 29

#define SCL1 27
#define SDA1 26

//PWM Channels
#define PWM0A 0
#define PWM0B 1
#define PWM1A 2
#define PWM1B 3
#define PWM2A 4
#define PWM2B 5
#define PWM3A 6
#define PWM3B 7
#define PWM4A 8
#define PWM4B 9

#define PWM5A 10
#define PWM5B 11
#define PWM6A 12
#define PWM6B 13
#define PWM7A 14
#define PWM7B 15

//Motor Enconders
#define MTR1_ENC_A PWM1B
#define MTR1_ENC_B PWM0B
#define MTR2_ENC_A PWM2B
#define MTR2_ENC_B PWM3B
#define MTR3_ENC_A PWM5B
#define MTR3_ENC_B PWM4B
#define MTR4_ENC_A PWM6B
#define MTR4_ENC_B PWM7B

//Motor Power
#define MTR1_PWR_A PWM0A
#define MTR1_PWR_B PWM1A
#define MTR2_PWR_A PWM3A
#define MTR2_PWR_B PWM2A
#define MTR3_PWR_A PWM4A
#define MTR3_PWR_B PWM5A
#define MTR4_PWR_A PWM7A
#define MTR4_PWR_B PWM6A



#endif /* EXP_SRC_QUATCONTROLLER_H_ */
