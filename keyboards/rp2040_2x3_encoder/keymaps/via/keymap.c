#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_2x3(
        KC_1, KC_2, KC_3,
        KC_4, KC_5, KC_6
    ),
    [1] = LAYOUT_2x3(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_2x3(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_2x3(
        KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}

// Encoder button toggles RGB
void matrix_scan_user(void) {
#ifdef ENCODER_BTN_PIN
    static bool released = true;
    static uint16_t tmr = 0;

    if (timer_elapsed(tmr) >= 10) {
        bool pressed = (readPin(ENCODER_BTN_PIN) == 0);
        if (pressed && released) {
            tmr = timer_read();
            rgblight_toggle_noeeprom();
        }
        released = !pressed;
    }
#endif
}
