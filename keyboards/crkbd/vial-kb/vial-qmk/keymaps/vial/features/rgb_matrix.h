/*
 * RGB Matrix Layer Indicators
 * Visual feedback for active layers using LED colors
 */

#pragma once

#include "quantum.h"
#include "matrix_pins.h"

/**
 * @brief Set color for a specific LED if it's within the current range
 * @param led_num Target LED number
 * @param led_min Minimum LED index in current range
 * @param led_max Maximum LED index in current range
 * @param r Red component (0-255)
 * @param g Green component (0-255)
 * @param b Blue component (0-255)
 */
static inline void set_led_color_if_in_range(uint8_t led_num, uint8_t led_min, uint8_t led_max, uint8_t r, uint8_t g, uint8_t b) {
    if (led_min <= led_num && led_num < led_max) {
        rgb_matrix_set_color(led_num, r, g, b);
    }
}

// Convenience macro for RGB colors
#define SET_LED_RGB(led_num, led_min, led_max, color) set_led_color_if_in_range(led_num, led_min, led_max, color)

/**
 * @brief Set LED colors based on active layer and keyboard state
 * @param led_min Minimum LED index in current range
 * @param led_max Maximum LED index in current range
 * @return false to allow other RGB effects to run
 */
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Caps Lock indicator - LED 22 (L_EX_BOT) turns white when active
    if (host_keyboard_led_state().caps_lock) {
        set_led_color_if_in_range(L_EX_BOT, led_min, led_max, RGB_WHITE);
    }

    // Layer-specific LED indicators
    switch (get_highest_layer(layer_state)) {
        case 0:
            // Base layer - use default RGB effects (no override)
            break;

        case 1: // Navigation Layer / LED 44 (R_EX_TOP)
            set_led_color_if_in_range(R_EX_TOP, led_min, led_max, RGB_CYAN);
            break;

        case 2: // Function/RGB Layer / LED 21 (L_EX_TOP)
            set_led_color_if_in_range(L_EX_TOP, led_min, led_max, RGB_MAGENTA);
            break;

        case 3: { // Symbols Layer / LEDs 21 (L_EX_TOP) and 44 (R_EX_TOP)
            const uint8_t leds[] = {L_EX_TOP, R_EX_TOP};
            for (uint8_t i = 0; i < ARRAY_SIZE(leds); i++) {
                set_led_color_if_in_range(leds[i], led_min, led_max, RGB_ORANGE);
            }
            break;
        }

        case 4: // Mouse Layer / LED 44 (R_EX_TOP)
            set_led_color_if_in_range(R_EX_TOP, led_min, led_max, RGB_CHARTREUSE);
            break;

        case 5: { // Macros Layer / LED 45 (R_EX_BOT) + macro key highlights
            // Primary indicator
            set_led_color_if_in_range(R_EX_BOT, led_min, led_max, RGB_PINK);

            // Additional macro keys highlighted in red
            const uint8_t macro_leds[] = {
                L_TOP_5, L_TOP_4, L_TOP_3, L_TOP_2, L_TOP_1,   // Left top row
                R_TOP_0, R_TOP_1,                              // Right top row
                R_THUMB_2,                                     // Right thumb
                R_EX_TOP                                       // Right extra top
            };
            for (uint8_t i = 0; i < ARRAY_SIZE(macro_leds); i++) {
                set_led_color_if_in_range(macro_leds[i], led_min, led_max, RGB_RED);
            }
            break;
        }

        case 6: // ErgoArabic Layer / LED 45 (R_EX_BOT)
            set_led_color_if_in_range(R_EX_BOT, led_min, led_max, RGB_PINK);
            break;

        case 7: // RGB Layer / LED 22 (L_EX_BOT)
            set_led_color_if_in_range(L_EX_BOT, led_min, led_max, RGB_BLUE);
            break;

        default:
            // Unknown layer - use default RGB effects
            break;
    }

    return false; // Allow other RGB effects to run
}
