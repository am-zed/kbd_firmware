#include QMK_KEYBOARD_H


#include "features/rgb_matrix.h"
#include "features/shift_backspace.h"
#include "features/leader_key.h"
#include "features/custom_keycodes.h"

#include "features/kb_layout.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_LEADER:
            if (record->event.pressed) {
                leader_start();  // Manually start leader sequence
            }
            return false;  // Skip further processing

        case KC_BSPC:
            return handle_smart_backspace(record);
    }

    return true;  // Continue processing for other keys
}

