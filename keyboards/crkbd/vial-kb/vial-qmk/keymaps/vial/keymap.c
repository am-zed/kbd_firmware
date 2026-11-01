#include QMK_KEYBOARD_H

#include "features/custom_keycodes.h"
#include "features/kb_layout.h"
#include "features/draw_boxes.h"
#include "features/leader_key.h"
#include "features/rgb_matrix.h"
#include "features/shift_backspace.h"
#include "process_unicode.h"

static bool jiggle_enabled = false;
static uint16_t jiggle_timer;
static uint16_t jiggle_interval = 2000;
static uint8_t jiggle_step = 0;

static uint16_t jiggle_rand(uint16_t range) {
    static uint16_t seed = 0xACE1;
    seed ^= seed << 7;
    seed ^= seed >> 9;
    seed ^= seed << 8;
    return seed % range;
}

static bool is_shift_held(void) {
  uint8_t mods = get_mods();
  uint8_t osm = get_oneshot_mods();
  return ((mods | osm) & MOD_MASK_SHIFT) != 0;
}

/* Send Unicode with Shift temporarily cleared */
static void send_unicode_no_shift(uint32_t codepoint) {
  uint8_t saved_mods = get_mods();
  uint8_t saved_osm = get_oneshot_mods();

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

bool sentence_case_check_ending(const uint16_t *buffer) {
  // Don't consider the abbreviations "vs.", "etc.", and "..." to end the
  // sentence.
  if (SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_V, KC_S, KC_DOT) ||
      SENTENCE_CASE_JUST_TYPED(KC_SPC, KC_E, KC_T, KC_C, KC_DOT) ||
      SENTENCE_CASE_JUST_TYPED(KC_DOT, KC_DOT, KC_DOT)) {
    return false; // Not a real sentence ending.
  }
  return true; // Real sentence ending; capitalize next letter.
}

