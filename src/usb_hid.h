#ifndef USB_HID_H
#define USB_HID_H

#include <stdint.h>

// Initialize USB HID
void usb_hid_init(void);

// Process USB tasks (call regularly in main loop)
void usb_hid_task(void);

// Send a keyboard HID report
// keys: array of USB HID keycodes (up to 6)
// key_count: number of keys pressed (0-6)
void usb_hid_send_report(const uint8_t *keys, uint8_t key_count);

#endif // USB_HID_H
