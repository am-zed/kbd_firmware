#pragma once

#define VIAL_KEYBOARD_UID {0x89, 0x36, 0x2A, 0xC7, 0xFA, 0xD8, 0x89, 0x45}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

// Set default layout macro to LAYOUT_split_3x6_3_ex2
// This allows using LAYOUT() instead of LAYOUT_split_3x6_3_ex2() in keymap.c
#define LAYOUT LAYOUT_split_3x6_3_ex2

// Disable audio features at compile time
#define NO_AUDIO
#define NO_MUSIC_MODE

#define MOD_MORPH_ENABLE

// ==================== TRI-LAYER CONFIGURATION ====================

// Tri-Layer - Activate third layer when two layers held simultaneously
// Allows efficient layer stacking with minimal keys
//
// Default behavior:
// - Hold LOWER (layer 1): Access lower layer
// - Hold UPPER (layer 2): Access upper layer
// - Hold LOWER + UPPER together: Activate ADJUST (layer 3)

// Lower layer number (usually function/navigation)
// Default: 1
//OK//#define TRI_LAYER_LOWER_LAYER 1

// Upper layer number (usually symbols/numbers)
// Default: 2
//OK//#define TRI_LAYER_UPPER_LAYER 2

// Adjust layer (activated by LOWER + UPPER)
// Default: 3
//OK//#define TRI_LAYER_ADJUST_LAYER 3

// ==================== CUSTOM SHIFT KEYS CONFIGURATION ====================

// Custom Shift Keys - Customize shifted behavior of specific keys
// See: https://getreuer.info/posts/keyboards/custom-shift-keys/

// Negative Mods - Disable custom shift keys when these mods are held
// Default: Apply custom shift keys with all mods
// Example: Don't apply with Ctrl (prevents Ctrl+Shift+. becoming Ctrl+?)
//OK//#define CUSTOM_SHIFT_KEYS_NEGMODS MOD_MASK_CTRL

// Alternative: Only apply custom shift keys when ONLY shift is held
// #define CUSTOM_SHIFT_KEYS_NEGMODS ~MOD_MASK_SHIFT

// Layer Mask - Restrict custom shift keys to specific layers
// Default: Apply on all layers
// Example: Only apply on layer 0 and 2
// #define CUSTOM_SHIFT_KEYS_LAYER_MASK (1 << 0) | (1 << 2)
//OK//#define CUSTOM_SHIFT_KEYS_LAYER_MASK (1 << 0)

// Example: Apply on all layers except layer 3 (gaming layer)
// #define CUSTOM_SHIFT_KEYS_LAYER_MASK ~(1 << 3)

// ==================== FLOW TAP CONFIGURATION ====================

// Flow Tap - Disable hold during fast typing sequences
// When you press a tap-hold key within FLOW_TAP_TERM of the previous key,
// it automatically taps (ignores hold), creating a "flow" of taps
//
// Example without Flow Tap:
//   Type "shift+a": Hold Shift, tap A, release A, release Shift
//   Problem: If you tap A too quickly, Shift might register as hold
//
// Example with Flow Tap:
//   Type "shift+a": Hold Shift, tap A within FLOW_TAP_TERM
//   Result: Correct Shift+A output (Flow Tap auto-taps the A)
//
// Recommended: Enable for smoother typing, especially with home row mods

// Flow Tap Term - Milliseconds to auto-tap after previous key
// Default: 150ms (good starting point)
// Lower values: Stricter (less forgiving)
// Higher values: Looser (more forgiving, faster typing)
//OK//#ifndef FLOW_TAP_TERM
//OK//#define FLOW_TAP_TERM 150
//OK//#endif

// ==================== CHORDAL HOLD CONFIGURATION ====================

// Chordal Hold - Implement "opposite hands" rule for tap-hold keys
// When a tap-hold key is pressed and another key is pressed before TAPPING_TERM:
// - If keys are on SAME hand → tap (prevent accidental mod)
// - If keys are on OPPOSITE hands → hold (modifier applies)
//
// Example without Chordal Hold:
//   Hold Shift(A), tap C on same hand → Shift+C (might be accident)
//
// Example with Chordal Hold:
//   Hold Shift(A), tap C on same hand → tap AC (no modifier)
//   Hold Shift(A), tap C on opposite hand → Shift+C (intentional chord)
//
// Recommended: Enable for home row mods to avoid accidental capitals

