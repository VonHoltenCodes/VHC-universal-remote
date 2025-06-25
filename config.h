/*
 * VHC Universal Remote - Configuration
 * Hardware pin definitions and system constants
 */

#ifndef CONFIG_H
#define CONFIG_H

// Display pins (ILI9341)
#define TFT_CS   10  // Chip select
#define TFT_DC   9   // Data/Command
#define TFT_MOSI 11  // SPI MOSI
#define TFT_SCK  13  // SPI Clock
#define TFT_MISO 12  // SPI MISO
#define TFT_RST  14  // Reset
#define TFT_LED  15  // Backlight control

// Touch controller pins (XPT2046)
#define TOUCH_CS 8   // Touch chip select

// IR LED pin
#define IR_LED   6   // Connected through transistor

// SD Card (uses Teensy built-in slot)
#define SD_CS    BUILTIN_SDCARD

// Display dimensions
#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

// Touch calibration values (adjust after testing)
#define TS_MINX 200
#define TS_MAXX 3800
#define TS_MINY 200
#define TS_MAXY 3800

// UI Color scheme (red-on-black terminal style)
#define COLOR_BACKGROUND ILI9341_BLACK
#define COLOR_TEXT       ILI9341_RED
#define COLOR_BUTTON     ILI9341_RED
#define COLOR_BUTTON_TEXT ILI9341_WHITE
#define COLOR_DISABLED   ILI9341_DARKGREY

// Timing constants
#define SPLASH_DURATION  5000  // 5 seconds
#define SPLASH_ANIMATION 2000  // 2 second logo animation
#define REPEAT_DELAY     200   // Button repeat delay in ms
#define DEBOUNCE_DELAY   50    // Touch debounce

// Menu configuration
#define DEVICES_PER_PAGE 4
#define MAX_DEVICES      20
#define MAX_COMMANDS     10

// File paths (IRDB format only)
#define CONFIG_FILE      "config.txt"

// Debug settings
#define DEBUG_SERIAL     1    // Enable serial debug output
#define DEBUG_TOUCH      0    // Show touch coordinates
#define DEBUG_IR         0    // Show IR codes being sent

// Logo style selection (0=Block text, 1=Modern, 2=Minimal, 3=Graphical blocks)
#define LOGO_STYLE       3    // Change this to select different logo styles

#endif // CONFIG_H