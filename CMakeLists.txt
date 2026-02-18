cmake_minimum_required(VERSION 3.13)

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(rp2040_3x3_firmware C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

# Add executable
add_executable(rp2040_3x3
    src/main.c
    src/keyboard.c
    src/usb_hid.c
    src/usb_descriptors.c
)

# Pull in common dependencies
target_link_libraries(rp2040_3x3
    pico_stdlib
    hardware_gpio
    tinyusb_device
    tinyusb_board
)

# Enable USB output, disable UART output
pico_enable_stdio_usb(rp2040_3x3 0)
pico_enable_stdio_uart(rp2040_3x3 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(rp2040_3x3)