//OK//#ifndef CHORDAL_HOLD
//OK//#define CHORDAL_HOLD
//OK//#endif

// Chordal Hold Manual - Manually define which keys are on which hand
// Corne: 3x6 split
// Left hand:  cols 0-2  (6 rows worth)
// Right hand: cols 3-5  (6 rows worth)
//
// Layout string format:
// - 'L': Left hand
// - 'R': Right hand
// - '*': Exempt from Chordal Hold
//
// Chordal Hold Manual - Manually define which keys are on which hand
// Corne: 3x6_3_ex2 split layout (6 main keys per hand + 2x2 middle extra)
//
// Physical layout:
// Left Hand (6 keys)  Middle (2x2 extra)   Right Hand (6 keys)
// CTL Q  W  E  R  T   EX │ EX   Y U  I  O  P CTL
// CTL A  S  D  F  G   EX │ EX   H J  K  L  ;  CTL
// CTL Z  X  C  V  B      │         N  M  ,  .  / CTL
//       GUI LWR SPC      │         ENT UPR ALT
//
// Key counts per row:
// Row 0: 6 left keys + 2 middle keys + 6 right keys = 14 total
// Row 1: 6 left keys + 2 middle keys + 6 right keys = 14 total
// Row 2: 6 left keys (gap) + 6 right keys = 12 total
// Row 3: 3 left thumb + 3 right thumb = 6 total
//

/* OK
#define CHORDAL_HOLD_LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06,  K07, K08, K09, K010, K011, K012, K013, \
    K10, K11, K12, K13, K14, K15, K16,  K17, K18, K19, K110, K111, K112, K113, \
    K20, K21, K22, K23, K24, K25,            K26, K27, K28, K29, K210, K211, \
                        K30, K31, K32,  K33, K34, K35 \
) \
    'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R', \
    'L', 'L', 'L', 'L', 'L', 'L', 'L',  'R', 'R', 'R', 'R', 'R', 'R', 'R', \
    'L', 'L', 'L', 'L', 'L', 'L',            'R', 'R', 'R', 'R', 'R', 'R', \
                        'L', 'L', 'L',  'R', 'R', 'R'
*/

// ==================== AUTO SHIFT CONFIGURATION ====================

// Auto Shift - Automatically capitalize letters when held longer
// Reduces need for dedicated Shift key, improves typing ergonomics
// Example: Tap 'a' = 'a', Hold 'a' = 'A'

// Auto Shift Timeout - Milliseconds to hold before shifted character
// Default: 175ms (conservative)
// Recommended: Start at 175, work down to 135-150 for fast typing
// Lower values: Easier to trigger capitals, faster typing
// Higher values: More deliberate, fewer accidental capitals
#define AUTO_SHIFT_TIMEOUT 175

// No Auto Shift Special - Do not auto-shift special keys
// Includes: -_, =+, [{, ]}, ;:, '", ,<, .>, /?, KC_TAB
// Recommended: Enable (prevents unintended symbol shifts)
#define NO_AUTO_SHIFT_SPECIAL

// No Auto Shift Numeric - Do not auto-shift numbers (0-9)
// Prevents holding 1 from producing !
// Recommended: Enable (most people don't want auto-shift on numbers)
#define NO_AUTO_SHIFT_NUMERIC

// Auto Shift No Auto Repeat - Disable key repeat when holding past timeout
// Without this: Hold 'a' past timeout = AAAA (repeating capitals)
// With this: Hold 'a' past timeout = A (single capital, no repeat)
// Recommended: Enable (prevents unwanted character spam)
//OK//#define AUTO_SHIFT_NO_AUTO_REPEAT

// No Auto Shift Alpha - Do not auto-shift alphabetic keys (A-Z)
// Uncomment to disable auto-shift on letters entirely
// Useful if you only want auto-shift on special keys
// #define NO_AUTO_SHIFT_ALPHA

