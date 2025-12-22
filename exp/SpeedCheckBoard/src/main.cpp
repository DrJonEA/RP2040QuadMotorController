/**
 * Jon Durrant.
 *
 * Pico Hall Effect Sensor Test
 */

#include "pico/stdlib.h"
#include <stdio.h>

#include "hardware/clocks.h"
extern "C"{
#include "LCD_0in96.h"
#include "lv_port_disp.h"
}

#include "Widgets.h"
#include <math.h>

#define DELAY 500 // in microseconds
#define LED_PAD  15
#define HALL_PAD 14

extern LCD_SetWindowsFunc LCD_SetWindows;
extern uint16_t DISP_HOR_RES;
extern uint16_t DISP_VER_RES;

Widgets widgets;


uint32_t last = 0;
float avgRPM = 0.0;

void gpioIrqCallback(uint gpio, uint32_t event_mask){
	if ((event_mask & GPIO_IRQ_EDGE_FALL)> 0){
		gpio_put(LED_PAD, 1);
	}

	if ((event_mask & GPIO_IRQ_EDGE_RISE)> 0){
		gpio_put(LED_PAD, 0);

		uint32_t now = to_ms_since_boot (get_absolute_time());
		uint32_t ms = now - last;
		if (ms < 100){
			return;
		}
		widgets.setMS(ms);
		last = now;
		float rpm = (60000.0 / (float)ms );
		avgRPM = (rpm + avgRPM )/2.0;
		widgets.setRPM(avgRPM);
		float radps = avgRPM * (M_PI * 2.0) / 60.0;
		widgets.setRADPS(radps);
	}
}


int main() {
	stdio_init_all();

    gpio_init(LED_PAD);
    gpio_set_dir(LED_PAD, GPIO_OUT);
    gpio_put(LED_PAD, 1);
    sleep_ms(DELAY);
    gpio_put(LED_PAD, 0);

    gpio_init(HALL_PAD);
    gpio_set_dir(HALL_PAD, GPIO_IN);
    gpio_set_irq_enabled_with_callback(HALL_PAD,
    		GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,
			true,
			gpioIrqCallback
    );


    if(DEV_Module_Init()!=0){
        return -1;
    }
    /*LCD Init*/
	printf("0.96inch LCD LVGL demo...\r\n");
	LCD_0IN96_Init(HORIZONTAL);
	LCD_0IN96_Clear(WHITE);

	/*Config parameters*/
	LCD_SetWindows = LCD_0IN96_SetWindows;
	DISP_HOR_RES = LCD_0IN96_WIDTH;
	DISP_VER_RES = LCD_0IN96_HEIGHT;

	/*Init LVGL data structure*/
	lvgl_data_struct *dat = (lvgl_data_struct *)malloc(sizeof(lvgl_data_struct));
	memset(dat->scr, 0, sizeof(dat->scr));
	dat->click_num = 0;

	/*Init LVGL*/
	LVGL_Init();



    printf("Pre Widgets\n");
    widgets.init();
    for(;;){
    	 lv_task_handler();
    	 DEV_Delay_ms(5);
    }

}
