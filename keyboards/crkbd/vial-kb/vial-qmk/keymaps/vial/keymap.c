#include QMK_KEYBOARD_H


#include "features/rgb_matrix.h"
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
    }
    return true;  // Continue processing for other keys
}

