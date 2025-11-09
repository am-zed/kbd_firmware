#pragma once

// ============================================================================
// PHYSICAL PIN MAPPING - LAYOUT_split_3x6_3_ex2
// ============================================================================
// Maps logical key positions to physical pin numbers
//
// Physical Layout (46 keys total):
//
// LEFT:                                RIGHT:
// L18 L17 L12 L11 L04 L03 [LE21]      [RE44] R26 R27 R34 R35 R47 R41
// L19 L16 L13 L10 L05 L02 [LE22]      [RE45] R25 R28 R33 R36 R39 R42
// L20 L15 L14 L09 L06 L01                    R24 R29 R32 R37 R38 R43
//               LM08 LM07 LM00        RM23 RM30 RM31
//
// Total: 7+7+7+7+6+6+3+3 = 46 keys
// ============================================================================

// ----------------------------------------------------------------------------
// LEFT HALF - Top Row (6 main keys + 1 extra)
// ----------------------------------------------------------------------------
#define L_TOP_0     18  // L18 - Leftmost key (usually Tab)
#define L_TOP_1     17  // L17
#define L_TOP_2     12  // L12
#define L_TOP_3     11  // L11
#define L_TOP_4      4  // L04
#define L_TOP_5      3  // L03
#define L_EX_TOP    21  // LE21 - Extra key top row (encoder/switch)

// ----------------------------------------------------------------------------
// LEFT HALF - Home Row (6 main keys + 1 extra)
// ----------------------------------------------------------------------------
#define L_HOME_0    19  // L19 - Leftmost home key
#define L_HOME_1    16  // L16
#define L_HOME_2    13  // L13
#define L_HOME_3    10  // L10
#define L_HOME_4     5  // L05
#define L_HOME_5     2  // L02
#define L_EX_BOT    22  // LE22 - Extra key home row (encoder/switch)

// ----------------------------------------------------------------------------
// LEFT HALF - Bottom Row (6 main keys only)
// ----------------------------------------------------------------------------
#define L_BOT_0     20  // L20 - Leftmost bottom key
#define L_BOT_1     15  // L15
#define L_BOT_2     14  // L14
#define L_BOT_3      9  // L09
#define L_BOT_4      6  // L06
#define L_BOT_5      1  // L01

// ----------------------------------------------------------------------------
// LEFT HALF - Thumb Row (3 keys)
// ----------------------------------------------------------------------------
#define L_THUMB_0    8  // LM08 - Leftmost thumb key
#define L_THUMB_1    7  // LM07 - Center thumb key
#define L_THUMB_2    0  // LM00 - Rightmost thumb key (usually Space/Enter)

// ----------------------------------------------------------------------------
// RIGHT HALF - Top Row (1 extra + 6 main keys)
// ----------------------------------------------------------------------------
#define R_EX_TOP    44  // RE44 - Extra key top row (encoder/switch)
#define R_TOP_0     26  // R26 - Leftmost right key (usually Y)
#define R_TOP_1     27  // R27
#define R_TOP_2     34  // R34
#define R_TOP_3     35  // R35
#define R_TOP_4     47  // R47
#define R_TOP_5     41  // R41 - Rightmost key (usually Backspace)

// ----------------------------------------------------------------------------
// RIGHT HALF - Home Row (1 extra + 6 main keys)
// ----------------------------------------------------------------------------
#define R_EX_BOT    45  // RE45 - Extra key home row (encoder/switch)
#define R_HOME_0    25  // R25 - Leftmost right home key (usually H)
#define R_HOME_1    28  // R28
#define R_HOME_2    33  // R33
#define R_HOME_3    36  // R36
#define R_HOME_4    39  // R39
#define R_HOME_5    42  // R42 - Rightmost home key (usually ')

// ----------------------------------------------------------------------------
// RIGHT HALF - Bottom Row (6 main keys only)
// ----------------------------------------------------------------------------
#define R_BOT_0     24  // R24 - Leftmost right bottom key (usually N)
#define R_BOT_1     29  // R29
#define R_BOT_2     32  // R32
#define R_BOT_3     37  // R37
#define R_BOT_4     38  // R38
#define R_BOT_5     43  // R43 - Rightmost bottom key

// ----------------------------------------------------------------------------
// RIGHT HALF - Thumb Row (3 keys)
// ----------------------------------------------------------------------------
#define R_THUMB_0   23  // RM23 - Leftmost right thumb key
#define R_THUMB_1   30  // RM30 - Center right thumb key
#define R_THUMB_2   31  // RM31 - Rightmost right thumb key

// ============================================================================
// LED GROUPS FOR CONVENIENCE
// ============================================================================

// All left side keys (23 keys)
#define LEFT_KEYS { \
    L_TOP_0, L_TOP_1, L_TOP_2, L_TOP_3, L_TOP_4, L_TOP_5, L_EX_TOP, \
    L_HOME_0, L_HOME_1, L_HOME_2, L_HOME_3, L_HOME_4, L_HOME_5, L_EX_BOT, \
    L_BOT_0, L_BOT_1, L_BOT_2, L_BOT_3, L_BOT_4, L_BOT_5, \
    L_THUMB_0, L_THUMB_1, L_THUMB_2 \
}

// All right side keys (23 keys)
#define RIGHT_KEYS { \
    R_EX_TOP, R_TOP_0, R_TOP_1, R_TOP_2, R_TOP_3, R_TOP_4, R_TOP_5, \
    R_EX_BOT, R_HOME_0, R_HOME_1, R_HOME_2, R_HOME_3, R_HOME_4, R_HOME_5, \
    R_BOT_0, R_BOT_1, R_BOT_2, R_BOT_3, R_BOT_4, R_BOT_5, \
    R_THUMB_0, R_THUMB_1, R_THUMB_2 \
}

// Extra keys (2x2 middle - encoders/switches)
#define EXTRA_KEYS { L_EX_TOP, L_EX_BOT, R_EX_TOP, R_EX_BOT }

// Thumb clusters (6 keys total)
#define THUMB_KEYS { L_THUMB_0, L_THUMB_1, L_THUMB_2, R_THUMB_0, R_THUMB_1, R_THUMB_2 }

// Home row keys (12 keys - for home row mods)
#define HOME_ROW_KEYS { \
    L_HOME_0, L_HOME_1, L_HOME_2, L_HOME_3, L_HOME_4, L_HOME_5, \
    R_HOME_0, R_HOME_1, R_HOME_2, R_HOME_3, R_HOME_4, R_HOME_5 \
}

// ============================================================================
// PIN SUMMARY
// ============================================================================
// Left side:  L00-L20, LM00, LM07-08, LE21-22 (23 pins)
// Right side: R24-R47, RM23, RM30-31, RE44-45 (23 pins)
// Total: 46 unique pins
// ============================================================================
