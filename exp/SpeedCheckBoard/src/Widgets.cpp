/*
 * Widgets.cpp
 *
 *  Created on: 4 Aug 2025
 *      Author: jondurrant
 */

#include "Widgets.h"
#include <cstdio>



Widgets::Widgets() {

}

Widgets::~Widgets() {
	// TODO Auto-generated destructor stub
}



void Widgets::init() {

	 /*Create tileview*/
	xTV = lv_tileview_create(lv_scr_act());
	lv_obj_set_scrollbar_mode(xTV,  LV_SCROLLBAR_MODE_OFF);

	initTile1();

}

void Widgets::setRADPS(float radps){
	xRadPS = radps;
	char s[10];
	sprintf(s, "%0.2f RPS", radps);
	lv_label_set_text(pRPSLbl, s);
}

void Widgets::setRPM(float rpm){
	char s[10];
	sprintf(s, "%0.2f RPM", rpm);
	lv_label_set_text(pRPMLbl, s);
}

void Widgets::setMS(uint ms){
	char s[10];
	sprintf(s, "%u ms", ms);
	lv_label_set_text(pMSLbl, s);
}

void Widgets::initTile1() {

	/*Tile1: */
	xTile1 = lv_tileview_add_tile(xTV, 0, 0,  LV_DIR_ALL);


	lv_style_init(&xStyleTile);
	lv_style_set_bg_color(&xStyleTile, lv_color_hex(0x000000));
	lv_style_set_bg_opa(&xStyleTile, LV_OPA_COVER);
	//lv_obj_add_style(xTile1, &xStyleTile, 0);

	lv_style_init(&xLabelSt);
	lv_style_set_text_font(&xLabelSt, &lv_font_montserrat_16);
	lv_style_set_text_color(
			&xLabelSt,
			lv_color_make(0, 0x40, 0x40));

	uint hor = lv_disp_get_hor_res(NULL);
	uint ver = lv_disp_get_ver_res(NULL);


	pRPSLbl = lv_label_create(xTile1);
	lv_label_set_long_mode(pRPSLbl, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_text(pRPSLbl, "0.0 RPS");
	lv_obj_set_width(pRPSLbl, hor/2);  /*Set smaller width to make the lines wrap*/
	lv_obj_set_style_text_align(pRPSLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pRPSLbl, LV_ALIGN_LEFT_MID,  0,0);
	lv_obj_add_style(pRPSLbl , &xLabelSt,  LV_PART_MAIN);

	pRPMLbl = lv_label_create(xTile1);
	lv_label_set_long_mode(pRPMLbl, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_text(pRPMLbl, "0.0 RPM");
	lv_obj_set_width(pRPMLbl, hor/2);  /*Set smaller width to make the lines wrap*/
	lv_obj_set_style_text_align(pRPMLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pRPMLbl, LV_ALIGN_RIGHT_MID,  0,0);
	lv_obj_add_style(pRPMLbl , &xLabelSt,  LV_PART_MAIN);

	pMSLbl = lv_label_create(xTile1);
	lv_label_set_long_mode(pMSLbl, LV_LABEL_LONG_WRAP);     /*Break the long lines*/
	lv_label_set_text(pMSLbl, "0 ms");
	lv_obj_set_width(pMSLbl, hor/2);  /*Set smaller width to make the lines wrap*/
	lv_obj_set_style_text_align(pMSLbl, LV_TEXT_ALIGN_LEFT, 0);
	lv_obj_align(pMSLbl, LV_ALIGN_TOP_LEFT,  0,0);
	lv_obj_add_style(pMSLbl , &xLabelSt,  LV_PART_MAIN);

	//pTimer = lv_timer_create(timerCB, 100,  this);
}



void Widgets::timerCB(lv_timer_t * timer){
	Widgets *self = (Widgets *)timer->user_data;
	self->timerHandler(timer);
}

void Widgets::timerHandler(lv_timer_t * timer){
}

