#ifndef __USB_DESCRIPTOR_SYSTEM_KEYBOARD_REPORT_H__
#define __USB_DESCRIPTOR_SYSTEM_KEYBOARD_REPORT_H__

// Includes:

    #include "usb_api.h"
    #include "arduino_hid/SystemAPI.h"

// Macros:

    #define USB_SYSTEM_KEYBOARD_REPORT_DESCRIPTOR_LENGTH (sizeof(UsbSystemKeyboardReportDescriptor))
    #define USB_SYSTEM_KEYBOARD_MAX_KEYS 1

// Variables:

    static USB_DESC_STORAGE_TYPE UsbSystemKeyboardReportDescriptor[] = {
        HID_RI_USAGE_PAGE(8, HID_RI_USAGE_PAGE_GENERIC_DESKTOP),
        HID_RI_USAGE(8, HID_RI_USAGE_GENERIC_DESKTOP_SYSTEM_CONTROL),
        HID_RI_COLLECTION(8, HID_RI_COLLECTION_APPLICATION),
            // System keys
            HID_RI_LOGICAL_MINIMUM(8, 0),
            HID_RI_LOGICAL_MAXIMUM(8, 1),
            HID_RI_USAGE_MINIMUM(8, SYSTEM_POWER_DOWN), // SYSTEM_POWER_DOWN, SYSTEM_SLEEP and SYSTEM_WAKE_UP
            HID_RI_USAGE_MAXIMUM(8, SYSTEM_WAKE_UP),
            HID_RI_REPORT_SIZE(8, 1),
            HID_RI_REPORT_COUNT(8, 3),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

            // Padding
            HID_RI_REPORT_SIZE(8, 1),
            HID_RI_REPORT_COUNT(8, 5),
            HID_RI_INPUT(8, HID_IOF_CONSTANT),
        HID_RI_END_COLLECTION(0),
    };

#endif
