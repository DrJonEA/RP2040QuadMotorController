/***
 * Demo
 * Jon Durrant
 * 9-Jan-2025
 */


#include "pico/stdlib.h"
#include "stdio.h"

extern "C"{
#include "pico/status_led.h"
}

#include "Motor.h"
#include "QuadController.h"



/***
 * Main
 * @return
 */
int main( void )
{
	//Setup serial over USB and give a few seconds to settle before we start
    stdio_init_all();
    sleep_ms(2000);
    printf("GO\n");

 	bool rc = status_led_init();
    hard_assert(rc);
    colored_status_led_set_on_with_color(0x00FF00);


    Motor motors[4];

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

    motors[0].throttle16(35000);
    for (;;){
    	printf("%.2f RadsPS\n", motors[0].getRADPS());
    	sleep_ms(1000);
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