#ifdef CHORDAL_HOLD
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT(
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R',
        'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R',
                       'L', 'L', 'L',            'R', 'R', 'R'
    );
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool is_pressed    = record->event.pressed;

  switch (keycode) {
  // ----- Leader key -----
  case CK_LEADER:
    if (is_pressed) {
      leader_start(); // Manually start leader sequence
    }
    return false; // Skip further processing

  // ----- Smart backspace -----
  case KC_BSPC:
    return handle_smart_backspace(record);

  // ----- Swap-hands controls -----
  case CK_SH_TOGG:
    if (is_pressed) {
      swap_hands_toggle();
    }
    return false;

  // ----- Sentence Case keys -----
  case CK_SENTENCE_CASE_TOGGLE:
    if (is_pressed) {
      sentence_case_toggle();
    }
    return false;

  // ===== Arabic letters =====
  case CK_AR_ALEF:
    if (is_pressed)
      send_unicode_shifted(0x0627, 0x0623); // ا (0627) -> Shift: أ (0623)
    return false;

  case CK_AR_BEH:
    if (is_pressed)
      send_unicode_shifted(0x0628, 0x064B); // ب (0628) -> Shift: ً (064B)
    return false;

  case CK_AR_TEH:
    if (is_pressed)
      send_unicode_shifted(0x062A, 0x0640); // ت (062A) -> Shift: ـ (0640)
    return false;

  case CK_AR_THEH:
    if (is_pressed)
      send_unicode_shifted(0x062B, 0x064F); // ث (062B) -> Shift: ُ (064F)
    return false;

  case CK_AR_JEEM:
    if (is_pressed)
      send_unicode_shifted(0x062C, 0x06A8); // ج (0x062C) -> Shift: ڨ (0x06A8)
    return false;

  case CK_AR_HAH:
    if (is_pressed)
      send_unicode_shifted(0x062D, 0x067E); // ح (062D) -> Shift: پ (067E)
    return false;

  case CK_AR_KHAH:
    if (is_pressed)
      send_unicode_shifted(0x062E, 0x2026); // خ (062E) -> Shift: … (2026)
    return false;

  case CK_AR_DAL:
    if (is_pressed)
      send_unicode_shifted(0x062F, 0x0630); // د (062F) -> Shift: ذ (0630)
    return false;

  case CK_AR_REH:
    if (is_pressed)
      send_unicode_shifted(0x0631, 0x0632); // ر (0631) -> Shift: ز (0632)
    return false;

  case CK_AR_SEEN:
    if (is_pressed)
      send_unicode_shifted(0x0633, 0x064D); // س (0633) -> Shift: ٍ (064D)
    return false;

  case CK_AR_SHEEN:
    if (is_pressed)
      send_unicode_shifted(0x0634, 0x0650); // ش (0634) -> Shift: ِ (0650)
    return false;

  case CK_AR_SAD:
    if (is_pressed)
      send_unicode_shifted(0x0635, 0x0636); // ص (0635) -> Shift: ض (0636)
    return false;

  case CK_AR_TAH:
    if (is_pressed)
      send_unicode_shifted(0x0637, 0x0638); // ط (0637) -> Shift: ظ (0638)
    return false;

  case CK_AR_AIN:
    if (is_pressed)
      send_unicode_shifted(0x0639, 0x063A); // ع (0639) -> Shift: غ (063A)
    return false;

  case CK_AR_FEH:
    if (is_pressed)
      send_unicode_shifted(0x0641, 0x0651); // ف (0641) -> Shift: ّ (0651)
    return false;

  case CK_AR_QAF:
    if (is_pressed)
      send_unicode_shifted(0x0642, 0x064C); // ق (0642) -> Shift: ٌ (064C)
    return false;

  case CK_AR_KAF:
    if (is_pressed)
      send_unicode_shifted(0x0643, 0x003A); // ك (0643) -> Shift: : (003A)
    return false;

  case CK_AR_LAM:
    if (is_pressed)
      send_unicode_shifted(0x0644, 0x0622); // ل (0644) -> Shift: آ (0622)
    return false;

  case CK_AR_MEEM:
    if (is_pressed)
      send_unicode_shifted(0x0645, 0x06A5); // م (0645) -> Shift: ڥ  (06A5)
    return false;

  case CK_AR_NOON:
    if (is_pressed)
      send_unicode_shifted(0x0646, 0xFDFA); // ن -> Shift: ﷺ
    return false;

  case CK_AR_HEH:
    if (is_pressed)
      send_unicode_shifted(0x0647, 0xFD4C); // ه (0647) -> Shift: ﵌ (FD4C)
    return false;

  case CK_AR_WAW:
    if (is_pressed)
      send_unicode_shifted(0x0648, 0x0624); // و (0648) -> Shift: ؤ (0624)
    return false;

  case CK_AR_TEH_MARBUTA:
    if (is_pressed)
      send_unicode_shifted(0x0629, 0x061B); // ة (0629) -> Shift: ؛ (061B)
    return false;

  case CK_AR_HAMZA:
    if (is_pressed)
      send_unicode_shifted(0x0621, 0x0625); // ء (0621) -> Shift: إ (0625)
    return false;

  case CK_AR_YEH:
    if (is_pressed)
      send_unicode_shifted(0x064A, 0x064E); // ي (064A) -> Shift: َ (064E)
    return false;

  case CK_AR_YEH_HAMZA:
    if (is_pressed)
      send_unicode_shifted(0x0626, 0xFDFD); // ئ -> Shift: besmellah
    return false;

  case CK_AR_ALEF_MAKSURA:
    if (is_pressed)
      send_unicode_shifted(0x0649, 0x0652); // ى (0649) -> Shift: ْ (0652)
    return false;

  case CK_AR_COMMA:
    if (is_pressed)
      send_unicode_shifted(0x060C, 0x003C); // ، (060C) -> Shift: < (003C)
    return false;

  case CK_AR_QUESTION:
    if (is_pressed)
      send_unicode_shifted(0x061F, 0x003E); // ؟ (061F) -> Shift: > (003E)
    return false;

  // ----- User-defined Unicode characters -----
  case CK_UNI_FDFE:
    if (is_pressed)
      register_unicode(0xFDFE); // ﷾
    return false;

  case CK_UNI_FDFF:
    if (is_pressed)
      register_unicode(0xFDFF); // ﷿
    return false;

  case CK_UNI_1F932:
    if (is_pressed)
      send_unicode_shifted(0x1F932, 0x1F3AF); // 🤲 -> Shift: 🎯
    return false;

  // ----- Unicode mode setters -----
  case CK_UNI_LINUX:
    if (is_pressed) {
      set_unicode_input_mode(UNICODE_MODE_LINUX);
    }
    return false;

  case CK_UNI_WINDOWS:
    if (is_pressed) {
      set_unicode_input_mode(UNICODE_MODE_WINDOWS);
    }
    return false;

  case CK_UNI_WINCOMPOSE:
    if (is_pressed) {
      set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
    }
    return false;

//  case CK_MOUSE_JIGGLE:
//    if (is_pressed) {
//      jiggle_enabled = !jiggle_enabled;
//      jiggle_timer = timer_read();
//    }
//    return false;
  case CK_MOUSE_JIGGLE:
    if (is_pressed) {
        jiggle_enabled = !jiggle_enabled;
        jiggle_timer   = timer_read();
        jiggle_interval = 1000 + jiggle_rand(2001); // 1000-3000 ms
    }
    return false;
  }

  return true; // Continue processing for other keys
}

//void matrix_scan_user(void) {
//  if (jiggle_enabled && timer_elapsed(jiggle_timer) > 5000) {
//    tap_code16(KC_MS_UP);   // move mouse up
//    tap_code16(KC_MS_DOWN); // then down
//    jiggle_timer = timer_read();
//  }
//}

void matrix_scan_user(void) {
    if (jiggle_enabled && timer_elapsed(jiggle_timer) >= jiggle_interval) {
        switch (jiggle_step++ & 3) {
            case 0: tap_code(KC_MS_UP);    break;
            case 1: tap_code(KC_MS_RIGHT); break;
            case 2: tap_code(KC_MS_DOWN);  break;
            case 3: tap_code(KC_MS_LEFT);  break;
        }

        jiggle_timer    = timer_read();
        jiggle_interval = 1000 + jiggle_rand(2001); // randomized 1-3 s
    }

    // keep any existing code here
}

char chordal_hold_handedness(keypos_t key) {
    return key.row < MATRIX_ROWS / 2 ? 'L' : 'R';
}
