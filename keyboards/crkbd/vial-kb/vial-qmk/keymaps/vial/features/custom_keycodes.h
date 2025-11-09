#pragma once

#include "quantum.h"

enum custom_keycodes {
    CK_LEADER = QK_KB_0,  // Use QK_KB_0 for first custom keycode in Vial

    // hand swap
    CK_SH_TOGG,
    CK_SH_MON,
    CK_SH_ON,
    CK_SH_OFF,
    CK_SH_TT,
    CK_SH_OS,

    // End marker (do not use for keycodes)
    CUSTOM_KEYCODE_COUNT,  // Tracks number of custom keycodes
};