// No Auto Shift Symbols - Do not auto-shift symbol keys
// Includes: -_, =+, [{, ]}, ;:, '", ,<, .>
// Already covered by NO_AUTO_SHIFT_SPECIAL
// #define NO_AUTO_SHIFT_SYMBOLS

// Auto Shift Modifiers - Enable auto-shift when modifiers are held
// Default: Auto-shift disabled when Ctrl/Alt/GUI are held
// Uncomment to enable: Ctrl+a held = Ctrl+Shift+A
// Not recommended: Can cause unexpected shortcuts
// #define AUTO_SHIFT_MODIFIERS

// Auto Shift No Setup - Disable tuning mode keycodes (AS_UP, AS_DOWN, AS_RPT)
// Uncomment after you've finalized your AUTO_SHIFT_TIMEOUT value
// Saves a small amount of firmware space
// #define AUTO_SHIFT_NO_SETUP

// ==================== TAP-HOLD CONFIGURATION ====================

// Tapping Term - Milliseconds to distinguish tap from hold
// Default: 200ms
// Lower values: Faster response, easier to trigger hold accidentally
// Higher values: More forgiving, but slower hold activation
#define TAPPING_TERM 200

// Permissive Hold - Trigger hold if another key is tapped during tapping term
// Essential for home row mods and fast typing
// Example: Hold A (LSFT_T), tap B → Result: Shift+B (not ab)
// Without this: Hold A, tap B → Result: ab (if released within TAPPING_TERM)
#define PERMISSIVE_HOLD

// Per-key Permissive Hold - Allow selective enabling per key
// Enable this to use get_permissive_hold() callback for granular control
// #define PERMISSIVE_HOLD_PER_KEY

// Tapping Force Hold - Prevent accidental holds when rapidly tapping same key
// If you tap a key, release it, and hold it again (double-tap-hold),
// this forces tap action on second press unless TAPPING_TERM expires
// Useful for preventing accidental holds on repeated keys
#define TAPPING_FORCE_HOLD

// Quick Tap Term - Milliseconds for quick tap repeat
// If you press a dual-role key, release, then press again within this time,
// it always taps (ignores hold). Useful for double-tapping letters.
// Default: TAPPING_TERM (200ms)
// Set to 0 to disable
#define QUICK_TAP_TERM 120

// Retro Tapping - Send tap keycode on release if no other key was pressed
// If you hold a tap-hold key, don't press any other key, then release it,
// this will send the tap keycode even if you held it past TAPPING_TERM
// Useful for modifier keys that can also be tapped (like Shift on Enter)
// #define RETRO_TAPPING

// ==================== SWAP HANDS CONFIGURATION ====================

// Swap Hands - Mirror keyboard for one-handed typing
// Enables SH_* keycodes to swap left/right halves
// Default: Off (normal typing with both hands)
// Can be toggled with SH_TOGG or held with SH_MON

// Tap-toggle count - Number of taps to toggle swap hands
// Default: TAPPING_TOGGLE (usually 5)
// Tapping SH_TT this many times will toggle swap hands on/off
// #define SWAP_HANDS_TAPPING_TOGGLE 5  // Uncomment to customize

// ==================== UNICODE CONFIGURATION ====================

// Unicode Selected Modes - Limit which modes can be cycled through
// Modes: UNICODE_MODE_LINUX, UNICODE_MODE_WINDOWS, UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_MACOS
// Defining this list restricts UC_NEXT/UC_PREV to only these modes
// OS detection will auto-set the initial mode; UC_NEXT/UC_PREV cycle through these
#define UNICODE_SELECTED_MODES \
    UNICODE_MODE_LINUX, \
    UNICODE_MODE_WINDOWS, \
    UNICODE_MODE_WINCOMPOSE, \
    UNICODE_MODE_MACOS

// Unicode Cycle Persist - Remember last used Unicode mode across reboots
// Default: true (saves mode to EEPROM)
// Set to false to always start with first mode in UNICODE_SELECTED_MODES
#define UNICODE_CYCLE_PERSIST false

