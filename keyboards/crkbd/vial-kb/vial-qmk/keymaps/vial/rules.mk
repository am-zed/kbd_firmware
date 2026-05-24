VIA_ENABLE         = yes
VIAL_ENABLE        = yes
VIALRGB_ENABLE     = yes
ENCODER_MAP_ENABLE = no
#SECURE_ENABLE      = yes

# disable unused features
#AUDIO_ENABLE           = no
#BACKLIGHT_ENABLE       = no
#BLUETOOTH_ENABLE       = no
#DIP_SWITCH_ENABLE      = no
#ENCODER_ENABLE         = no
#HD44780_ENABLE         = no
##IOS_DEVICE_ENABLE     = no
#LCD_BACKLIGHT_ENABLE   = no
#LCD_ENABLE             = no
#POINTING_DEVICE_ENABLE = no
#PS2_MOUSE_ENABLE       = no
#SLEEP_LED_ENABLE       = no
#STENO_ENABLE           = no
#DIGITIZER_ENABLE       = no
#WPM_ENABLE             = no
DEBUG_ENABLE           = no
#GERMAN_ENABLE          = no
#KEYLOGGER_ENABLE       = no
#AUTOLOG_ENABLE         = no
#AUTOCORRECT_ENABLE     = no

# Enable debug console for debug output
# Allows dprintf(), uprintf(), and debug macros to work
CONSOLE_ENABLE = no

# Optional: Enable command feature for magic key debug shortcuts
# Adds Magic+D toggle, Magic+E debug matrix, etc.
COMMAND_ENABLE = no

## NOTE: Conflicts with CAPS_WORD_ENABLE
## Key Lock feature - hold next pressed key until pressed again
KEY_LOCK_ENABLE    = yes

# Layer Lock feature - lock momentary layers in place
# Allows temporarily accessed layers (MO, LT, OSL) to stay active
LAYER_LOCK_ENABLE  = yes

# Terminal feature - run commands from keyboard
TERMINAL_ENABLE    = no

# Extra Keys - Media control and System control keycodes
# Enables volume up/down, play/pause, mute, wake, sleep, power, etc.
EXTRAKEY_ENABLE    = yes

# Repeat Key - Repeat last pressed key
# Enables QK_REP (Repeat) and QK_AREP (Alternate Repeat) keycodes
REPEAT_KEY_ENABLE  = yes

# Caps Word - Modern alternative to Caps Lock
# Auto-capitalizes letters, turns - into _, disables after word/idle
CAPS_WORD_ENABLE   = yes
#
# NKRO - N-Key Rollover
# Allows unlimited simultaneous keypresses (vs 6KRO default)
# Toggle at runtime with NK_TOGG keycode
NKRO_ENABLE        = yes

# Mouse Keys - Control mouse cursor and buttons from keyboard
# Allows cursor movement, mouse buttons, and scroll wheel
MOUSEKEY_ENABLE    = yes

# Key Overrides - Conditionally remap keys with modifiers
# Example: Shift + Backspace = Delete, Shift + Esc = ~
KEY_OVERRIDE_ENABLE = yes

# Programmable Buttons - 32 custom keys with no OS meaning
# Captured by custom software (Linux 5.14+: KEY_MACRO1-30)
# Useful for automation, scripting, custom macros
PROGRAMMABLE_BUTTON_ENABLE = no

# OS Detection - Auto-detect host OS (Windows/Linux/macOS/iOS)
# Detects OS based on USB setup packets
OS_DETECTION_ENABLE = yes

# Deferred Execution - Required for OS detection callbacks
# Allows delaying execution until OS is detected
DEFERRED_EXEC_ENABLE = yes

# Unicode Support - Type Unicode characters (emoji, symbols, etc.)
# Automatically configured based on detected OS
UNICODE_ENABLE = yes

# Dynamic Macros - Record and replay macros on-the-fly
# Two slots (Macro 1 and Macro 2), not persistent across reboots
# Default buffer: 128 keypresses total (configurable)
DYNAMIC_MACRO_ENABLE = yes

# One-Shot Keys - Tap to activate modifier for next key only
# Essential for Sentence Case functionality
# Enables: OSM(mod), OSL(layer)
ONESHOT_ENABLE     = yes

# Leader Key - Vim-style key sequences
# Allows up to 5-key sequences: Leader + key1 + key2 + ... = action
LEADER_ENABLE      = yes

# Raw HID - Bidirectional communication with host computer
# Allows sending/receiving data over HID interface
# Useful for custom utilities, configuration, metrics, etc.
RAW_ENABLE         = yes

# Swap Hands - Mirror keyboard for one-handed typing
# Allows swapping left/right halves (useful for accessibility/gaming)
SWAP_HANDS_ENABLE  = yes

# Auto Shift - Automatically capitalize letters when held longer
# Hold a key briefly = shifted (capital) version
# Reduces need for Shift key, improves ergonomics
AUTO_SHIFT_ENABLE  = yes

# Tri-Layer - Activate ADJUST layer when LOWER + UPPER held together
# Allows three layers with only two layer keys: LOWER, UPPER, and ADJUST (L+U)
TRI_LAYER_ENABLE   = yes

# Disable audio features
AUDIO_ENABLE = no
MUSIC_ENABLE = no

# Disable haptic feedback
HAPTIC_ENABLE = no

# Disable clicky mode (audio clicks on keypresses)
CLICKY_ENABLE = no

# Disable Link Time Optimization
# LTO can sometimes cause issues with certain toolchains or configurations
# Disable if you encounter compilation errors
LTO_ENABLE         = no
# or enable it (setting to yes not working)
#EXTRAFLAGS        += -flto=none

# Split keyboard configuration
# Corne Choc v4.1 uses two RP2040 MCUs connected via serial (TRRS cable)
SPLIT_KEYBOARD     = yes

# Disable OLED support (no OLED on this build - 2 extra keys instead)
OLED_ENABLE        = no
OLED_DRIVER        = none

# RGB Lighting Configuration
# Disable RGBLIGHT (underglow only)
RGBLIGHT_ENABLE    = no

# Enable RGB_MATRIX for per-key RGB control
RGB_MATRIX_ENABLE  = yes

