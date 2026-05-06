
#pragma once

#include "quantum.h"

#include QMK_KEYBOARD_H

typedef struct {
    uint32_t h;
    uint32_t v;
    uint32_t tl;
    uint32_t tr;
    uint32_t bl;
    uint32_t br;
} box_style_t;

static void send_repeat_unicode(uint32_t cp, uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        register_unicode(cp);
    }
}

static void send_box_style(uint8_t w, box_style_t s) {
    register_unicode(s.tl);
    send_repeat_unicode(s.h, w);
    register_unicode(s.tr);
    tap_code(KC_ENT);

    register_unicode(s.v);
    for (uint8_t i = 0; i < w; i++) {
        tap_code(KC_SPC);
    }
    register_unicode(s.v);
    tap_code(KC_ENT);

    register_unicode(s.bl);
    send_repeat_unicode(s.h, w);
    register_unicode(s.br);
}

static void send_box(void) {
    send_box_style(10, (box_style_t){
        .h  = 0x2500, // ─
        .v  = 0x2502, // │
        .tl = 0x250C, // ┌
        .tr = 0x2510, // ┐
        .bl = 0x2514, // └
        .br = 0x2518  // ┘
    });
}

static void send_box_bold(void) {
    send_box_style(10, (box_style_t){
        .h  = 0x2501, // ━
        .v  = 0x2503, // ┃
        .tl = 0x250F, // ┏
        .tr = 0x2513, // ┓
        .bl = 0x2517, // ┗
        .br = 0x251B  // ┛
    });
}

static void send_box_double(void) {
    send_box_style(10, (box_style_t){
        .h  = 0x2550, // ═
        .v  = 0x2551, // ║
        .tl = 0x2554, // ╔
        .tr = 0x2557, // ╗
        .bl = 0x255A, // ╚
        .br = 0x255D  // ╝
    });
}

static void send_box_round(void) {
    send_box_style(10, (box_style_t){
        .h  = 0x2500, // ─
        .v  = 0x2502, // │
        .tl = 0x256D, // ╭
        .tr = 0x256E, // ╮
        .bl = 0x2570, // ╰
        .br = 0x256F  // ╯
    });
}

//void leader_end_user(void) {
//    if (leader_sequence_one_key(KC_B)) {
//        send_box();
//    } else if (leader_sequence_two_keys(KC_B, KC_B)) {
//        send_box_bold();
//    } else if (leader_sequence_two_keys(KC_B, KC_D)) {
//        send_box_double();
//    } else if (leader_sequence_two_keys(KC_B, KC_R)) {
//        send_box_round();
//    }
//}

static void send_table(void) {
    const uint8_t w = 10;

    // Top border
    register_unicode(0x250C);              // ┌
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x252C);              // ┬
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x2510);              // ┐
    tap_code(KC_ENT);

    // Header row
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    tap_code(KC_ENT);

    // Header separator: double horizontal
    register_unicode(0x255E);              // ╞
    send_repeat_unicode(0x2550, w);        // ═
    register_unicode(0x256A);              // ╪
    send_repeat_unicode(0x2550, w);        // ═
    register_unicode(0x2561);              // ╡
    tap_code(KC_ENT);

    // Row 2
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    tap_code(KC_ENT);

    // Separator
    register_unicode(0x251C);              // ├
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x253C);              // ┼
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x2524);              // ┤
    tap_code(KC_ENT);

    // Row 3
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    for (uint8_t i = 0; i < w; i++) tap_code(KC_SPC);
    register_unicode(0x2502);              // │
    tap_code(KC_ENT);

    // Bottom border
    register_unicode(0x2514);              // └
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x2534);              // ┴
    send_repeat_unicode(0x2500, w);        // ─
    register_unicode(0x2518);              // ┘
}

