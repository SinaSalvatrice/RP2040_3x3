# Example Configurations

This directory contains example configuration files for different use cases.

## Available Examples

### config_numpad.h
A simple numpad configuration with keys 1-9.
- Pin configuration: GPIO 6-11
- Keymap: Numbers 1-9 in a 3x3 grid

### config_macropad.h  
A macro pad configuration with function keys and arrow keys.
- Pin configuration: GPIO 2-7
- Keymap: F1-F3 on top row, arrow keys in middle, Space/Down/Enter on bottom

## Using an Example

To use an example configuration:

1. Copy the desired example file to `src/config.h`:
   ```bash
   cp examples/config_numpad.h src/config.h
   ```

2. Adjust the pin assignments if needed to match your hardware

3. Build the firmware:
   ```bash
   cd build
   cmake ..
   make
   ```

## Creating Your Own Configuration

You can use these examples as templates for your own configuration. Just copy one to `src/config.h` and modify:

1. Update the pin numbers in `row_pins[]` and `col_pins[]`
2. Change the keymap values to your desired keys
3. Adjust debounce settings if needed
