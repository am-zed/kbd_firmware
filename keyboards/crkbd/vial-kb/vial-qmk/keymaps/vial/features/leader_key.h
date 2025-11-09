/*
 * Leader Key Sequences
 * Vim-style key sequences for macros and shortcuts
 *
 * Usage: Press QK_LEAD, then sequence keys
 * Example: Leader + d + d = Select All + Delete
 */

#pragma once

#include "quantum.h"

// Track whether a sequence was matched (for feedback)
static bool leader_sequence_matched = false;

// Called when Leader key is pressed
void leader_start_user(void) {
    dprintf("Leader Key: Started (waiting for sequence)\n");
    leader_sequence_matched = false;

    // Optional: Visual feedback (LED indicator)
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(HSV_PURPLE);  // Purple = Leader active
    #endif
}

// Called when Leader sequence completes or times out
void leader_end_user(void) {
    // ==================== ONE-KEY SEQUENCES ====================

    // Leader + f = Type "QMK is awesome!"
    //if (leader_sequence_one_key(KC_F)) {
    //    SEND_STRING("QMK is awesome!");
    //    leader_sequence_matched = true;
    //}

    // Leader + e = Type email (customize in features/macros.h)
    //else if (leader_sequence_one_key(KC_E)) {
    //    SEND_STRING("user@example.com");
    //    leader_sequence_matched = true;
    //}

    // Leader + u = Type URL
    //else if (leader_sequence_one_key(KC_U)) {
    //    SEND_STRING("https://example.com");
    //    leader_sequence_matched = true;
    //}

    // Leader + b = Enter bootloader (QMK Boot)
    if (leader_sequence_one_key(KC_B)) {
        reset_keyboard();
        leader_sequence_matched = true;
    }

    // ==================== TWO-KEY SEQUENCES ====================

    // Leader + d + d = Select All + Delete (clear field)
    else if (leader_sequence_two_keys(KC_D, KC_D)) {
        SEND_STRING(SS_LCTL("a"));  // Ctrl+A (Select All)
        wait_ms(50);
        tap_code(KC_BSPC);          // Backspace (Delete)
        leader_sequence_matched = true;
    }

    // Leader + c + c = Ctrl+A, Ctrl+C (Select All, Copy)
    else if (leader_sequence_two_keys(KC_C, KC_C)) {
        SEND_STRING(SS_LCTL("a") SS_LCTL("c"));
        leader_sequence_matched = true;
    }

    // Fullscreen screenshot - Linux
    else if (leader_sequence_two_keys(KC_S, KC_S)) {
        // Leader + s + s = Screenshot (Shift+Win+S on Windows)
        //tap_code16(S(G(KC_S)));
        tap_code(KC_PSCR);
        leader_sequence_matched = true;
    }

    // Active window screenshot - Linux
    //else if (leader_sequence_two_keys(KC_S, KC_W)) {
    //    tap_code16(C(KC_PSCR));
    //    leader_sequence_matched = true;
    //}

    // ==================== THREE-KEY SEQUENCES ====================

    // Leader + d + d + s = Type DuckDuckGo URL
    else if (leader_sequence_three_keys(KC_D, KC_D, KC_S)) {
        SEND_STRING("https://start.duckduckgo.com\n");
        leader_sequence_matched = true;
    }

    // Leader + r + g + b = Toggle RGB
    else if (leader_sequence_three_keys(KC_R, KC_G, KC_B)) {
        rgb_matrix_toggle();
        leader_sequence_matched = true;
    }

    // ==================== END NOTIFICATION ====================

    // Provide feedback on sequence completion
    if (leader_sequence_matched) {
        //dprintf("Leader Key: Sequence matched!\n");

        // Visual feedback: Brief green flash
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_GREEN);
        wait_ms(200);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
        #endif
    } else {
        //dprintf("Leader Key: No sequence matched (timed out or invalid)\n");

        // Visual feedback: Brief red flash
        #ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_RED);
        wait_ms(200);
        rgb_matrix_mode_noeeprom(RGB_MATRIX_GRADIENT_UP_DOWN);
        #endif
    }
}
