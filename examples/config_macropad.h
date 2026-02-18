#ifndef CONFIG_H
#define CONFIG_H

// ============================================================================
// EXAMPLE PIN CONFIGURATION
// This example uses GPIO pins 2-7 for a 3x3 matrix
// ============================================================================

#define MATRIX_ROWS 3
static const uint8_t row_pins[MATRIX_ROWS] = {
    2,  // Row 0 - GPIO 2
    3,  // Row 1 - GPIO 3
    4   // Row 2 - GPIO 4
};

#define MATRIX_COLS 3
static const uint8_t col_pins[MATRIX_COLS] = {
    5,  // Col 0 - GPIO 5
    6,  // Col 1 - GPIO 6
    7   // Col 2 - GPIO 7
};

// ============================================================================
// EXAMPLE KEYMAP - Macro Pad with Arrow Keys
// ============================================================================

static const uint8_t keymap[MATRIX_ROWS][MATRIX_COLS] = {
    {0x3A, 0x3B, 0x3C},  // Row 0: F1, F2, F3
    {0x50, 0x52, 0x4F},  // Row 1: Left Arrow, Up Arrow, Right Arrow
    {0x2C, 0x51, 0x28}   // Row 2: Space, Down Arrow, Enter
};

// ============================================================================
// HARDWARE CONFIGURATION
// ============================================================================

#define DEBOUNCE_MS 5
#define SCAN_INTERVAL_US 1000

#endif // CONFIG_H
