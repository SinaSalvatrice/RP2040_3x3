# Quick Start Guide

This guide will help you configure and build your RP2040 3x3 keyboard firmware.

## Step 1: Configure Your Hardware

Edit `src/config.h`:

### Configure Pin Mapping

1. Identify which GPIO pins on your RP2040 are connected to your keyboard matrix rows and columns
2. Update the `row_pins` and `col_pins` arrays with your actual pin numbers

Example:
```c
static const uint8_t row_pins[MATRIX_ROWS] = {
    6,   // Row 0 connected to GPIO 6
    7,   // Row 1 connected to GPIO 7
    8    // Row 2 connected to GPIO 8
};

static const uint8_t col_pins[MATRIX_COLS] = {
    9,   // Col 0 connected to GPIO 9
    10,  // Col 1 connected to GPIO 10
    11   // Col 2 connected to GPIO 11
};
```

### Configure Your Keymap

Decide what you want each key to do and update the `keymap` array using USB HID keycodes.

Example for a numpad layout:
```c
static const uint8_t keymap[MATRIX_ROWS][MATRIX_COLS] = {
    {0x1E, 0x1F, 0x20},  // 1, 2, 3
    {0x21, 0x22, 0x23},  // 4, 5, 6
    {0x24, 0x25, 0x26}   // 7, 8, 9
};
```

Example for media keys:
```c
// Note: Media keys require consumer control HID report (not yet implemented)
// Use standard keys for now
```

### Common USB HID Keycodes

| Key | Hex Code | Dec Code |
|-----|----------|----------|
| A-Z | 0x04-0x1D | 4-29 |
| 1-9 | 0x1E-0x26 | 30-38 |
| 0 | 0x27 | 39 |
| Enter | 0x28 | 40 |
| Escape | 0x29 | 41 |
| Backspace | 0x2A | 42 |
| Tab | 0x2B | 43 |
| Space | 0x2C | 44 |
| F1-F12 | 0x3A-0x45 | 58-69 |
| Right Arrow | 0x4F | 79 |
| Left Arrow | 0x50 | 80 |
| Down Arrow | 0x51 | 81 |
| Up Arrow | 0x52 | 82 |

For a complete list, see: https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf (page 53)

## Step 2: Build the Firmware

### Install Prerequisites

Ubuntu/Debian:
```bash
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi build-essential
```

macOS:
```bash
brew install cmake
brew install --cask gcc-arm-embedded
```

### Get the Pico SDK

```bash
cd ~
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=~/pico-sdk
```

Add to your `~/.bashrc` or `~/.zshrc`:
```bash
export PICO_SDK_PATH=~/pico-sdk
```

### Build

```bash
cd /path/to/RP2040_3x3
mkdir build
cd build
cmake ..
make -j4
```

The firmware file will be created at: `build/rp2040_3x3.uf2`

## Step 3: Flash the Firmware

1. Disconnect your RP2040 board from USB
2. Hold down the BOOTSEL button on the board
3. While holding BOOTSEL, connect the board to your computer via USB
4. Release the BOOTSEL button
5. The board will appear as a USB drive named "RPI-RP2"
6. Drag and drop `rp2040_3x3.uf2` onto the drive
7. The board will automatically reboot and your keyboard is ready!

## Troubleshooting

### Build fails with "PICO_SDK_PATH not found"
Make sure you've set the `PICO_SDK_PATH` environment variable and initialized the SDK submodules.

### Keys don't work or behave strangely
- Check your pin configuration in `src/config.h`
- Verify your wiring matches the pin configuration
- Try adjusting the `DEBOUNCE_MS` value if keys register multiple times

### Board not recognized as keyboard
- Make sure the firmware flashed successfully (the drive should disappear after flashing)
- Try a different USB cable or port
- Check that you're using a data cable, not just a charging cable

### Need to reflash
Simply repeat Step 3 with the new `.uf2` file. You can enter BOOTSEL mode by:
- Holding BOOTSEL while plugging in, OR
- Double-tapping the reset button (if your board has one)

## Next Steps

- Customize the USB device information in `src/usb_descriptors.c`
- Adjust debounce and scan timing in `src/config.h` for your switches
- Add additional features like layers or macros (requires code modifications)
