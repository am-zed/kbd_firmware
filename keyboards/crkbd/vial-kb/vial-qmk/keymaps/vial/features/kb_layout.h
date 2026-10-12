
#pragma once

#include "quantum.h"


// Layout: LC*/RC* control keys, LE*/RE* extra keys, LT*/RT* thumb keys:
// LC18, | L17,  L12,  L11,  L04,  L03,  LE21, | RE44, R26,  R27,  R34,  R35,  R47,  | RC41,
// LC19, | L16,  L13,  L10,  L05,  L02,  LE22, | RE45, R25,  R28,  R33,  R36,  R39,  | RC42,
// LC20, | L15,  L14,  L09,  L06,  L01,  NULL, | NULL, R24,  R29,  R32,  R37,  R38,  | RC43,
// NULL, | NULL, NULL, LT08, LT07, LT00, NULL, | NULL, RT23, RT30, RT31, NULL, NULL, | NULL

enum layers {
    _BASE,
    _LOWER,
    _UPPER,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_LCTL,    KC_RCTL,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_LALT,    KC_RALT,    KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_UPPR,  KC_ENT,     KC_SPC, TL_LOWR, QK_KB_0
                                      //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5, KC_LCTL,    KC_RCTL,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,    KC_RALT, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ENT,     KC_SPC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_UPPER] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, KC_LCTL,    KC_RCTL, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LALT,    KC_RALT, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ENT,     KC_SPC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_ENT,     KC_SPC, _______, KC_LALT
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef SWAP_HANDS_ENABLE

// Swap hands configuration for Corne v4.1 with 8 rows × 7 cols matrix
// Split keyboards: left side = rows 0-3, right side = rows 4-7
// Only L01-L17 swap with R24-R47 (mirrored)
// All other keys (LC*, RC*, LE*, RE*, LT*, RT*) map to themselves
const keypos_t PROGMEM hand_swap_config[MATRIX_ROWS][MATRIX_COLS] = {
    // Row 0 (Left): LC18, L17, L12, L11, L04, L03, LE21
    {{0, 0}, {1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 0}},

    // Row 1 (Left): LC19, L16, L13, L10, L05, L02, LE22
    {{0, 1}, {1, 5}, {2, 5}, {3, 5}, {4, 5}, {5, 5}, {6, 1}},

    // Row 2 (Left): LC20, L15, L14, L09, L06, L01, NULL
    {{0, 2}, {1, 6}, {2, 6}, {3, 6}, {4, 6}, {5, 6}, {6, 2}},

    // Row 3 (Left): NULL, NULL, NULL, LT08, LT07, LT00, NULL
    {{0, 3}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {5, 3}, {6, 3}},

    // Row 4 (Right): RE44, R26, R27, R34, R35, R47, RC41
    {{0, 4}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {5, 0}, {6, 4}},

    // Row 5 (Right): RE45, R25, R28, R33, R36, R39, RC42
    {{0, 5}, {1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}, {6, 5}},

    // Row 6 (Right): NULL, R24, R29, R32, R37, R38, RC43
    {{0, 6}, {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 6}},

    // Row 7 (Right): NULL, RT23, RT30, RT31, NULL, NULL, NULL
    {{0, 7}, {1, 7}, {2, 7}, {3, 7}, {4, 7}, {5, 7}, {6, 7}}
};

#endif

