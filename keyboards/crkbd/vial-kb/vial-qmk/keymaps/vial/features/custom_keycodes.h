enum custom_keycodes {
    CK_LEADER = QK_KB_0, // Use QK_KB_0 for first custom keycode in Vial

    // Hand swap
    CK_SH_TOGG,
    CK_SH_MON,
    CK_SH_ON,
    CK_SH_OFF,
    CK_SH_TT,
    CK_SH_OS,

    // Sentence Case controls (indexes match vial.json)
    CK_SENTENCE_CASE_ON,
    CK_SENTENCE_CASE_OFF,
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
    CK_AR_THAL,
    CK_AR_REH,
    CK_AR_ZAIN,
    CK_AR_SEEN,
    CK_AR_SHEEN,
    CK_AR_SAD,
    CK_AR_DAD,
    CK_AR_TAH,
    CK_AR_ZAH,
    CK_AR_AIN,
    CK_AR_GHAIN,
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
    CK_AR_ALEF_MADDA,
    CK_AR_ALEF_HAMZA_ABV,
    CK_AR_ALEF_HAMZA_BLW,

    // ===== Arabic diacritics and tanwin =====
    CK_AR_FATHA,
    CK_AR_DAMMA,
    CK_AR_KASRA,
    CK_AR_SHADDA,
    CK_AR_SUKUN,
    CK_AR_FATHATAN,
    CK_AR_DAMMATAN,
    CK_AR_KASRATAN,
    CK_AR_TATWEEL,

    // ===== Arabic punctuation =====
    CK_AR_COMMA,
    CK_AR_SEMICOLON,
    CK_AR_QUESTION,

    CK_AR_WAW_HAMZA,

    // Unicode mode controls
    CK_UNI_LINUX,      // Force UNICODE_MODE_LINUX
    CK_UNI_WINDOWS,    // Force UNICODE_MODE_WINDOWS
    CK_UNI_WINCOMPOSE, // Force UNICODE_MODE_WINCOMPOSE

    CUSTOM_KEYCODE_COUNT,
};
