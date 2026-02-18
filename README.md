# RP2040_3x3

An RP2040-based 3x3 keyboard with 9 low-profile silent switches (purple) and clear caps.

## Features

- 3x3 key matrix (9 keys total)
- USB HID keyboard interface
- Configurable pin mapping
- Configurable keymap
- Debouncing support
- Based on Raspberry Pi Pico SDK

## Hardware Configuration

Before building, you need to configure your hardware settings in `src/config.h`:

1. **Pin Configuration**: Update the `row_pins` and `col_pins` arrays with your actual GPIO pin numbers
2. **Keymap**: Modify the `keymap` array to define what each key does (using USB HID keycodes)

## Building the Firmware

### Prerequisites

1. Install the Raspberry Pi Pico SDK:
   ```bash
   git clone https://github.com/raspberrypi/pico-sdk.git
   cd pico-sdk
   git submodule update --init
   export PICO_SDK_PATH=/path/to/pico-sdk
   ```

2. Install required tools:
   - CMake (version 3.13 or higher)
   - ARM GCC cross-compiler (`gcc-arm-none-eabi`)
   - Build tools (`build-essential` on Ubuntu/Debian)

### Build Instructions

1. Create a build directory:
   ```bash
   mkdir build
   cd build
   ```

2. Configure with CMake:
   ```bash
   cmake ..
   ```

3. Build the firmware:
   ```bash
   make -j4
   ```

4. The output file `rp2040_3x3.uf2` will be created in the `build` directory.

### Flashing the Firmware

1. Hold down the BOOTSEL button on your RP2040 board while connecting it to your computer
2. The board will appear as a USB mass storage device
3. Copy the `rp2040_3x3.uf2` file to the mounted drive
4. The board will automatically reboot with the new firmware

## Customization

### Changing the Keymap

Edit `src/config.h` and modify the `keymap` array. Each element is a USB HID keycode:

- `0x04-0x1D`: A-Z
- `0x1E-0x27`: 1-0  
- `0x28`: Enter
- `0x29`: Escape
- `0x2A`: Backspace
- `0x2B`: Tab
- `0x2C`: Space
- `0x4F-0x52`: Arrow keys (Right, Left, Down, Up)

Full keycode reference: [USB HID Usage Tables](https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf) (page 53)

### Changing Pin Assignments

Edit `src/config.h` and update:
- `row_pins[]`: GPIO pins connected to the matrix rows
- `col_pins[]`: GPIO pins connected to the matrix columns

### USB Device Information

Edit `src/usb_descriptors.c` to customize:
- Vendor ID and Product ID
- Manufacturer name
- Product name
- Serial number

## Project Structure

```
.
├── CMakeLists.txt           # Build configuration
├── pico_sdk_import.cmake    # Pico SDK integration
├── README.md                # This file
└── src/
    ├── config.h             # Hardware and keymap configuration (EDIT THIS)
    ├── main.c               # Main program entry point
    ├── keyboard.h           # Keyboard matrix interface
    ├── keyboard.c           # Keyboard matrix scanning logic
    ├── usb_hid.h            # USB HID interface
    ├── usb_hid.c            # USB HID implementation
    ├── usb_descriptors.c    # USB device descriptors
    └── tusb_config.h        # TinyUSB configuration
```

## License

[Add your license here]
