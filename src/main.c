#include <stdio.h>
#include "pico/stdlib.h"
#include "keyboard.h"
#include "usb_hid.h"

int main() {
    // Initialize standard library
    stdio_init_all();
    
    // Small delay to allow USB to enumerate
    sleep_ms(1000);
    
    // Initialize keyboard matrix
    keyboard_init();
    
    // Initialize USB HID
    usb_hid_init();
    
    // Main loop
    while (1) {
        // Scan keyboard matrix and send reports
        keyboard_task();
        
        // Process USB tasks
        usb_hid_task();
        
        // Small delay for timing
        sleep_us(SCAN_INTERVAL_US);
    }
    
    return 0;
}
