#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// EXAMPLE PIN CONFIGURATION
// This example uses GPIO pins 6-11 for a 3x3 matrix
// ============================================================================

#define MATRIX_ROWS 3
static const uint8_t row_pins[MATRIX_ROWS] = {
    6,  // Row 0 - GPIO 6
    7,  // Row 1 - GPIO 7
    8   // Row 2 - GPIO 8
};

#define MATRIX_COLS 3
static const uint8_t col_pins[MATRIX_COLS] = {
    9,   // Col 0 - GPIO 9
    10,  // Col 1 - GPIO 10
    11   // Col 2 - GPIO 11
};

// ============================================================================
// EXAMPLE KEYMAP - Numpad Layout (1-9)
// ============================================================================

static const uint8_t keymap[MATRIX_ROWS][MATRIX_COLS] = {
    {0x1E, 0x1F, 0x20},  // Row 0: 1, 2, 3
    {0x21, 0x22, 0x23},  // Row 1: 4, 5, 6
    {0x24, 0x25, 0x26}   // Row 2: 7, 8, 9
};

// ============================================================================
// HARDWARE CONFIGURATION
// ============================================================================

#define DEBOUNCE_MS 5
#define SCAN_INTERVAL_US 1000

#endif // CONFIG_H