// Type delay - Milliseconds between Unicode sequence keystrokes
// Default: 10ms
// Increase if characters aren't typed correctly
#define UNICODE_TYPE_DELAY 10

// ==================== RAW HID CONFIGURATION ====================

// Raw HID Usage Page (default: 0xFF60 - Vendor-defined)
// Standard QMK default works with most tools
//OK//#define RAW_USAGE_PAGE 0xFF60

// Raw HID Usage ID (default: 0x61)
// Standard QMK default works with most tools
//OK//#define RAW_USAGE_ID 0x61

// Raw HID Report Size (default: 32 bytes)
// Size of each HID report sent/received
// Default 32 is standard for compatibility
// Increase if you need larger data payloads (uses more RAM)
//OK//#define RAW_EPSIZE 32

// ==================== LEADER KEY CONFIGURATION ====================

// Leader Key timeout - Total time from pressing Leader to complete sequence
// Default: 300ms (fast typing required)
// Recommended: 500-1000ms for comfortable use
// Set to 0 with LEADER_NO_TIMEOUT for unlimited time
//#define LEADER_TIMEOUT 1000
#define LEADER_TIMEOUT 800

// Per-key timing - Reset timeout after each key in sequence
// Without this: Total time for entire sequence = LEADER_TIMEOUT
// With this: Each key gets LEADER_TIMEOUT to be pressed
// Recommended for longer sequences
#define LEADER_PER_KEY_TIMING

// No timeout - Disable timeout entirely (wait forever for sequence)
// Uncomment if you want unlimited time to complete sequences
// With this enabled, LEADER_TIMEOUT is ignored
// #define LEADER_NO_TIMEOUT

// Strict key processing - Only process defined sequences
// Prevents accidental keypresses from leaking through
// Recommended: Enabled for cleaner behavior
#define LEADER_KEY_STRICT_KEY_PROCESSING

// ==================== ONE-SHOT KEYS CONFIGURATION ====================

// One-shot key timeout - Release after this time (milliseconds)
// Default: 5000ms (5 seconds)
// Tap a one-shot key, then you have 5 seconds to press another key
// If no key is pressed, the one-shot is released automatically
#define ONESHOT_TIMEOUT 5000

// Tap-to-toggle threshold - Tap this many times to toggle on/off
// Default: 5 taps
// Example: Tap OSM(MOD_LSFT) 5 times quickly = toggle normal shift mode
// Tap once: One-shot shift for next key
// Tap 5 times: Shift stays on until tapped again
#define ONESHOT_TAP_TOGGLE 5

// Tap-toggle behavior:
// - ONESHOT_TAP_TOGGLE = 0: Disabled (no tap-toggle)
// - ONESHOT_TAP_TOGGLE = 2: Fast double-tap toggles
// - ONESHOT_TAP_TOGGLE = 5: Recommended (5 taps to toggle)

// ==================== SENTENCE CASE CONFIGURATION ====================

// Sentence Case: Automatically capitalize first letter of sentences
// Requires: One-shot keys (enabled by default)
// DO NOT define NO_ACTION_ONESHOT or this will not work

// Idle timeout - Reset state after 5 seconds of inactivity
// Default: 5000ms (5 seconds)
// Set to 0 to never timeout
//OK//#define SENTENCE_CASE_TIMEOUT 5000

// Buffer size - Maximum pattern length for abbreviation detection
// Default: 8 keys
// Increase if you need longer abbreviation patterns (e.g., "e.g.")
//OK//#define SENTENCE_CASE_BUFFER_SIZE 8

// ==================== DEFERRED EXECUTION CONFIGURATION ====================

// Maximum number of deferred executor callbacks that can be scheduled
// Default: 8 callbacks
// You are using:
//   - 1 callback for OS detection (configure_unicode_mode)
//   - Potential callbacks for other deferred tasks
// Recommended: 16 for sufficient headroom
#define MAX_DEFERRED_EXECUTORS 16

// ==================== DYNAMIC MACRO CONFIGURATION ====================

// Dynamic macro buffer size (total keypresses for both macros)
// Default: 128 keypresses shared between Macro 1 and Macro 2
// Increase if you need longer macros (consumes RAM)
#define DYNAMIC_MACRO_SIZE 256

