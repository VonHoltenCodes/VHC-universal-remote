/*
 * VHC Universal Remote - ASCII Art Assets
 * Logos and visual text elements for the retro terminal UI
 */

#ifndef ASCII_ART_H
#define ASCII_ART_H

// Small logo for menu corners (3x3)
const char* LOGO_SMALL[] = {
  "VHC",
  "===", 
  "UR "
};

// Block-style logo using ASCII block characters
const char* LOGO_MEDIUM[] = {
  "██    ██ ██   ██  ████",
  "██    ██ ██   ██ ██   ",
  "██    ██ ███████ ██   ",
  " ██  ██  ██   ██ ██   ",
  "  ████   ██   ██  ████",
  "                      "
};

// Alternative block logo with more geometric style
const char* LOGO_MODERN[] = {
  "▌█▐ ▌█▐ ▌██▐",
  "▌█▐ ▌█▐ ▌█ ▐",
  "▌█████▐ ▌█ ▐",
  "▌ ███ ▐ ▌██▐",
  " REMOTE CTRL "
};

// Minimalist block logo
const char* LOGO_MINIMAL[] = {
  "▀▄   ▄▀ █ █ ▄▄▄",
  " ▀▄▄▄▀  █▄█ █  ",
  "  ▀█▀   █ █ ▀▀▀",
  "  VHC REMOTE   "
};

// Pure block design
const char* LOGO_BLOCKS[] = {
  "████ ████ ████",
  "█  █ █  █ █   ",
  "█  █ ████ █   ",
  "█  █ █  █ █   ",
  "████ █  █ ████",
  "              "
};

// Full splash screen text
const char* SPLASH_TITLE = "UNIVERSAL REMOTE";
const char* SPLASH_CREATOR = "Created by Trent Von Holten";
const char* SPLASH_LOADING = "Loading";

// Alternative compact logos for different screen sizes
const char* LOGO_COMPACT_1[] = {
  " VHC ",
  "[UR]"
};

const char* LOGO_COMPACT_2[] = {
  "VonHolten",
  " Codes   ",
  "Universal", 
  " Remote  "
};

// Stylized VHC for larger displays
const char* LOGO_LARGE[] = {
  "__      ___    _  _____ ",
  "\\ \\    / / |  | |/ ____|",
  " \\ \\  / /| |__| | |     ",
  "  \\ \\/ / |  __  | |     ",
  "   \\  /  | |  | | |____ ",
  "    \\/   |_|  |_|\\_____|"
};

// Loading animation frames (cycle through these)
const char* LOADING_FRAMES[] = {
  "Loading.  ",
  "Loading.. ",
  "Loading..."
};

// Alternative loading spinner
const char* SPINNER_FRAMES[] = {
  "[-]",
  "[\\]",
  "[|]", 
  "[/]"
};

// Error messages with style
const char* ERROR_NO_SD = "! INSERT SD CARD !";
const char* ERROR_NO_DEVICES = "! NO DEVICES FOUND !";
const char* ERROR_READ_FAIL = "! FILE READ ERROR !";

// Menu headers
const char* HEADER_DEVICES = "DEVICES:";
const char* HEADER_VOLUME = "VOLUME CONTROL";
const char* HEADER_CHANNEL = "CHANNEL CONTROL";
const char* HEADER_SETTINGS = "SETTINGS";

// Special characters for terminal feel
const char PROMPT = '>';
const char CURSOR_BLOCK = 219; // █
const char CURSOR_LINE = '_';

// Progress bar elements
const char PROGRESS_EMPTY = '.';
const char PROGRESS_FULL = '=';
const char PROGRESS_START = '[';
const char PROGRESS_END = ']';

// Function to get centered X position for text
inline int getCenteredX(const char* text, int screenWidth, int charWidth = 6) {
  int textWidth = strlen(text) * charWidth;
  return (screenWidth - textWidth) / 2;
}

// Function to draw a progress bar
inline void getProgressBar(char* buffer, int current, int total, int width = 20) {
  buffer[0] = PROGRESS_START;
  int filled = (current * (width - 2)) / total;
  for (int i = 1; i < width - 1; i++) {
    buffer[i] = (i <= filled) ? PROGRESS_FULL : PROGRESS_EMPTY;
  }
  buffer[width - 1] = PROGRESS_END;
  buffer[width] = '\0';
}

#endif // ASCII_ART_H