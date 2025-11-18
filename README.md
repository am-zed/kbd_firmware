# Custom QMK/Vial Keyboard Firmware

A feature-rich QMK firmware implementation with Vial support, featuring extensive customization options including leader key macros, Arabic Unicode support, RGB lighting effects, and advanced typing features.

## Table of Contents

- [Features Overview](#features-overview)
- [Layer Configuration](#layer-configuration)
- [Leader Key Sequences](#leader-key-sequences)
- [Custom Features](#custom-features)
- [Arabic Unicode Support](#arabic-unicode-support)
- [RGB Matrix Lighting](#rgb-matrix-lighting)
- [Typing Enhancements](#typing-enhancements)
- [Configuration Options](#configuration-options)
- [Building and Flashing](#building-and-flashing)

---

## Features Overview

### Core Features
- **Vial Support**: Real-time keymap configuration via Vial GUI
- **8 Layers**: Base, Navigation, Function/RGB, Symbols, Mouse, Macros, ErgoArabic, RGB control
- **Leader Key System**: Vim-inspired key sequences for complex macros
- **Unicode Input**: Full Arabic alphabet with diacritics and special characters
- **RGB Matrix**: Per-key RGB lighting with layer indicators
- **Split Keyboard Support**: Full split keyboard configuration with hand detection
- **Smart Typing Features**: Auto-shift, sentence case, smart backspace
- **Swap Hands**: One-handed typing mirror mode

### Advanced Features
- Tri-layer activation
- Dynamic macros (32 slots, 256 keystrokes)
- Custom shift key behaviors
- OS detection for cross-platform shortcuts
- Tap-hold configurations
- Caps Word mode
- Layer lock functionality

---

## Layer Configuration

### Layer 0: Base Layer
Default typing layer with standard QWERTY layout and home row modifiers.

### Layer 1: Navigation Layer
- **Indicator**: Right extra top LED (Cyan)
- Arrow keys, Home, End, Page Up/Down
- Text selection shortcuts

### Layer 2: Function/RGB Layer
- **Indicator**: Left extra top LED (Magenta)
- Function keys (F1-F12)
- RGB control keys
- Media controls

### Layer 3: Symbols Layer
- **Indicator**: Both extra top LEDs (Orange)
- Special characters and symbols
- Programming-focused punctuation

### Layer 4: Mouse Layer
- **Indicator**: Right extra top LED (Chartreuse)
- Mouse movement and buttons
- Scroll wheel controls

### Layer 5: Macros Layer
- **Indicator**: Right extra bottom LED (Pink), macro keys highlighted in red
- Pre-programmed macro shortcuts
- Dynamic macro recording

### Layer 6: ErgoArabic Layer
- **Indicator**: Right extra bottom LED (Pink)
- Full Arabic alphabet with shift variants
- Arabic diacritics (Fatha, Damma, Kasra, Shadda, Sukun, Tanwin)
- Arabic punctuation
- Accessible via `Leader + A + R`

### Layer 7: RGB Control Layer
- **Indicator**: Left extra bottom LED (Blue)
- Advanced RGB effects
- Brightness and speed controls

---

## Leader Key Sequences

The leader key system uses Vim-style sequences for powerful macros. Press the Leader key (configured as `CK_LEADER`) followed by the sequence.

### Visual Feedback
- **Purple LED**: Leader sequence active, waiting for input
- **Green flash**: Sequence successfully matched
- **Red flash**: Invalid sequence or timeout

### One-Key Sequences

#### File Operations
- `Leader + W` → Save (Ctrl+S / Cmd+S)
- `Leader + Q` → Quit (Alt+F4 / Cmd+Q)

#### Edit Operations
- `Leader + U` → Undo (Ctrl+Z / Cmd+Z)
- `Leader + R` → Redo (Ctrl+Y / Cmd+Shift+Z)
- `Leader + P` → Paste (Ctrl+V / Cmd+V)

#### Search & Navigation
- `Leader + /` → Search (Ctrl+F / Cmd+F)
- `Leader + N` → Find Next (F3 / Cmd+G)
- `Leader + Shift+N` → Find Previous (Shift+F3 / Cmd+Shift+G)
- `Leader + 0` → Go to beginning of line (Home)
- `Leader + $` → Go to end of line (End)

#### System
- `Leader + B` → Enter bootloader mode (for flashing firmware)

### Two-Key Sequences

#### Layer Control
- `Leader + A + R` → Activate ErgoArabic layer (Layer 6)

#### File Operations
- `Leader + W + Q` → Save and Quit
- `Leader + W + A` → Save All (Ctrl+Shift+S / Cmd+Shift+S)

#### Line Operations (Vim-style)
- `Leader + D + D` → Delete current line
- `Leader + Y + Y` → Yank (copy) current line
- `Leader + D + U` → Duplicate current line
- `Leader + D + W` → Delete current word

#### Navigation
- `Leader + G + G` → Go to top of file (Ctrl+Home / Cmd+Up)

#### Selection & Deletion
- `Leader + G + D` → Select All and Delete (clear field)
- `Leader + G + Y` → Select All and Copy

#### Screenshots
- `Leader + S + S` → Screenshot (full screen)
- `Leader + S + W` → Screenshot active window (OS-specific)

### Three-Key Sequences
- `Leader + D + D + S` → Type DuckDuckGo URL
- `Leader + R + G + B` → Toggle RGB lighting

### Configuration
- **Timeout**: 800-1000ms (configurable via `LEADER_TIMEOUT`)
- **Per-key timing**: Each key in sequence resets the timeout
- **Strict processing**: Only defined sequences are processed

---

## Custom Features

### Smart Backspace
Enhanced backspace behavior with context-aware deletion:
- Deletes matching brackets/quotes automatically
- Handles whitespace intelligently
- Configured in `shift_backspace.h`

### Swap Hands
Mirror the keyboard for one-handed typing:
- `CK_SH_TOGG` - Toggle swap hands on/off
- `CK_SH_MON` - Momentary swap while held
- `CK_SH_TT` - Tap 5 times to lock, hold for momentary
- `CK_SH_OS` - One-shot swap for next key only
- `CK_SH_ON` / `CK_SH_OFF` - Explicit on/off controls

### Sentence Case
Automatically capitalize the first letter of sentences:
- `CK_SENTENCE_CASE_ON` - Enable sentence case
- `CK_SENTENCE_CASE_OFF` - Disable sentence case
- `CK_SENTENCE_CASE_TOGGLE` - Toggle on/off
- Timeout: 5 seconds of inactivity
- Buffer size: 8 keys for abbreviation detection

### Caps Word
Type a word in all caps, then automatically return to lowercase:
- **Activation**: Press both shift keys simultaneously
- **Auto-disable**: After 5 seconds of inactivity or when typing spaces/punctuation
- Continues through numbers and underscores

---

## Arabic Unicode Support

### Full Arabic Alphabet
The ErgoArabic layer (Layer 6) provides complete Arabic typing support with shift variants for efficient input.

#### Base Letters (Unshifted)
ا ب ت ث ج ح خ د ذ ر ز س ش ص ض ط ظ ع غ ف ق ك ل م ن ه و ة ء ي ئ ى

#### Shifted Variants
Many letters have diacritics or alternate forms when shifted:
- `Shift + ا` → أ (Alef with Hamza above)
- `Shift + ب` → ً (Fathatan)
- `Shift + ي` → َ (Fatha)
- `Shift + ل` → آ (Alef with Madda)

### Arabic Diacritics
- **Fatha** (َ) - Short "a" sound
- **Damma** (ُ) - Short "u" sound  
- **Kasra** (ِ) - Short "i" sound
- **Shadda** (ّ) - Consonant doubling
- **Sukun** (ْ) - Vowel absence
- **Tanwin**: Fathatan (ً), Dammatan (ٌ), Kasratan (ٍ)
- **Tatweel** (ـ) - Kashida/elongation

### Arabic Punctuation
- **Comma** (،) - Arabic comma
- **Semicolon** (؛) - Arabic semicolon
- **Question Mark** (؟) - Arabic question mark

### Unicode Mode Configuration
Select the appropriate Unicode input mode for your OS:
- `CK_UNI_LINUX` - Linux (Ctrl+Shift+U method)
- `CK_UNI_WINDOWS` - Windows (Alt+numpad method)
- `CK_UNI_WINCOMPOSE` - Windows with WinCompose
- Auto-detection enabled via OS detection feature

Supported modes can be cycled: Linux, Windows, WinCompose, macOS

---

## RGB Matrix Lighting

### Layer Indicators
Specific LEDs illuminate to show the active layer:
- **Caps Lock**: Left extra bottom LED (White)
- **Layer 1 (Navigation)**: Right extra top LED (Cyan)
- **Layer 2 (Function/RGB)**: Left extra top LED (Magenta)
- **Layer 3 (Symbols)**: Both extra top LEDs (Orange)
- **Layer 4 (Mouse)**: Right extra top LED (Chartreuse)
- **Layer 5 (Macros)**: Right extra bottom LED (Pink), macro keys in red
- **Layer 6 (ErgoArabic)**: Right extra bottom LED (Pink)
- **Layer 7 (RGB)**: Left extra bottom LED (Blue)

### RGB Effects
- **Default Mode**: Gradient Up/Down
- **Reactive Effects**: Lighting responds to keypresses
- **Framebuffer Effects**: Typing heatmap and trails
- **Performance**: 60 FPS animation, 10 LEDs per frame
- **Auto-off**: After 5 minutes of inactivity
- **USB Suspend**: RGB disabled when computer sleeps

### LED Configuration
- **Total LEDs**: 46 (23 per side for split keyboard)
- **Default Brightness**: 128/255
- **Maximum Brightness**: 200/255 (power saving)

### RGB Control
- Enable/disable RGB when USB suspended
- Layer-specific RGB overrides default settings
- Keypress and key release triggers

---

## Typing Enhancements

### Auto Shift
Hold a key longer to type the shifted character automatically.
- **Timeout**: 175ms (configurable)
- **Excluded**: Special characters and numbers (no auto-shift)
- **No Auto Repeat**: Prevents unwanted character spam

### Tapping Configuration
Fine-tuned tap-hold behavior for dual-function keys:
- **Tapping Term**: 200ms to distinguish tap from hold
- **Permissive Hold**: Trigger hold if another key pressed during tapping
- **Quick Tap Term**: 120ms for rapid key repeat
- **Retro Tapping**: Send tap on release if no other key pressed

### Flow Tap
Disables hold functionality during fast typing sequences:
- **Flow Tap Term**: 150ms window
- Prevents accidental modifiers when typing quickly
- Ideal for home row mods

### Chordal Hold
Opposite-hands rule for tap-hold keys:
- **Same hand keys**: Tap (prevent accidental mod)
- **Opposite hand keys**: Hold (intentional modifier)
- Prevents accidental capitals with home row mods

---

## Configuration Options

### Tri-Layer
Automatically activate a third layer when two layers are held:
- **Lower Layer**: 1 (Navigation)
- **Upper Layer**: 2 (Function/RGB)
- **Adjust Layer**: 3 (Symbols) - activated when both held

### Dynamic Macros
Record and playback custom keystroke sequences:
- **Macro Slots**: 32 available
- **Buffer Size**: 256 keystrokes total
- **Playback Delay**: 10-20ms between keystrokes
- Record via Vial GUI or on-the-fly

### Split Keyboard Settings
- **Communication**: Serial over TRRS cable
- **Serial Pin**: GP12 (UART0 TX)
- **Handedness Detection**: Pin-based (GP21)
- **Master Side**: Left (USB connects to left half)
- **Synchronization**: Layer state, modifiers, LEDs, activity
- **Watchdog**: Auto-reboot slave after 3s timeout
- **USB Detection**: Active USB communication detection

### NKRO (N-Key Rollover)
- **Boot Mode**: 6-Key Rollover (6KRO) for maximum compatibility
- **Toggle**: Use `NK_TOGG` keycode to enable NKRO when needed
- **Persistence**: NKRO state saved across reboots

### One-Shot Keys
Press modifier once, then press another key - modifier applies then releases:
- **Timeout**: 5 seconds
- **Tap-Toggle**: Tap 5 times to lock modifier
- Works with Shift, Ctrl, Alt, GUI

### Layer Lock
Lock a layer active without holding the layer key:
- **Idle Timeout**: 5 seconds of inactivity auto-unlocks
- Useful for extended work in a specific layer

---

## Building and Flashing

### Prerequisites
- QMK Firmware environment
- Vial enabled in build
- RP2040-based keyboard controller

### Build Command
```bash
qmk compile -kb <your_keyboard> -km vial
```

### Flash Command
```bash
qmk flash -kb <your_keyboard> -km vial
```

### Bootloader Entry
- **Via Keymap**: Press `Leader + B`
- **Physical**: Short BOOT and GND pins while plugging in USB
- **Via Vial**: Use "Reboot to Bootloader" option in Vial GUI

### Files Structure
```
.
├── config.h              # Main configuration file
├── rules.mk              # Build options and features
├── keymap.c              # Keymap and process_record_user
├── keymap.json           # Base keymap definition
├── vial.json             # Vial GUI configuration
│
├── features/
│   ├── leader_key.h      # Leader key sequences
│   ├── shift_backspace.h # Smart backspace logic
│   ├── custom_keycodes.h # Custom keycode definitions
│   ├── rgb_matrix.h      # RGB layer indicators
│   ├── kb_layout.h       # Keyboard layout definition
│   └── matrix_pins.h     # Pin assignments
```

---

## Customization

### Adding Leader Key Sequences
Edit `leader_key.h` and add new sequences in the `leader_end_user()` function:

```c
// Example: Leader + M + Y = Type "my text"
else if (leader_sequence_two_keys(KC_M, KC_Y)) {
    SEND_STRING("my text");
    leader_sequence_matched = true;
}
```

### Modifying RGB Indicators
Edit `rgb_matrix.h` to change LED colors for layers:

```c
case 1: // Navigation Layer
    set_led_color_if_in_range(LED_INDEX, led_min, led_max, RGB_CYAN);
    break;
```

### Adjusting Timeouts
Modify timing values in `config.h`:
- `LEADER_TIMEOUT` - Leader key sequence timeout
- `TAPPING_TERM` - Tap vs hold distinction
- `AUTO_SHIFT_TIMEOUT` - Auto-shift delay
- `CAPS_WORD_IDLE_TIMEOUT` - Caps Word auto-disable

### Unicode Input
Add custom Unicode characters in `keymap.c`:

```c
case MY_CUSTOM_CHAR:
    if (record->event.pressed) register_unicode(0x1F600); // 😀
    return false;
```

---

## Troubleshooting

### Arabic Characters Not Typing
1. Ensure correct Unicode mode is set for your OS
2. On Linux: `CK_UNI_LINUX` (Ctrl+Shift+U method)
3. On Windows: `CK_UNI_WINCOMPOSE` (requires WinCompose installed)
4. Try increasing `UNICODE_TYPE_DELAY` in config.h

### Leader Key Timeout Too Short
Increase `LEADER_TIMEOUT` in config.h (default: 800-1000ms)

### Split Keyboard Not Communicating
1. Check TRRS cable connection
2. Verify `SOFT_SERIAL_PIN` matches your wiring
3. Ensure both halves have correct handedness detection
4. Check `SPLIT_HAND_PIN` is correctly configured

### RGB Not Working
1. Verify `RGB_MATRIX_ENABLE` in rules.mk
2. Check LED count matches your hardware (46 total, 23 per side)
3. Ensure adequate USB power for LEDs
4. Try reducing `RGB_MATRIX_MAXIMUM_BRIGHTNESS`

### Accidental Modifier Triggers
Fine-tune tap-hold settings:
1. Increase `TAPPING_TERM` for more deliberate holds
2. Enable `FLOW_TAP` to prevent holds during fast typing
3. Adjust `FLOW_TAP_TERM` for your typing speed

---

## Credits

- QMK Firmware: https://qmk.fm/
- Vial: https://get.vial.today/
- Custom Shift Keys: https://getreuer.info/posts/keyboards/custom-shift-keys

---

## License

This firmware configuration is provided as-is for personal use and modification.
