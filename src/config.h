#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// PIN CONFIGURATION - Fill in your actual GPIO pins here
// ============================================================================

// Matrix rows (GPIO pins connected to rows)
// Replace these with your actual row pins
#define MATRIX_ROWS 3
static const uint8_t row_pins[MATRIX_ROWS] = {
    0,  // Row 0 - TODO: Change to your actual GPIO pin
    1,  // Row 1 - TODO: Change to your actual GPIO pin
    2   // Row 2 - TODO: Change to your actual GPIO pin
};

// Matrix columns (GPIO pins connected to columns)
// Replace these with your actual column pins
#define MATRIX_COLS 3
static const uint8_t col_pins[MATRIX_COLS] = {
    3,  // Col 0 - TODO: Change to your actual GPIO pin
    4,  // Col 1 - TODO: Change to your actual GPIO pin
    5   // Col 2 - TODO: Change to your actual GPIO pin
};

// ============================================================================
// KEYMAP CONFIGURATION - Fill in your desired key layout here
// ============================================================================

// USB HID Keycodes (standard keyboard scancodes)
// Common keys:
// 0x04-0x1D: A-Z
// 0x1E-0x27: 1-0
// 0x28: Enter, 0x29: Escape, 0x2A: Backspace
// 0x2B: Tab, 0x2C: Space
// 0x4F-0x52: Arrow keys (Right, Left, Down, Up)
// Full list: https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf (page 53)

// Define your 3x3 keymap here
// Each row represents one row of keys
static const uint8_t keymap[MATRIX_ROWS][MATRIX_COLS] = {
    {0x1E, 0x1F, 0x20},  // Row 0: 1, 2, 3 - TODO: Change to your desired keys
    {0x21, 0x22, 0x23},  // Row 1: 4, 5, 6 - TODO: Change to your desired keys
    {0x24, 0x25, 0x26}   // Row 2: 7, 8, 9 - TODO: Change to your desired keys
};

// ============================================================================
// HARDWARE CONFIGURATION
// ============================================================================

// Debounce time in milliseconds
#define DEBOUNCE_MS 5

// Matrix scan interval in microseconds
#define SCAN_INTERVAL_US 1000

#endif // CONFIG_H
