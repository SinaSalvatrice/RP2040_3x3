#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "config.h"

// Initialize the keyboard matrix
void keyboard_init(void);

// Scan the keyboard matrix and update state
void keyboard_task(void);

// Get the current state of all keys
// Returns a bitmask where each bit represents a key (row * MATRIX_COLS + col)
uint16_t keyboard_get_state(void);

#endif // KEYBOARD_H