// Delay between each keypress during macro playback (milliseconds)
// Default: None (0ms = immediate, back-to-back keypresses)
// Recommended: 10-50ms for most typing macros
// Higher values: Slower playback, more compatible with some software
// Lower values: Faster playback, useful for gaming
// #define DYNAMIC_MACRO_DELAY 20
#define DYNAMIC_MACRO_DELAY 10  // 10ms between keys
// Good balance between speed and compatibility

// Optional: Disable nested macros (call one macro from another)
// Saves a small amount of code space
// #define DYNAMIC_MACRO_NO_NESTING

// ==================== VIAL DYNAMIC FEATURE MEMORY ALLOCATION ====================

#define VIAL_ENABLE_SETTINGS

// Combos - Chording solution (press multiple keys simultaneously for action)
// Default: Auto-calculated based on EEPROM size
// Recommended: 16-32 for heavy chord users, 8 for casual use
#define VIAL_COMBO_ENTRIES 32

// Tap Dance - Tap key once for action A, twice for action B
// Default: Auto-calculated based on EEPROM size
// Recommended: 8-16 for most users
//OK//#define VIAL_TAP_DANCE_ENTRIES 16
#define VIAL_TAP_DANCE_ENTRIES 32

// Key Overrides - Modifier-based key remapping (Shift+Backspace=Delete)
// Default: Auto-calculated based on EEPROM size
// Recommended: 8-16 for most users
//OK//#define VIAL_KEY_OVERRIDE_ENTRIES 16
#define VIAL_KEY_OVERRIDE_ENTRIES 32

// Alt Repeat Key - Define alternate key behaviors for QK_AREP
// Example: After Right Arrow, QK_AREP performs Left Arrow
// Default: Auto-calculated based on EEPROM size
// Recommended: 8-16 mappings for most users, 32 for power users
#define VIAL_ALT_REPEAT_KEY_ENTRIES 32

// Dynamic Macros - Text/keystroke macros recorded in GUI
// Note: This is total macro buffer size, not number of macros
// DYNAMIC_KEYMAP_MACRO_COUNT controls number of macro slots
// Default: Auto-calculated based on EEPROM size
// Recommended: Leave undefined (auto) or 512-2048 bytes
// #define VIAL_MACRO_ENTRIES 512

//OK//#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
//OK//#define DYNAMIC_KEYMAP_LAYER_COUNT 16
//OK//#endif

// Enable persistent default layer changing
#define VIAL_ENABLE_LAYER_PERSISTENCE

// Enable layer locking and unlocking features if supported
#define VIAL_ENABLE_LAYER_LOCKING

// ==================== MOUSE KEY CONFIGURATION ====================

// Mouse cursor acceleration (default mode)
// Adjust these values for comfortable mouse control from keyboard
#define MOUSEKEY_INTERVAL        7   // Time between cursor movements (ms)
#define MOUSEKEY_DELAY           0   // Delay before cursor starts moving (ms)
#define MOUSEKEY_TIME_TO_MAX     60  // Time until max speed is reached
#define MOUSEKEY_MAX_SPEED       8   // Maximum cursor speed
#define MOUSEKEY_MOVE_DELTA      1   // Acceleration increment

// Mouse wheel settings
#define MOUSEKEY_WHEEL_DELAY     0   // Delay before wheel starts (ms)
#define MOUSEKEY_WHEEL_INTERVAL  76  // Time between wheel movements (ms)

// ==================== QMK KEYS PER SCAN ====================

// Allows sending more than one key per scan
// Default: 1 key event per scan cycle
// Useful for: Fast typing, chording, simultaneous keypresses
// Recommended: 4 for heavy chording, 8-12 for gaming/combos
//OK//#define QMK_KEYS_PER_SCAN 4

// ==================== NKRO CONFIGURATION ====================
// NKRO is ENABLED in rules.mk but NOT forced on boot
// Keyboard starts in 6KRO mode (6-key rollover) for maximum compatibility
// Use NK_TOGG keycode to enable NKRO when needed
// NKRO state persists across power cycles

