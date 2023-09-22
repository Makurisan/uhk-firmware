#ifndef __MACRO_EVENTS_H__
#define __MACRO_EVENTS_H__

// Includes:

    #include <stdint.h>
    #include <stdbool.h>
    #include "key_action.h"
    #include "usb_device_config.h"
    #include "key_states.h"
    #include "layer.h"

// Macros:


// Typedefs:

// Variables:

    extern bool MacroEvent_CapsLockStateChanged;
    extern bool MacroEvent_NumLockStateChanged;
    extern bool MacroEvent_ScrollLockStateChanged;

// Functions:

    void MacroEvent_OnInit();
    void MacroEvent_OnKeymapChange(uint8_t keymapIdx);
    void MacroEvent_OnLayerChange(layer_id_t layerId);
    void MacroEvent_RegisterLayerMacros();
    void MacroEvent_ProcessStateKeyEvents();

#endif
