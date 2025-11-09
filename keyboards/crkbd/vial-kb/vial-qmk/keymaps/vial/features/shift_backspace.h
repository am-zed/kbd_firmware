/*
 * Smart Backspace Feature
 * Automatically send Delete when Shift+Backspace is pressed
 * Regular Backspace when pressed without Shift
 *
 * Usage:
 * - Backspace alone: Delete backward (standard backspace)
 * - Shift+Backspace: Delete forward (equivalent to Delete key)
 * - Works with one-shot shifts and home row mods
 */

#pragma once

#include "quantum.h"

static bool handle_smart_backspace(keyrecord_t *record) {
    static uint16_t registered_key = KC_NO;

    if (record->event.pressed) {
        const uint8_t mods = get_mods();

        // Compute shift modifier state including oneshot if supported
        #ifndef NO_ACTION_ONESHOT
            uint8_t shift_mods = (mods | get_oneshot_mods()) & MOD_MASK_SHIFT;
        #else
            uint8_t shift_mods = mods & MOD_MASK_SHIFT;
        #endif

        if (shift_mods) {
            // Shift is held or active via one-shot
            registered_key = KC_DEL;

            // If exactly one shift held (not both), suppress shift for plain delete
            if (shift_mods != MOD_MASK_SHIFT) {
                #ifndef NO_ACTION_ONESHOT
                    del_oneshot_mods(MOD_MASK_SHIFT);
                #endif
                unregister_mods(MOD_MASK_SHIFT);
            }

            dprintf("Smart Backspace: Delete (shift detected)\n");
        } else {
            // No shift held
            registered_key = KC_BSPC;
            dprintf("Smart Backspace: Backspace (no shift)\n");
        }

        register_code(registered_key);
        set_mods(mods);  // Restore original modifier state after registering

    } else {
        // Key released
        unregister_code(registered_key);
        registered_key = KC_NO;  // Reset registered key
        dprintf("Smart Backspace: Released\n");
    }

    return false;  // Always consume the key event
}

