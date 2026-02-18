#include "usb_hid.h"
#include "tusb.h"
#include <string.h>

// HID report structure
typedef struct {
    uint8_t modifiers;  // Modifier keys (Ctrl, Shift, Alt, etc.)
    uint8_t reserved;   // Reserved byte
    uint8_t keys[6];    // Up to 6 simultaneous key presses
} hid_keyboard_report_t;

static hid_keyboard_report_t keyboard_report = {0};

void usb_hid_init(void) {
    // TinyUSB is initialized by the SDK
    tusb_init();
}

void usb_hid_task(void) {
    // Process TinyUSB tasks
    tud_task();
}

void usb_hid_send_report(const uint8_t *keys, uint8_t key_count) {
    // Only send if USB is ready
    if (!tud_hid_ready()) {
        return;
    }
    
    // Clear previous report
    memset(&keyboard_report, 0, sizeof(keyboard_report));
    
    // Copy keys (up to 6)
    if (key_count > 6) {
        key_count = 6;
    }
    memcpy(keyboard_report.keys, keys, key_count);
    
    // Send HID report
    tud_hid_keyboard_report(0, keyboard_report.modifiers, keyboard_report.keys);
}

// ============================================================================
// TinyUSB Callbacks
// ============================================================================

// Invoked when received GET_REPORT control request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, 
                                hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen) {
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;
    
    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, 
                            hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize) {
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}

// Invoked when device is mounted
void tud_mount_cb(void) {
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
}

// Invoked when USB bus is suspended
void tud_suspend_cb(bool remote_wakeup_en) {
    (void) remote_wakeup_en;
}

// Invoked when USB bus is resumed
void tud_resume_cb(void) {
}
