# Wiring Guide

This guide explains how to wire your 3x3 keyboard matrix to the RP2040.

## Understanding the Matrix

A keyboard matrix reduces the number of GPIO pins needed. Instead of needing 9 pins for 9 keys, you only need 6 pins (3 rows + 3 columns).

### How it Works

```
        COL0    COL1    COL2
         |       |       |
ROW0 ----+-------+-------+----  Key(0,0)  Key(0,1)  Key(0,2)
         |       |       |
ROW1 ----+-------+-------+----  Key(1,0)  Key(1,1)  Key(1,2)
         |       |       |
ROW2 ----+-------+-------+----  Key(2,0)  Key(2,1)  Key(2,2)
```

When a key is pressed, it connects its row and column together. The firmware scans each row one at a time and reads the column states to detect which keys are pressed.

## Matrix Wiring

### Components Needed
- RP2040 board (e.g., Raspberry Pi Pico)
- 9 mechanical keyboard switches
- Diodes (1N4148 recommended) - one per switch
- Wire (26-30 AWG recommended)

### Diode Orientation

**IMPORTANT**: Each switch must have a diode to prevent ghosting. Connect the diode with the cathode (marked with a line) pointing towards the column.

```
Key Switch:  [Switch] ──┤>├── Column
                 |
                Row
```

### Example Wiring with GPIO 6-11

```
Rows:
- GPIO 6 → Row 0 (Top row)
- GPIO 7 → Row 1 (Middle row)
- GPIO 8 → Row 2 (Bottom row)

Columns:
- GPIO 9  → Column 0 (Left column)
- GPIO 10 → Column 1 (Middle column)
- GPIO 11 → Column 2 (Right column)
```

### Physical Layout

```
┌─────┐  ┌─────┐  ┌─────┐
│  1  │  │  2  │  │  3  │    Row 0 (GPIO 6)
└─────┘  └─────┘  └─────┘
┌─────┐  ┌─────┐  ┌─────┐
│  4  │  │  5  │  │  6  │    Row 1 (GPIO 7)
└─────┘  └─────┘  └─────┘
┌─────┐  ┌─────┐  ┌─────┐
│  7  │  │  8  │  │  9  │    Row 2 (GPIO 8)
└─────┘  └─────┘  └─────┘
 Col 0    Col 1    Col 2
(GPIO 9) (GPIO 10)(GPIO 11)
```

## Step-by-Step Wiring

1. **Prepare the switches**: Solder a diode to each switch
   - Cathode (marked end) towards the column pin
   - Anode to the switch pin

2. **Wire the rows**: Connect all switches in each row together
   - Top row (keys 1, 2, 3) → GPIO 6
   - Middle row (keys 4, 5, 6) → GPIO 7
   - Bottom row (keys 7, 8, 9) → GPIO 8

3. **Wire the columns**: Connect the diode cathodes in each column
   - Left column (keys 1, 4, 7) → GPIO 9
   - Middle column (keys 2, 5, 8) → GPIO 10
   - Right column (keys 3, 6, 9) → GPIO 11

4. **Connect ground**: Connect the RP2040 GND pin to ground

5. **Connect power**: Connect the RP2040 USB port for power and data

## Testing

After wiring:

1. Double-check all connections
2. Verify diode orientation (cathode towards columns)
3. Flash the firmware (see QUICKSTART.md)
4. Open a text editor and test each key

## Common Issues

### All keys in a row/column don't work
- Check the row/column wire connection to the GPIO pin
- Verify the GPIO pin number in `src/config.h`

### Multiple keys register for one press (ghosting)
- Check diode installation and orientation
- Ensure every switch has a diode
- Diode cathode must point towards the column

### Some keys don't register
- Check switch soldering
- Verify diode connections
- Test the switch with a multimeter

### Keys register multiple times
- Increase `DEBOUNCE_MS` in `src/config.h` (try 10-20ms)
- Check for loose connections

## Alternative Wiring Schemes

You can use any GPIO pins you want! Just update `src/config.h`:

### Compact Layout (GPIO 0-5)
```c
static const uint8_t row_pins[MATRIX_ROWS] = {0, 1, 2};
static const uint8_t col_pins[MATRIX_COLS] = {3, 4, 5};
```

### Spread Out Layout (GPIO 10-15)
```c
static const uint8_t row_pins[MATRIX_ROWS] = {10, 11, 12};
static const uint8_t col_pins[MATRIX_COLS] = {13, 14, 15};
```

Just avoid:
- GPIO 23-25 (used for Pico's onboard systems)
- Any pins you need for other purposes (LEDs, etc.)

## Pro Tips

- Use different colored wires for rows and columns (easier debugging)
- Label your wires with tape or heat shrink
- Test each connection with a multimeter before final assembly
- Keep wires organized and strain-relieved
- Consider using a PCB for a cleaner build