// NKRO Default On - Set to false
// Keyboard boots in 6KRO mode (6-key rollover + modifiers)
// User can press NK_TOGG to enable NKRO if needed
#define NKRO_DEFAULT_ON false

// DO NOT add #define FORCE_NKRO here

// Reconfigure Command to use Left Ctrl + Right Ctrl (instead of both shifts)
// This prevents conflict with BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#ifdef COMMAND_ENABLE
#define IS_COMMAND() (get_mods() == MOD_MASK_CTRL)
#endif

// ==================== CAPS WORD CONFIGURATION ====================

// Activate Caps Word by pressing Left Shift + Right Shift simultaneously
// Works with KC_LSFT/KC_RSFT, one-shot shifts, and Space Cadet shifts
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

// Caps Word idle timeout (default: 5000ms = 5 seconds)
// Auto-disables if no keys pressed for this duration
// Set to 0 to never timeout
#define CAPS_WORD_IDLE_TIMEOUT 5000

// ==================== DYNAMIC KEYMAP CONFIGURATION ====================

// Increase number of macros available in Vial GUI (default: 16)
// Increased to 32 for extended macro use
// RP2040 has sufficient space for 32-128 macros
#define DYNAMIC_KEYMAP_MACRO_COUNT 32  // or 40, 64, 128, etc.

// ==================== LAYER LOCK CONFIGURATION ====================

// Layer Lock idle timeout - automatically unlock if no keypresses for 6 seconds
// Useful to avoid confusion if you step away with a layer locked
// Time in milliseconds: 5000ms = 5 seconds
#define LAYER_LOCK_IDLE_TIMEOUT 5000

// ==================== SPLIT KEYBOARD CONFIGURATION ====================

// Serial communication
// Communication transport for split keyboard
// Use 'serial' for RP2040 controllers connected via TRRS cable
//OK//#define SPLIT_TRANSPORT               SERIAL

// Serial communication pin (UART)
// Adjust based on your RP2040's UART pin configuration
// Common pins: GP0, GP1, GP4, GP5, etc.
//#define SOFT_SERIAL_PIN               GP12  // TX pin on UART0 (pin 15)
                                            //
// Handedness detection
// EE_HANDS: Eeprom-based handedness (requires programming each side separately)
// MASTER_LEFT: Left side is always master (requires USB always on left)
// MASTER_RIGHT: Right side is always master (requires USB always on right)
// #define SPLIT_HAND_PIN                GP21  // Hand detection pin, adjust based on your wiring

// Configure GP19 as input with pull-up for stable hand detection
// GND on left half pulls LOW (detected as left)
// Floating on right half reads HIGH (detected as right)
//OK//#define SPLIT_HAND_PIN_LOW_IS_LEFT    true

// Debounce settings for split keyboard
// Reduce debounce for responsive split keyboard
#define DEBOUNCE                      5

// Master side designation
// Left side is the master (USB connected to left half)
// Right side connects to left via TRRS cable
#define MASTER_LEFT

// ==================== SPLIT SYNCHRONIZATION OPTIONS ====================

// LED State Sync - Sync host indicator LEDs (Caps/Num/Scroll Lock)
// Useful for displaying LED indicators on slave side
#define SPLIT_LED_STATE_ENABLE
// Already defined (keeping for reference)
//#define SPLIT_LED_STATE_SYNC          // Alias for SPLIT_LED_STATE_ENABLE

// Activity Sync - Sync activity timestamps between halves
// Enables proper timeout behavior on both sides
#define SPLIT_ACTIVITY_ENABLE

// Layer State Sync - Sync current layer to slave side
// Required for layer-dependent RGB effects on slave
#define SPLIT_LAYER_STATE_ENABLE

// Modifier State Sync (already enabled earlier as SPLIT_MODS_ENABLE)
// Keeps modifier state (Shift, Ctrl, Alt, GUI) synced
#define SPLIT_MODS_ENABLE

// Transport Mirror - Mirror master matrix to slave
// Useful for debugging, allows slave to "see" master keypresses
#define SPLIT_TRANSPORT_MIRROR

// ==================== SPLIT WATCHDOG & USB DETECTION ====================

