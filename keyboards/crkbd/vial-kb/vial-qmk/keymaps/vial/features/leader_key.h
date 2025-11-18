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
    //dprintf("Leader Key: Started (waiting for sequence)\n");
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

    // Leader + w = Save (Ctrl+S / Cmd+S)
    if (leader_sequence_one_key(KC_W)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("s"));     // Cmd+S on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("s"));     // Ctrl+S on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("s"));             // Default to Ctrl+S
        #endif
        leader_sequence_matched = true;
    }

    // Leader + q = Quit (Alt+F4 / Cmd+Q)
    else if (leader_sequence_one_key(KC_Q)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("q"));     // Cmd+Q on macOS
                break;
            default:
                SEND_STRING(SS_LALT(SS_TAP(X_F4))); // Alt+F4 on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));    // Default to Alt+F4
        #endif
        leader_sequence_matched = true;
    }

    // Leader + u = Undo (Ctrl+Z / Cmd+Z)
    else if (leader_sequence_one_key(KC_U)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("z"));     // Cmd+Z on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("z"));     // Ctrl+Z on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("z"));             // Default to Ctrl+Z
        #endif
        leader_sequence_matched = true;
    }

    // Leader + r = Redo (Ctrl+Y / Cmd+Shift+Z)
    else if (leader_sequence_one_key(KC_R)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI(SS_LSFT("z"))); // Cmd+Shift+Z on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("y"));     // Ctrl+Y on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("y"));             // Default to Ctrl+Y
        #endif
        leader_sequence_matched = true;
    }

    // Leader + p = Paste (Ctrl+V / Cmd+V)
    else if (leader_sequence_one_key(KC_P)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("v"));     // Cmd+V on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("v"));     // Ctrl+V on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("v"));             // Default to Ctrl+V
        #endif
        leader_sequence_matched = true;
    }

    // Leader + / = Search (Ctrl+F / Cmd+F)
    else if (leader_sequence_one_key(KC_SLSH)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("f"));     // Cmd+F on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("f"));     // Ctrl+F on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("f"));             // Default to Ctrl+F
        #endif
        leader_sequence_matched = true;
    }

    // Leader + n = Find next (F3 / Cmd+G)
    else if (leader_sequence_one_key(KC_N)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("g"));     // Cmd+G on macOS
                break;
            default:
                SEND_STRING(SS_TAP(X_F3));     // F3 on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_TAP(X_F3));             // Default to F3
        #endif
        leader_sequence_matched = true;
    }

    // Leader + 0 = Go to beginning of line (Home)
    else if (leader_sequence_one_key(KC_0)) {
        tap_code(KC_HOME);
        leader_sequence_matched = true;
    }

    // Leader + $ = Go to end of line (End)
    else if (leader_sequence_one_key(KC_DLR)) {
        tap_code(KC_END);
        leader_sequence_matched = true;
    }

    // Leader + b = Enter bootloader (QMK Boot)
    else if (leader_sequence_one_key(KC_B)) {
        reset_keyboard();
        leader_sequence_matched = true;
    }

    // ==================== TWO-KEY SEQUENCES ====================

    // Leader + a + r = Activate ErgoArabic layer (layer 6)
    else if (leader_sequence_two_keys(KC_A, KC_R)) {
        layer_move(6); // Switch to ErgoArabic layer
        leader_sequence_matched = true;
    }

    // Leader + w + q = Save and Quit
    else if (leader_sequence_two_keys(KC_W, KC_Q)) {
        // Save first
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("s"));     // Save: Cmd+S
                wait_ms(100);
                SEND_STRING(SS_LGUI("q"));     // Quit: Cmd+Q
                break;
            default:
                SEND_STRING(SS_LCTL("s"));     // Save: Ctrl+S
                wait_ms(100);
                SEND_STRING(SS_LALT(SS_TAP(X_F4))); // Quit: Alt+F4
                break;
        }
        #else
        SEND_STRING(SS_LCTL("s"));             // Save: Ctrl+S
        wait_ms(100);
        SEND_STRING(SS_LALT(SS_TAP(X_F4)));    // Quit: Alt+F4
        #endif
        leader_sequence_matched = true;
    }

    // Leader + w + a = Save All (Ctrl+Shift+S / Cmd+Shift+S)
    else if (leader_sequence_two_keys(KC_W, KC_A)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI(SS_LSFT("s"))); // Cmd+Shift+S on macOS
                break;
            default:
                SEND_STRING(SS_LCTL(SS_LSFT("s"))); // Ctrl+Shift+S on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL(SS_LSFT("s")));    // Default to Ctrl+Shift+S
        #endif
        leader_sequence_matched = true;
    }

    // Leader + d + d = Delete line (Vim style)
    else if (leader_sequence_two_keys(KC_D, KC_D)) {
        SEND_STRING(SS_TAP(X_HOME));           // Go to beginning of line
        SEND_STRING(SS_LSFT(SS_TAP(X_END)));   // Select to end of line
        wait_ms(50);
        tap_code(KC_BSPC);                     // Delete selected line
        leader_sequence_matched = true;
    }

    // Leader + y + y = Yank (copy) line (Vim style)
    else if (leader_sequence_two_keys(KC_Y, KC_Y)) {
        SEND_STRING(SS_TAP(X_HOME));           // Go to beginning of line
        SEND_STRING(SS_LSFT(SS_TAP(X_END)));   // Select to end of line
        wait_ms(50);

        // Copy the selected line
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI("c"));     // Cmd+C on macOS
                break;
            default:
                SEND_STRING(SS_LCTL("c"));     // Ctrl+C on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL("c"));             // Default to Ctrl+C
        #endif

        wait_ms(50);
        tap_code(KC_RIGHT);                    // Deselect the text
        leader_sequence_matched = true;
    }

    // Leader + g + g = Go to top of file (Ctrl+Home / Cmd+Up)
    else if (leader_sequence_two_keys(KC_G, KC_G)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI(SS_TAP(X_UP))); // Cmd+Up on macOS
                break;
            default:
                SEND_STRING(SS_LCTL(SS_TAP(X_HOME))); // Ctrl+Home on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LCTL(SS_TAP(X_HOME)));  // Default to Ctrl+Home
        #endif
        leader_sequence_matched = true;
    }

    // Leader + d + w = Delete current word (robust version)
    else if (leader_sequence_two_keys(KC_D, KC_W)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                // macOS: Select word (Option+Shift+Left/Right) then delete
                SEND_STRING(SS_LALT(SS_LSFT(SS_TAP(X_LEFT)))); // Select to word start
                wait_ms(30);
                SEND_STRING(SS_LSFT(SS_LALT(SS_TAP(X_RGHT)))); // Extend to word end
                wait_ms(50);
                tap_code(KC_BSPC); // Delete selection
                break;
            default:
                // Windows/Linux: Select word (Ctrl+Shift+Left/Right) then delete
                SEND_STRING(SS_LCTL(SS_TAP(X_LEFT))); // go to word start
                wait_ms(30);
                SEND_STRING(SS_LSFT(SS_LSFT(SS_LCTL(SS_TAP(X_RGHT))))); // Select to word end
                wait_ms(50);
                tap_code(KC_BSPC); // Delete selection
                break;
        }
        #else
        // Default: Select word then delete
        SEND_STRING(SS_LCTL(SS_TAP(X_LEFT))); // go to word start
        wait_ms(30);
        SEND_STRING(SS_LSFT(SS_LSFT(SS_LCTL(SS_TAP(X_RGHT))))); // Select to word end
        wait_ms(50);
        tap_code(KC_BSPC); // Delete selection
        #endif
        leader_sequence_matched = true;
    }

    // Leader + s + s = Screenshot (full screen)
    else if (leader_sequence_two_keys(KC_S, KC_S)) {
        tap_code(KC_PSCR); // Print Screen
        leader_sequence_matched = true;
    }

    // Leader + s + w = Screenshot active window
    else if (leader_sequence_two_keys(KC_S, KC_W)) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_WINDOWS:
                // Windows: Alt+Print Screen (captures active window)
                SEND_STRING(SS_LALT(SS_TAP(X_PSCR)));
                break;
            case OS_MACOS:
            case OS_IOS:
                // macOS: Cmd+Shift+4 then Space (captures window)
                SEND_STRING(SS_LGUI(SS_LSFT("4")));
                wait_ms(200); // Wait for crosshair to appear
                tap_code(KC_SPC); // Switch to window capture mode
                break;
            case OS_LINUX:
                // Linux: Ctrl+Print Screen (common in many DEs)
                // Alternative: Print Screen alone usually brings up screenshot dialog
                SEND_STRING(SS_LCTL(SS_TAP(X_PSCR)));
                break;
            default:
                // Fallback: Print Screen (may capture full screen)
                tap_code(KC_PSCR);
                break;
        }
        #else
        // Default: Try Ctrl+Print Screen
        SEND_STRING(SS_LCTL(SS_TAP(X_PSCR)));
        #endif
        leader_sequence_matched = true;
    }

    // Leader + g + d = Select All + Delete (clear field)
    else if (leader_sequence_two_keys(KC_G, KC_D)) {
        SEND_STRING(SS_LCTL("a"));  // Ctrl+A (Select All)
        wait_ms(50);
        tap_code(KC_BSPC);          // Backspace (Delete)
        leader_sequence_matched = true;
    }

    // Leader + g + y = Select All + Yank
    else if (leader_sequence_two_keys(KC_G, KC_Y)) {
        // Universal line selection that works across most editors
        SEND_STRING(SS_LCTL("a"));             // Ctrl+A (Select All)
        wait_ms(50);                           // Small delay for selection to complete
        SEND_STRING(SS_LCTL("c"));             // Copy
        wait_ms(50);
        tap_code(KC_END);                     // Deselect
        leader_sequence_matched = true;
    }

    // Leader + d + u = Duplicate current line
    else if (leader_sequence_two_keys(KC_D, KC_U)) {
        SEND_STRING(SS_TAP(X_HOME));
        SEND_STRING(SS_LSFT(SS_TAP(X_END)));
        wait_ms(50);
        SEND_STRING(SS_LCTL("c"));
        wait_ms(50);
        tap_code(KC_RIGHT); // Deselect
        SEND_STRING(SS_TAP(X_END));
        tap_code(KC_ENTER); // New line
        SEND_STRING(SS_LCTL("v")); // Paste duplicate
        leader_sequence_matched = true;
    }


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


    // ==================== SHIFT MODIFIER SEQUENCES ====================

    // Leader + G = Go to bottom of file (Shift+G in Vim)
    //else if (leader_sequence_one_key(S(KC_G))) {
    //    #ifdef OS_DETECTION_ENABLE
    //    switch (detected_host_os()) {
    //        case OS_MACOS:
    //        case OS_IOS:
    //            SEND_STRING(SS_LGUI(SS_TAP(X_DOWN))); // Cmd+Down on macOS
    //            break;
    //        default:
    //            SEND_STRING(SS_LCTL(SS_TAP(X_END)));  // Ctrl+End on Windows/Linux
    //            break;
    //    }
    //    #else
    //    SEND_STRING(SS_LCTL(SS_TAP(X_END)));   // Default to Ctrl+End
    //    #endif
    //    leader_sequence_matched = true;
    //}

    //if (leader_sequence_one_key(KC_G)) {
    //    // Check if Shift is held during this keypress
    //    if (get_mods() & MOD_MASK_SHIFT) {
    //        // Send Ctrl+End for Leader + Shift+G
    //        #ifdef OS_DETECTION_ENABLE
    //        switch (detected_host_os()) {
    //            case OS_MACOS:
    //            case OS_IOS:
    //                SEND_STRING(SS_LGUI(SS_TAP(X_DOWN))); // Cmd+Down on macOS
    //                break;
    //            default:
    //                SEND_STRING(SS_LCTL(SS_TAP(X_END)));  // Ctrl+End on Windows/Linux
    //                break;
    //        }
    //        #else
    //        SEND_STRING(SS_LCTL(SS_TAP(X_END))); // Default Ctrl+End
    //        #endif
    //    }

    //    leader_sequence_matched = true;
    //}

    //if (leader_sequence_one_key(KC_G)) {
    //    uint8_t mods = get_mods() | get_weak_mods();
    //    if (mods & MOD_MASK_SHIFT) {
    //        #ifdef OS_DETECTION_ENABLE
    //        switch (detected_host_os()) {
    //            case OS_MACOS:
    //            case OS_IOS:
    //                SEND_STRING(SS_LGUI(SS_TAP(X_DOWN)));
    //                break;
    //            default:
    //                SEND_STRING(SS_LCTL(SS_TAP(X_END)));
    //                break;
    //        }
    //        #else
    //        SEND_STRING(SS_LCTL(SS_TAP(X_END)));
    //        #endif
    //        leader_sequence_matched = true;
    //    }
    //}

    // Leader + N = Find previous (Shift+N in Vim)
    else if (leader_sequence_one_key(S(KC_N))) {
        #ifdef OS_DETECTION_ENABLE
        switch (detected_host_os()) {
            case OS_MACOS:
            case OS_IOS:
                SEND_STRING(SS_LGUI(SS_LSFT("g"))); // Cmd+Shift+G on macOS
                break;
            default:
                SEND_STRING(SS_LSFT(SS_TAP(X_F3))); // Shift+F3 on Windows/Linux
                break;
        }
        #else
        SEND_STRING(SS_LSFT(SS_TAP(X_F3)));    // Default to Shift+F3
        #endif
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
