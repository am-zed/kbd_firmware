enum custom_keycodes {
  CK_LEADER = QK_KB_0, // Use QK_KB_0 for first custom keycode in Vial

  // Hand swap
  CK_SH_TOGG,

  // Sentence Case controls (indexes match vial.json)
  CK_SENTENCE_CASE_TOGGLE,

  // ===== Arabic letters =====
  CK_AR_ALEF,
  CK_AR_BEH,
  CK_AR_TEH,
  CK_AR_THEH,
  CK_AR_JEEM,
  CK_AR_HAH,
  CK_AR_KHAH,
  CK_AR_DAL,
  CK_AR_REH,
  CK_AR_SEEN,
  CK_AR_SHEEN,
  CK_AR_SAD,
  CK_AR_TAH,
  CK_AR_AIN,
  CK_AR_FEH,
  CK_AR_QAF,
  CK_AR_KAF,
  CK_AR_LAM,
  CK_AR_MEEM,
  CK_AR_NOON,
  CK_AR_HEH,
  CK_AR_WAW,
  CK_AR_TEH_MARBUTA,
  CK_AR_HAMZA,
  CK_AR_YEH,
  CK_AR_YEH_HAMZA,
  CK_AR_ALEF_MAKSURA,

  // ===== Arabic punctuation =====
  CK_AR_COMMA,
  CK_AR_QUESTION,

  // User-defined Unicode characters
  CK_UNI_FDFE,
  CK_UNI_FDFF,
  CK_UNI_1F932,

  // Unicode mode controls
  CK_UNI_LINUX,      // Force UNICODE_MODE_LINUX
  CK_UNI_WINDOWS,    // Force UNICODE_MODE_WINDOWS
  CK_UNI_WINCOMPOSE, // Force UNICODE_MODE_WINCOMPOSE

  // Mouse jiggler
  CK_MOUSE_JIGGLE,

  CUSTOM_KEYCODE_COUNT,
};
