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

        case CK_SH_TOGG:
            if (record->event.pressed) {
                swap_hands_toggle();
            }
            return false;

        case CK_SH_MON:
            if (record->event.pressed) {
                swap_hands_on();
            } else {
                swap_hands_off();
            }
            return false;

        case CK_SH_ON:
            if (record->event.pressed) {
                swap_hands_on();
            }
            return false;

        case CK_SH_OFF:
            if (record->event.pressed) {
                swap_hands_off();
            }
            return false;

        case CK_SH_TT:
            // Tap-toggle: tap 5x to lock, hold for momentary
            static uint16_t sh_tt_timer = 0;
            static uint8_t sh_tt_count = 0;

            if (record->event.pressed) {
                if (timer_elapsed(sh_tt_timer) < TAPPING_TERM) {
                    sh_tt_count++;
                    if (sh_tt_count >= 5) {
                        swap_hands_toggle();
                        sh_tt_count = 0;
                    }
                } else {
                    sh_tt_count = 1;
                    swap_hands_on();
                }
                sh_tt_timer = timer_read();
            } else {
                if (sh_tt_count < 5) {
                    swap_hands_off();
                }
            }
            return false;

        case CK_SH_OS:
            // One-shot: swap for next key press
            if (record->event.pressed) {
                swap_hands_on();
                set_oneshot_layer(get_highest_layer(layer_state), ONESHOT_START);
            }
    }

    return true;  // Continue processing for other keys
}

