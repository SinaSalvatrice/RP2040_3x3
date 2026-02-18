#include "quantum.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#include "color.h"
#endif

/* ---------------------------
   Palette: Turquoise + Yellow (HSV 0..255)
   --------------------------- */
#define H_TURQ 128
#define H_YELL  43
#define SAT     255

static uint8_t dot_pos = 0;  // encoder-controlled “wander light” position

static inline RGB rgb_blend(RGB a, RGB b, uint8_t t) {
    RGB o;
    o.r = lerp8by8(a.r, b.r, t);
    o.g = lerp8by8(a.g, b.g, t);
    o.b = lerp8by8(a.b, b.b, t);
    return o;
}

/* Base effect: 2-color breathing (Turquoise <-> Yellow) + encoder-driven wander dot */
static void render_lights(void) {
    if (!rgblight_is_enabled()) return;

    const uint8_t n = RGBLIGHT_LED_COUNT;
    if (n == 0) return;

    // slower breathing: increase shift (>>4 = slower, >>5 = slower)
    uint8_t phase = (uint8_t)(timer_read() >> 5);
    uint8_t t     = sin8(phase);              // 0..255
    uint8_t br    = 60 + scale8(t, 140);      // calmer: brightness 60..200

    RGB turq = hsv_to_rgb((HSV){ .h = H_TURQ, .s = SAT, .v = 255 });
    RGB yell = hsv_to_rgb((HSV){ .h = H_YELL, .s = SAT, .v = 255 });
    RGB base = rgb_blend(turq, yell, t);

    base.r = scale8(base.r, br);
    base.g = scale8(base.g, br);
    base.b = scale8(base.b, br);

    for (uint8_t i = 0; i < n; i++) {
        rgblight_setrgb_at(base.r, base.g, base.b, i);
    }

    // Wanderlicht: head turq, tail yellow
    uint8_t head = dot_pos % n;
    uint8_t tail = (head == 0) ? (n - 1) : (head - 1);

    rgblight_sethsv_at(H_YELL, SAT, 140, tail);
    rgblight_sethsv_at(H_TURQ, SAT, 255, head);

    rgblight_set();
}

/* ---------------------------
   Encoder: wheel + wander-dot step
   --------------------------- */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index != 0 || RGBLIGHT_LED_COUNT == 0) return true;

    if (clockwise) {
        dot_pos = (dot_pos + 1) % RGBLIGHT_LED_COUNT;
        tap_code(KC_WFWD);   // swap UP/DOWN if direction feels wrong
    } else {
        dot_pos = (dot_pos + RGBLIGHT_LED_COUNT - 1) % RGBLIGHT_LED_COUNT;
        tap_code(KC_WHOM);
    }

    render_lights();
    return true;
}

/* ---------------------------
   Encoder button (NOT in matrix): debounce + RGB toggle
   --------------------------- */
static bool     enc_btn_last   = true;   // pullup: HIGH = unpressed
static bool     enc_btn_stable = true;
static uint16_t enc_btn_timer  = 0;

/* ---------------------------
   Keymap
   Notes:
   - You had keypad dot/enter/plus/minus issues. For “always works” on Android/DE layout:
     use normal keys: KC_DOT / KC_ENT / KC_PLUS / KC_MINS.
   - If you later want “true keypad” for Windows: we can add a second layer with KC_KP_*.
   --------------------------- */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_NO,      KC_NO,   KC_NO,   KC_BSPC,
        KC_NUM,     KC_ASTR, KC_SLSH, KC_MINS,
        KC_7,       KC_8,    KC_9,    KC_PLUS,
        KC_4,       KC_5,    KC_6,    KC_ENT,
        KC_1,       KC_2,    KC_3,    KC_ENT,
        KC_0,       KC_0,    KC_DOT,  KC_DOT
    )
};

/* ---------------------------
   Startup: one colorful wander pulse, then switch to our renderer
   --------------------------- */
void keyboard_post_init_user(void) {
    setPinInputHigh(ENCODER_BTN_PIN);

    rgblight_toggle_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);

    // Startup pulse (once)
    for (uint8_t i = 0; i < RGBLIGHT_LED_COUNT; i++) {
        uint8_t hue = (uint8_t)((uint16_t)i * 150 / (RGBLIGHT_LED_COUNT ? RGBLIGHT_LED_COUNT : 1));
        rgblight_sethsv_at(hue, 255, 180, i);
        rgblight_set();
        wait_ms(35);
    }
    wait_ms(60);

    render_lights();
}

void matrix_scan_user(void) {
    // Debounce encoder button (active LOW)
    bool raw = readPin(ENCODER_BTN_PIN);

    if (raw != enc_btn_stable) {
        enc_btn_stable = raw;
        enc_btn_timer  = timer_read();
    }

    if (timer_elapsed(enc_btn_timer) > 25) {
        if (enc_btn_stable != enc_btn_last) {
            enc_btn_last = enc_btn_stable;

            if (!enc_btn_last) { // pressed
                rgblight_toggle_noeeprom();   // ON/OFF toggle (fix)
            }
        }
    }

    // Update breathing regularly (no internal RGB modes active)
    static uint16_t last = 0;
    if (timer_elapsed(last) > 35) {  // slower refresh is enough for breathing
        last = timer_read();
        render_lights();
    }
}