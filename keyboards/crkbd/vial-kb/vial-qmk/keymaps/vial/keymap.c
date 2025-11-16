#include QMK_KEYBOARD_H

#include "features/rgb_matrix.h"
#include "features/shift_backspace.h"
#include "features/leader_key.h"
#include "process_unicode.h"
#include "features/custom_keycodes.h"
#include "features/kb_layout.h"

static bool is_shift_held(void) {
    uint8_t mods = get_mods();
    uint8_t osm  = get_oneshot_mods();
    return ((mods | osm) & MOD_MASK_SHIFT) != 0;
}

/* Send Unicode with Shift temporarily cleared */
static void send_unicode_no_shift(uint32_t codepoint) {
    uint8_t saved_mods = get_mods();
    uint8_t saved_osm  = get_oneshot_mods();

    clear_mods();
    clear_oneshot_mods();
    register_unicode(codepoint);
    set_mods(saved_mods);
    set_oneshot_mods(saved_osm);
}

/* Helper: send base or shifted codepoint depending on Shift state */
static void send_unicode_shifted(uint32_t base_cp, uint32_t shifted_cp) {
    if (is_shift_held()) {
        send_unicode_no_shift(shifted_cp);
    } else {
        send_unicode_no_shift(base_cp);
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // ----- Leader key -----
        case CK_LEADER:
            if (record->event.pressed) {
                leader_start(); // Manually start leader sequence
            }
            return false; // Skip further processing

        // ----- Smart backspace -----
        case KC_BSPC:
            return handle_smart_backspace(record);

        // ----- Swap-hands controls -----
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

        case CK_SH_TT: {
            // Tap-toggle: tap 5x to lock, hold for momentary
            static uint16_t sh_tt_timer = 0;
            static uint8_t  sh_tt_count = 0;

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
        }

        case CK_SH_OS:
            // One-shot: swap for next key press
            if (record->event.pressed) {
                swap_hands_on();
                set_oneshot_layer(get_highest_layer(layer_state), ONESHOT_START);
            }
            return true; // Let the next key process normally

        // ----- Sentence Case keys -----
        case CK_SENTENCE_CASE_ON:
            if (record->event.pressed) {
                sentence_case_on();
            }
            return false;

        case CK_SENTENCE_CASE_OFF:
            if (record->event.pressed) {
                sentence_case_off();
            }
            return false;

        case CK_SENTENCE_CASE_TOGGLE:
            if (record->event.pressed) {
                sentence_case_toggle();
            }
            return false;

        // ===== Arabic letters =====
        case CK_AR_ALEF:
            if (record->event.pressed) send_unicode_shifted(0x0627, 0x0623); // ا (0627) -> Shift: أ (0623)
            return false;

        case CK_AR_BEH:
            if (record->event.pressed) send_unicode_shifted(0x0628, 0x064B); // ب (0628) -> Shift: ً (064B)
            return false;

        case CK_AR_TEH:
            if (record->event.pressed) send_unicode_shifted(0x062A, 0x0640); // ت (062A) -> Shift: ـ (0640)
            return false;

        case CK_AR_THEH:
            if (record->event.pressed) send_unicode_shifted(0x062B, 0x064F); // ث (062B) -> Shift: ُ (064F)
            return false;

        case CK_AR_JEEM:
            if (record->event.pressed) register_unicode(0x062C); // ج
            return false;

        case CK_AR_HAH:
            if (record->event.pressed) register_unicode(0x062D); // ح
            return false;

        case CK_AR_KHAH:
            if (record->event.pressed) register_unicode(0x062E); // خ
            return false;

        case CK_AR_DAL:
            if (record->event.pressed) send_unicode_shifted(0x062F, 0x0630); // د (062F) -> Shift: ذ (0630)
            return false;

        case CK_AR_THAL:
            if (record->event.pressed) register_unicode(0x0630); // ذ
            return false;

        case CK_AR_REH:
            if (record->event.pressed) send_unicode_shifted(0x0631, 0x0632); // ر (0631) -> Shift: ز (0632)
            return false;

        case CK_AR_ZAIN:
            if (record->event.pressed) register_unicode(0x0632); // ز
            return false;

        case CK_AR_SEEN:
            if (record->event.pressed) send_unicode_shifted(0x0633, 0x064D); // س (0633) -> Shift: ٍ (064D)
            return false;

        case CK_AR_SHEEN:
            if (record->event.pressed) send_unicode_shifted(0x0634, 0x0650); // ش (0634) -> Shift: ِ (0650)
            return false;

        case CK_AR_SAD:
            if (record->event.pressed) send_unicode_shifted(0x0635, 0x0636); // ص (0635) -> Shift: ض (0636)
            return false;

        case CK_AR_DAD:
            if (record->event.pressed) register_unicode(0x0636); // ض
            return false;

        case CK_AR_TAH:
            if (record->event.pressed) send_unicode_shifted(0x0637, 0x0638); // ط (0637) -> Shift: ظ (0638)
            return false;

        case CK_AR_ZAH:
            if (record->event.pressed) register_unicode(0x0638); // ظ
            return false;

        case CK_AR_AIN:
            if (record->event.pressed) send_unicode_shifted(0x0639, 0x063A); // ع (0639) -> Shift: غ (063A)
            return false;

        case CK_AR_GHAIN:
            if (record->event.pressed) register_unicode(0x063A); // غ
            return false;

        case CK_AR_FEH:
            if (record->event.pressed) send_unicode_shifted(0x0641, 0x0651); // ف (0641) -> Shift: ّ (0651)
            return false;

        case CK_AR_QAF:
            if (record->event.pressed) send_unicode_shifted(0x0642, 0x064C); // ق (0642) -> Shift: ٌ (064C)
            return false;

        case CK_AR_KAF:
            if (record->event.pressed) send_unicode_shifted(0x0643, 0x003A); // ك (0643) -> Shift: : (003A)
            return false;

        case CK_AR_LAM:
            if (record->event.pressed) send_unicode_shifted(0x0644, 0x0622); // ل (0644) -> Shift: آ (0622)
            return false;

        case CK_AR_MEEM:
            if (record->event.pressed) register_unicode(0x0645); // م
            return false;

        case CK_AR_NOON:
            if (record->event.pressed) register_unicode(0x0646); // ن
            return false;

        case CK_AR_HEH:
            if (record->event.pressed) register_unicode(0x0647); // ه
            return false;

        case CK_AR_WAW:
            if (record->event.pressed) send_unicode_shifted(0x0648, 0x0624); // و (0648) -> Shift: ؤ (0624)
            return false;

        case CK_AR_TEH_MARBUTA:
            if (record->event.pressed) send_unicode_shifted(0x0629, 0x061B); // ة (0629) -> Shift: ؛ (061B)
            return false;

        case CK_AR_HAMZA:
            if (record->event.pressed) send_unicode_shifted(0x0621, 0x0625); // ء (0621) -> Shift: إ (0625)
            return false;

        case CK_AR_YEH:
            if (record->event.pressed) send_unicode_shifted(0x064A, 0x064E); // ي (064A) -> Shift: َ (064E)
            return false;

        case CK_AR_YEH_HAMZA:
            if (record->event.pressed) register_unicode(0x0626); // ئ
            return false;

        case CK_AR_ALEF_MAKSURA:
            if (record->event.pressed) send_unicode_shifted(0x0649, 0x0652); // ى (0649) -> Shift: ْ (0652)
            return false;

        // Hamzated alefs
        case CK_AR_ALEF_MADDA:
            if (record->event.pressed) register_unicode(0x0622); // آ
            return false;

        case CK_AR_ALEF_HAMZA_ABV:
            if (record->event.pressed) register_unicode(0x0623); // أ
            return false;

        case CK_AR_ALEF_HAMZA_BLW:
            if (record->event.pressed) register_unicode(0x0625); // إ
            return false;

        // ===== Arabic diacritics and marks =====
        case CK_AR_FATHA:
            if (record->event.pressed) register_unicode(0x064E); // َ
            return false;

        case CK_AR_DAMMA:
            if (record->event.pressed) register_unicode(0x064F); // ُ
            return false;

        case CK_AR_KASRA:
            if (record->event.pressed) register_unicode(0x0650); // ِ
            return false;

        case CK_AR_SHADDA:
            if (record->event.pressed) register_unicode(0x0651); // ّ
            return false;

        case CK_AR_SUKUN:
            if (record->event.pressed) register_unicode(0x0652); // ْ
            return false;

        case CK_AR_FATHATAN:
            if (record->event.pressed) register_unicode(0x064B); // ً
            return false;

        case CK_AR_DAMMATAN:
            if (record->event.pressed) register_unicode(0x064C); // ٌ
            return false;

        case CK_AR_KASRATAN:
            if (record->event.pressed) register_unicode(0x064D); // ٍ
            return false;

        case CK_AR_TATWEEL:
            if (record->event.pressed) register_unicode(0x0640); // ـ
            return false;

        // ===== Arabic punctuation =====
        case CK_AR_COMMA:
            if (record->event.pressed) register_unicode(0x060C); // ،
            return false;

        case CK_AR_SEMICOLON:
            if (record->event.pressed) register_unicode(0x061B); // ؛
            return false;

        case CK_AR_QUESTION:
            if (record->event.pressed) register_unicode(0x061F); // ؟
            return false;

        case CK_AR_WAW_HAMZA:
            if (record->event.pressed) register_unicode(0x0624); // ؤ
            return false;

        // ----- Unicode mode setters -----
        case CK_UNI_LINUX:
            if (record->event.pressed) {
                set_unicode_input_mode(UNICODE_MODE_LINUX);
            }
            return false;

        case CK_UNI_WINDOWS:
            if (record->event.pressed) {
                set_unicode_input_mode(UNICODE_MODE_WINDOWS);
            }
            return false;

        case CK_UNI_WINCOMPOSE:
            if (record->event.pressed) {
                set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
            }
            return false;

    }

    return true; // Continue processing for other keys
}
