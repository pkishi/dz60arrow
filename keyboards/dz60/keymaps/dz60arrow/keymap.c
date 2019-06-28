#include "keymap.h"

#define BASE_COLOR 20, 255, 255
#define MODIFIER_COLOR 255, 255, 255

static bool RUNFLAG = true;
static uint16_t RUNDELAY;

bool process_record_user(uint16_t keycode, keyrecord_t *record){
	switch (keycode){
		case _01_MACRO:
				tap_code16(C(X_F7));
			break;
	}
	return true;
};

uint32_t layer_state_set_user(uint32_t state){
	switch (biton32(state)){
		case _02_MODIFIER:
			rgblight_sethsv_noeeprom(MODIFIER_COLOR); //#FC4E36
			break;
		case _01_BASE:
			rgblight_sethsv_noeeprom(BASE_COLOR); //#A02C35
			break;

	}
	return state;
}

void matrix_init_user(void){
	PreInitRGB();
}

void matrix_scan_user(void){
	InitRGB();
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_01_BASE] = LAYOUT_dz60arrow(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_TRNS, KC_BSPC, 
		KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, 
		KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT, 
		KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT, KC_UP, KC_SLSH, 
		KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, _01_MACRO, TT(1), KC_LEFT, KC_DOWN, KC_RGHT),

	[_02_MODIFIER] = LAYOUT_dz60arrow(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, KC_DEL, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

void PreInitRGB(void){
	RUNDELAY = timer_read();
}

void InitRGB(void){
	if (RUNFLAG && timer_elapsed(RUNDELAY) > INIT_DELAY){
		RUNFLAG = false;

		rgblight_sethsv_noeeprom(BASE_COLOR);
		rgblight_mode_noeeprom(1);
		rgblight_enable_noeeprom();
	}
}