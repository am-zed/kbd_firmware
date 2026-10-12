# Corne v4.1 (46-key) — QMK/Vial Firmware Documentation

**Board:** Corne Choc v4.1 · **MCU:** RP2040 (both halves) · **Keys:** 46 (23 per side)  
**Layout:** `LAYOUT_split_3x6_3_ex2` · **Communication:** Serial/TRRS

---

## Table of Contents

1. [File Structure](#file-structure)
2. [Physical Layout](#physical-layout)
3. [Layers](#layers)
4. [Features](#features)
   - [Leader Key](#leader-key)
   - [Smart Backspace](#smart-backspace)
   - [Arabic Input](#arabic-input)
   - [Swap Hands](#swap-hands)
   - [Sentence Case](#sentence-case)
   - [Draw Boxes](#draw-boxes)
   - [RGB Matrix](#rgb-matrix)
   - [Mouse Jiggler](#mouse-jiggler)
5. [Custom Keycodes](#custom-keycodes)
6. [Key Timing Configuration](#key-timing-configuration)
7. [Split Keyboard Configuration](#split-keyboard-configuration)
8. [Unicode Configuration](#unicode-configuration)
9. [Vial Configuration](#vial-configuration)
10. [QMK Modules](#qmk-modules)
11. [Build & Rules Summary](#build--rules-summary)

---

## File Structure

```
keymap.c                    — Main entry point; process_record_user, matrix_scan_user
keymap.json                 — QMK modules declaration
config.h                    — All compile-time feature configuration
rules.mk                    — Feature enable/disable flags
vial.json                   — Vial GUI layout definition and custom keycode names
rgb_matrix_user.inc         — PaletteFx include hook

features/
  kb_layout.h               — Keymap arrays for all layers + swap-hands config
  custom_keycodes.h         — Enum of all custom keycode IDs
  matrix_pins.h             — Named LED/pin constants for all 46 keys
  leader_key.h              — Leader key sequence definitions
  draw_boxes.h              — Unicode box-drawing macros
  rgb_matrix.h              — Layer-based RGB indicator logic
  shift_backspace.h         — Shift+Backspace → Delete remapping
```

---

## Physical Layout

```
LEFT HALF                              RIGHT HALF
─────────────────────────────────────────────────────────────────────
L_TOP_0  L_TOP_1  L_TOP_2  L_TOP_3  L_TOP_4  L_TOP_5  [L_EX_TOP]   [R_EX_TOP]  R_TOP_0  R_TOP_1  R_TOP_2  R_TOP_3  R_TOP_4  R_TOP_5
L_HOME_0 L_HOME_1 L_HOME_2 L_HOME_3 L_HOME_4 L_HOME_5 [L_EX_BOT]   [R_EX_BOT]  R_HOME_0 R_HOME_1 R_HOME_2 R_HOME_3 R_HOME_4 R_HOME_5
L_BOT_0  L_BOT_1  L_BOT_2  L_BOT_3  L_BOT_4  L_BOT_5                           R_BOT_0  R_BOT_1  R_BOT_2  R_BOT_3  R_BOT_4  R_BOT_5
                            L_THUMB_0 L_THUMB_1 L_THUMB_2           R_THUMB_0 R_THUMB_1 R_THUMB_2
```

- `[L_EX_TOP/BOT]` and `[R_EX_TOP/BOT]` are the 4 middle "extra" keys (encoders/switches).
- Named constants are defined in `features/matrix_pins.h` and map to physical LED numbers (0–45).

---

## Layers

| Index | Name      | Activation           | Description                        |
|-------|-----------|----------------------|------------------------------------|
| 0     | `_BASE`   | Default              | QWERTY with standard modifiers     |
| 1     | `_LOWER`  | Hold `TL_LOWR`       | Numbers (top row) + arrow keys     |
| 2     | `_UPPER`  | Hold `TL_UPPR`       | Symbols, brackets, punctuation     |
| 3     | `_ADJUST` | Hold `_LOWER+_UPPER` | RGB controls + QK_BOOT (flash)     |

Tri-layer is handled by `TRI_LAYER_ENABLE` with `TL_LOWR`/`TL_UPPR` keycodes.

### Base Layer (0)
```
TAB   Q  W  E  R  T  [LCTL]     [RCTL]  Y  U  I  O  P   BSPC
LCTL  A  S  D  F  G  [LALT]     [RALT]  H  J  K  L  ;   '
LSFT  Z  X  C  V  B                     N  M  ,  .  /   ESC
          LGUI  TL_UPPR  ENT     SPC  TL_LOWR  CK_LEADER
```

### Lower Layer (1)
```
TAB   1  2  3  4  5  [LCTL]     [RCTL]  6    7     8   9     0    BSPC
LCTL  -  -  -  -  -  [LALT]     [RALT]  LEFT DOWN  UP  RIGHT -    -
LSFT  -  -  -  -  -                     -    -     -   -     -    -
          LGUI  ___  ENT          SPC  ___  LALT
```

### Upper Layer (2)
```
TAB   !  @  #  $  %  [LCTL]     [RCTL]  ^  &  *  (  )   BSPC
LCTL  -  -  -  -  -  [LALT]     [RALT]  -  =  [  ]  \   `
LSFT  -  -  -  -  -                     _  +  {  }  |   ~
          LGUI  ___  ENT          SPC  ___  LALT
```

### Adjust Layer (3)
```
QK_BOOT  -  -  -  -  -  -     -  -  -  -  -  -  -
RGB_TOG  RGB_HUI  RGB_SAI  RGB_VAI  -  -  -     -  -  -  -  -  -  -
RGB_MOD  RGB_HUD  RGB_SAD  RGB_VAD  -  -              -  -  -  -  -  -
              LGUI  ___  ENT          SPC  ___  LALT
```

---

## Features

### Leader Key

**File:** `features/leader_key.h`  
**Activation:** `CK_LEADER` (right thumb key, base layer)

**Timeout:** 800ms total; per-key timing resets on each keypress.  
**Visual feedback:** RGB → purple while active, green on match, red on miss.

#### One-Key Sequences

| Sequence | Action |
|----------|--------|
| `W` | Save (Ctrl+S / Cmd+S) |
| `Q` | Quit (Alt+F4 / Cmd+Q) |
| `U` | Undo (Ctrl+Z / Cmd+Z) |
| `R` | Redo (Ctrl+Y / Cmd+Shift+Z) |
| `P` | Paste (Ctrl+V / Cmd+V) |
| `/` | Find (Ctrl+F / Cmd+F) |
| `N` | Find Next (F3 / Cmd+G) |
| `0` | Home (beginning of line) |
| `$` | End (end of line) |
| `B` | Draw thin box (Unicode) |
| `Shift+N` | Find Previous (Shift+F3 / Cmd+Shift+G) |

#### Two-Key Sequences

| Sequence | Action |
|----------|--------|
| `W` `Q` | Save then Quit |
| `W` `A` | Save All (Ctrl+Shift+S / Cmd+Shift+S) |
| `D` `D` | Delete line (Home → Shift+End → Backspace) |
| `Y` `Y` | Yank (copy) line |
| `G` `G` | Go to top of file (Ctrl+Home / Cmd+Up) |
| `D` `W` | Delete current word |
| `D` `U` | Duplicate current line |
| `G` `D` | Select All + Delete (clear field) |
| `G` `Y` | Select All + Copy |
| `S` `S` | Screenshot (Print Screen) |
| `S` `W` | Screenshot active window (OS-aware) |
| `A` `R` | Switch to ErgoArabic layer (layer 6) |
| `B` `B` | Draw bold box |
| `B` `D` | Draw double-line box |
| `B` `R` | Draw rounded-corner box |
| `B` `T` | Draw 2-column table with header separator |

#### Three-Key Sequences

| Sequence | Action |
|----------|--------|
| `D` `D` `S` | Type `https://start.duckduckgo.com` + Enter |
| `R` `G` `B` | Toggle RGB matrix |

> All sequences with application shortcuts are OS-aware via `OS_DETECTION_ENABLE`.

---

### Smart Backspace

**File:** `features/shift_backspace.h`

Overrides `KC_BSPC`:

| Input | Output |
|-------|--------|
| `Backspace` | Normal backspace |
| `Shift + Backspace` | Forward delete (`KC_DEL`) |

Works with one-shot shifts and home row mods. Shift is suppressed for a plain `Delete` (i.e., not `Shift+Delete`) unless both shifts are held simultaneously.

---

### Arabic Input

**File:** `keymap.c` (cases), `features/custom_keycodes.h` (enum)  
**Layer:** ErgoArabic (layer 6, activated via `Leader + A + R`)  
**Method:** QMK `register_unicode()` with `send_unicode_no_shift()` wrapper to avoid shift contamination.

#### Letter Keycodes

Each Arabic letter keycode (`CK_AR_*`) sends a Unicode codepoint. Many have a shifted variant:

| Keycode | Base | Shifted |
|---------|------|---------|
| `CK_AR_ALEF` | ا (0627) | أ (0623) |
| `CK_AR_BEH` | ب (0628) | ً (064B) tanwin fath |
| `CK_AR_TEH` | ت (062A) | ـ (0640) tatweel |
| `CK_AR_THEH` | ث (062B) | ُ (064F) damma |
| `CK_AR_JEEM` | ج (062C) | ڨ (06A8) |
| `CK_AR_DAL` | د (062F) | ذ (0630) |
| `CK_AR_REH` | ر (0631) | ز (0632) |
| `CK_AR_SEEN` | س (0633) | ٍ (064D) tanwin kasr |
| `CK_AR_SHEEN` | ش (0634) | ِ (0650) kasra |
| `CK_AR_SAD` | ص (0635) | ض (0636) |
| `CK_AR_TAH` | ط (0637) | ظ (0638) |
| `CK_AR_AIN` | ع (0639) | غ (063A) |
| `CK_AR_FEH` | ف (0641) | ّ (0651) shadda |
| `CK_AR_QAF` | ق (0642) | ٌ (064C) tanwin damm |
| `CK_AR_KAF` | ك (0643) | `:` (003A) |
| `CK_AR_LAM` | ل (0644) | آ (0622) |
| `CK_AR_WAW` | و (0648) | ؤ (0624) |
| `CK_AR_TEH_MARBUTA` | ة (0629) | ؛ (061B) |
| `CK_AR_HAMZA` | ء (0621) | إ (0625) |
| `CK_AR_YEH` | ي (064A) | َ (064E) fatha |
| `CK_AR_ALEF_MAKSURA` | ى (0649) | ْ (0652) sukun |

#### Diacritics & Standalone Marks

| Keycode | Character | Unicode |
|---------|-----------|---------|
| `CK_AR_FATHA` | َ | 064E |
| `CK_AR_DAMMA` | ُ | 064F |
| `CK_AR_KASRA` | ِ | 0650 |
| `CK_AR_SHADDA` | ّ | 0651 |
| `CK_AR_SUKUN` | ْ | 0652 |
| `CK_AR_FATHATAN` | ً | 064B |
| `CK_AR_DAMMATAN` | ٌ | 064C |
| `CK_AR_KASRATAN` | ٍ | 064D |
| `CK_AR_TATWEEL` | ـ | 0640 |

#### Punctuation

| Keycode | Character | Unicode |
|---------|-----------|---------|
| `CK_AR_COMMA` | ، | 060C |
| `CK_AR_SEMICOLON` | ؛ | 061B |
| `CK_AR_QUESTION` | ؟ | 061F |

---

### Swap Hands

**File:** `features/kb_layout.h` (swap config), `keymap.c` (keycodes)  
**Purpose:** Mirror left/right halves for one-handed typing.

`hand_swap_config` maps each physical key to its mirror. Control/extra/thumb keys map to themselves; only the 12 main keys per row are swapped.

| Keycode | Behavior |
|---------|----------|
| `CK_SH_TOGG` | Toggle swap on/off persistently |
| `CK_SH_MON` | Momentary: swap while held |
| `CK_SH_ON` | Force swap on |
| `CK_SH_OFF` | Force swap off |
| `CK_SH_TT` | Tap 5× to toggle; hold for momentary |
| `CK_SH_OS` | One-shot: swap for next keypress only |

---

### Sentence Case

**Module:** `getreuer/sentence_case` (via `keymap.json`)  
**Keycodes:** `CK_SENTENCE_CASE_ON`, `CK_SENTENCE_CASE_OFF`, `CK_SENTENCE_CASE_TOGGLE`

Automatically capitalizes the first letter after a sentence-ending `.`, `!`, or `?` followed by a space.

**Custom endings** (defined in `keymap.c`): The abbreviations `vs.`, `etc.`, and `...` are excluded from triggering capitalization.

Config:
- `SENTENCE_CASE_TIMEOUT`: 5000ms idle reset
- `SENTENCE_CASE_BUFFER_SIZE`: 8 keys (for abbreviation detection)

---

### Draw Boxes

**File:** `features/draw_boxes.h`  
**Activation:** Leader key sequences (see Leader Key section)

All boxes are 10 characters wide. Triggered via `send_box_style()` which types the frame using `register_unicode()` + `KC_ENT`/`KC_SPC`.

| Style | Characters used |
|-------|----------------|
| Thin (`send_box`) | `─ │ ┌ ┐ └ ┘` |
| Bold (`send_box_bold`) | `━ ┃ ┏ ┓ ┗ ┛` |
| Double (`send_box_double`) | `═ ║ ╔ ╗ ╚ ╝` |
| Round (`send_box_round`) | `─ │ ╭ ╮ ╰ ╯` |
| Table (`send_table`) | Mixed; 3-row 2-column with double-line header separator |

---

### RGB Matrix

**File:** `features/rgb_matrix.h`  
**LED count:** 46 (23 per side, defined in `config.h`)

#### Layer Indicators

`rgb_matrix_indicators_advanced_user()` runs every frame and sets specific LEDs per active layer:

| Layer | LED | Color |
|-------|-----|-------|
| Caps Lock (any layer) | `L_EX_BOT` (22) | White |
| 0 (Base) | — | Default effects |
| 1 (Lower/Nav) | `R_EX_TOP` (44) | Cyan |
| 2 (Upper/Symbols) | `L_EX_TOP` (21) | Magenta |
| 3 (Adjust) | `L_EX_TOP` + `R_EX_TOP` | Orange |
| 4 (Mouse) | `R_EX_TOP` (44) | Chartreuse |
| 5 (Macros) | `R_EX_BOT` (45) + macro keys | Pink + Red |
| 6 (ErgoArabic) | `R_EX_BOT` (45) | Pink |
| 7 (RGB) | `L_EX_BOT` (22) | Blue |

The function returns `false` to allow other RGB effects to continue rendering underneath.

#### Effects Enabled

All standard QMK RGB Matrix effects are enabled (`ENABLE_RGB_MATRIX_*`), including reactive, gradient, heatmap, digital rain, and splash effects. PaletteFx effects are also fully enabled via `PALETTEFX_ENABLE_ALL_EFFECTS` and `PALETTEFX_ENABLE_ALL_PALETTES`.

**Defaults on boot:**
- Mode: `RGB_MATRIX_GRADIENT_UP_DOWN`
- Speed: 127
- RGB on: true
- Auto-off: 5 minutes (`RGB_MATRIX_TIMEOUT 300000`)

---

### Mouse Jiggler

**Keycode:** `CK_MOUSE_JIGGLE`  
**Behavior:** Toggles a background jiggler. Every 5 seconds, moves the mouse cursor up then down by one unit. Prevents screen lock/sleep without being visible during normal use.

Implementation uses `matrix_scan_user()` with `timer_elapsed()`.

---

## Custom Keycodes

All custom keycodes are defined in `features/custom_keycodes.h`, starting from `QK_USER_0` to use the keymap-level user keycode range.

| Range | Purpose |
|-------|---------|
| `CK_LEADER` | Leader key trigger |
| `CK_SH_*` (6 codes) | Swap hands controls |
| `CK_SENTENCE_CASE_*` (3 codes) | Sentence case controls |
| `CK_AR_ALEF` … `CK_AR_ALEF_HAMZA_BLW` (35 codes) | Arabic letters |
| `CK_AR_FATHA` … `CK_AR_TATWEEL` (9 codes) | Arabic diacritics |
| `CK_AR_COMMA` … `CK_AR_WAW_HAMZA` (4 codes) | Arabic punctuation |
| `CK_UNI_LINUX/WINDOWS/WINCOMPOSE` | Force Unicode input mode |
| `CK_MOUSE_JIGGLE` | Toggle mouse jiggler |

Total: `CUSTOM_KEYCODE_COUNT` entries.

The `vial.json` `customKeycodes` array mirrors this enum order so Vial GUI displays correct names and short labels.

---

## Key Timing Configuration

| Parameter | Value | Notes |
|-----------|-------|-------|
| `TAPPING_TERM` | 140ms | Tap vs. hold threshold |
| `QUICK_TAP_TERM` | 100ms | Double-tap-to-hold suppression |
| `RETRO_TAPPING` | enabled | Tap fires on solo hold release |
| `SPECULATIVE_HOLD` | enabled | Improves hold detection latency |
| `CHORDAL_HOLD` | enabled | Same-hand = tap, opposite-hand = hold |
| `ONESHOT_TIMEOUT` | 5000ms | One-shot key expires after 5s |
| `ONESHOT_TAP_TOGGLE` | 5 | Tap 5× to lock one-shot |
| `LEADER_TIMEOUT` | 800ms | Per-key timeout for leader sequences |
| `CAPS_WORD_IDLE_TIMEOUT` | 5000ms | Caps Word auto-off |
| `LAYER_LOCK_IDLE_TIMEOUT` | 5000ms | Layer Lock auto-release |
| `DEBOUNCE` | 5ms | Switch debounce |

**Chordal Hold** uses `CHORDAL_HOLD_LAYOUT` macro in `config.h` to manually assign `'L'`/`'R'` handedness to every key position, and `chordal_hold_handedness()` in `keymap.c` to handle any remaining keys by matrix row.

---

## Split Keyboard Configuration

| Setting | Value |
|---------|-------|
| Master side | Left (`MASTER_LEFT`) |
| Communication | Serial/TRRS |
| USB detection | `SPLIT_USB_DETECT`, 2000ms timeout |
| Watchdog timeout | 3000ms (reboot slave on lost comms) |
| Synced state | Layer, mods, LED state, activity, transport mirror |

---

## Unicode Configuration

| Setting | Value |
|---------|-------|
| `UNICODE_SELECTED_MODES` | Linux, Windows, WinCompose, macOS |
| `UNICODE_CYCLE_PERSIST` | false (resets to first mode on reboot) |
| `UNICODE_TYPE_DELAY` | 10ms between keystrokes |

OS detection (`OS_DETECTION_ENABLE`) auto-sets the initial Unicode mode on connection.

Force-set at runtime with:
- `CK_UNI_LINUX` → `UNICODE_MODE_LINUX`
- `CK_UNI_WINDOWS` → `UNICODE_MODE_WINDOWS`
- `CK_UNI_WINCOMPOSE` → `UNICODE_MODE_WINCOMPOSE`

---

## Vial Configuration

**File:** `vial.json`

- **UID:** `{0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}`
- **Unlock combo:** Row 0, cols 0+1 (top-left two keys)
- **Matrix:** 8 rows × 7 cols
- **Lighting:** `vialrgb`
- **Dynamic features** (from `config.h`):

| Feature | Slots |
|---------|-------|
| Combos | 32 |
| Tap Dance | 32 |
| Key Overrides | 32 |
| Alt Repeat Key | 32 |
| Macros | 32 |
| Layers | 16 |

The `layouts.labels` array defines 4 encoder/switch variant groups for the extra keys.

---

## QMK Modules

Declared in `keymap.json`:

| Module | Purpose |
|--------|---------|
| `getreuer/palettefx` | Extended RGB palette cycling (included via `rgb_matrix_user.inc`) |
| `getreuer/sentence_case` | Auto-capitalize sentence starts |
| `srwi/keypeek_layer_notify` | Visual layer change notifications |

---

## Build & Rules Summary

Key flags from `rules.mk`:

| Flag | State |
|------|-------|
| `VIAL_ENABLE` | yes |
| `SPLIT_KEYBOARD` | yes |
| `RGB_MATRIX_ENABLE` | yes |
| `UNICODE_ENABLE` | yes |
| `LEADER_ENABLE` | yes |
| `SWAP_HANDS_ENABLE` | yes |
| `AUTO_SHIFT_ENABLE` | yes |
| `TRI_LAYER_ENABLE` | yes |
| `CAPS_WORD_ENABLE` | yes |
| `LAYER_LOCK_ENABLE` | yes |
| `KEY_LOCK_ENABLE` | yes |
| `MOUSEKEY_ENABLE` | yes |
| `NKRO_ENABLE` | yes (boots in 6KRO; toggle with `NK_TOGG`) |
| `OS_DETECTION_ENABLE` | yes |
| `DYNAMIC_MACRO_ENABLE` | yes |
| `CONSOLE_ENABLE` | no |
| `LTO_ENABLE` | no |
| `AUDIO_ENABLE` | no |
| `OLED_ENABLE` | no |
