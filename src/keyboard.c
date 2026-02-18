#include "keyboard.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "usb_hid.h"
#include <string.h>

// Key state tracking
static bool key_state[MATRIX_ROWS][MATRIX_COLS] = {0};
static uint32_t last_change_time[MATRIX_ROWS][MATRIX_COLS] = {0};

void keyboard_init(void) {
    // Initialize row pins as outputs (set low initially)
    for (int i = 0; i < MATRIX_ROWS; i++) {
        gpio_init(row_pins[i]);
        gpio_set_dir(row_pins[i], GPIO_OUT);
        gpio_put(row_pins[i], 0);
    }
    
    // Initialize column pins as inputs with pull-up resistors
    for (int i = 0; i < MATRIX_COLS; i++) {
        gpio_init(col_pins[i]);
        gpio_set_dir(col_pins[i], GPIO_IN);
        gpio_pull_up(col_pins[i]);
    }
}

void keyboard_task(void) {
    uint8_t pressed_keys[6] = {0};  // HID supports up to 6 simultaneous keys
    uint8_t key_count = 0;
    bool state_changed = false;
    
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    // Scan each row
    for (int row = 0; row < MATRIX_ROWS; row++) {
        // Activate this row (set high)
        gpio_put(row_pins[row], 1);
        
        // Small delay to let the signal stabilize
        sleep_us(1);
        
        // Read all columns
        for (int col = 0; col < MATRIX_COLS; col++) {
            // Read column (active low due to pull-up)
            // If key is pressed, the column will read as high (connected to the active row)
            bool pressed = gpio_get(col_pins[col]);
            
            // Debouncing: only update state if enough time has passed
            if (now - last_change_time[row][col] > DEBOUNCE_MS) {
                if (pressed != key_state[row][col]) {
                    key_state[row][col] = pressed;
                    last_change_time[row][col] = now;
                    state_changed = true;
                }
            }
            
            // Build list of pressed keys for HID report
            if (key_state[row][col] && key_count < 6) {
                pressed_keys[key_count++] = keymap[row][col];
            }
        }
        
        // Deactivate this row (set low)
        gpio_put(row_pins[row], 0);
    }
    
    // Send HID report whenever state changes
    // This includes key presses, releases, and transitions to no keys pressed
    if (state_changed) {
        usb_hid_send_report(pressed_keys, key_count);
    }
}

uint16_t keyboard_get_state(void) {
    uint16_t state = 0;
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            if (key_state[row][col]) {
                state |= (1 << (row * MATRIX_COLS + col));
            }
        }
    }
    return state;
}