// Watchdog - Auto-reboot slave if no communication from master
// Prevents both sides becoming slaves (common issue on some systems)
//OK//#define SPLIT_WATCHDOG_ENABLE

// Watchdog timeout - Reboot slave after 3 seconds of no master communication
#define SPLIT_WATCHDOG_TIMEOUT 3000

// USB Detection - Detect master via active USB communication
// More reliable than VBUS detection on some systems
#define SPLIT_USB_DETECT

// USB detection poll frequency - Check every 10ms
#define SPLIT_USB_TIMEOUT_POLL 10

// USB detection timeout - Maximum wait time for USB detection
#define SPLIT_USB_TIMEOUT 2000

// ==================== SPLIT MISC ====================

// Watchdog timer for split communication recovery
#define SPLIT_WDT_WINDOW_MS           100

//#define SPLIT_OLED_ENABLE             // (Enable if you have OLEDs)

// ==================== RGB MATRIX CONFIGURATION ====================

// USB Suspend - Disable RGB when USB is suspended (computer sleeps)
#define RGB_DISABLE_WHEN_USB_SUSPENDED

// Default RGB settings on boot
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_UP_DOWN  // Boot with vertical gradient
#define RGB_MATRIX_DEFAULT_ON true                           // RGB enabled on boot

// Reactive effects - Respond to keypresses and releases
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS   // Enable framebuffer-based effects (typing heatmap, etc.)
#define RGB_MATRIX_KEYPRESSES             // Effects trigger on key press (default)
#define RGB_MATRIX_KEYRELEASES            // Effects also trigger on key release

// Layer behavior - Allow layer to override RGB off state
// When a layer has custom RGB, it overrides the "RGB off" setting
#define RGB_MATRIX_LAYERS_OVERRIDE_RGB_OFF

// LED count and split configuration
#define RGB_MATRIX_LED_COUNT 46          // Total LEDs: 46 (23 per side)
#define RGB_MATRIX_SPLIT { 23, 23 }      // 23 LEDs on left, 23 on right

// Sleep and timeout behavior
#define RGB_MATRIX_SLEEP                 // Turn off RGB when suspended
#define RGB_MATRIX_TIMEOUT 300000        // Auto-off after 5 minutes (300,000ms)

// Trigger behavior - Keypress triggers RGB immediately (more responsive)
#define RGB_TRIGGER_ON_KEYDOWN

// USB wake delay - Wait 200ms after USB resume before enabling RGB
// Prevents issues with some USB hubs/ports
#define USB_SUSPEND_WAKEUP_DELAY 200

// ==================== RGB MATRIX PERFORMANCE ====================

// Process 10 LEDs per animation frame (46 total / 5 = ~10)
// Balances animation smoothness vs keyboard responsiveness
#define RGB_MATRIX_LED_PROCESS_LIMIT 10

// Update LEDs at 60fps max (16ms = 1000ms / 60fps)
// Reduces USB bandwidth usage
#define RGB_MATRIX_LED_FLUSH_LIMIT 16

// ==================== RGB MATRIX COLOR DEFAULTS ====================

// Already set in rules.mk, documenting here for reference:
// RGB_MATRIX_DEFAULT_MODE = RGB_MATRIX_GRADIENT_UP_DOWN
// RGB_MATRIX_DEFAULT_SPD = 127

// Optional: Set default brightness (0-255)
// #define RGB_MATRIX_DEFAULT_VAL 128

// Optional: Maximum brightness limit (saves power)
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200

// ==================== RGB MATRIX + PALETTEFX CONFIGURATION ====================

// PaletteFx uses the hue setting to select palettes
// Standard RGB_MATRIX_HUE_STEP applies (default 8)
// 16 palettes available via hue adjustment (RM_HUEU/RM_HUED)

// Optional: Disable shared RGB keycodes to avoid conflicts
//#define RGB_MATRIX_DISABLE_SHARED_KEYCODES

//OK//#define PALETTEFX_ENABLE_ALL_EFFECTS  // cycle with RM_NEXT/RM_PREV
//OK//#define PALETTEFX_ENABLE_ALL_PALETTES // cycle with RM_HUEU/RM_HUED

