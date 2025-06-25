/*
 * VHC Universal Remote - ASCII Art Assets
 * All visual text elements for the retro terminal UI
 */

#ifndef ASCII_ART_H
#define ASCII_ART_H

// Small logo for menu corners (3x3)
const char* LOGO_SMALL[] = {
  "VHC",
  "===", 
  "UR "
};

// Medium logo for splash screen (23x6)
const char* LOGO_MEDIUM[] = {
  "  _   _ _   _ _____   ",
  " | | | | | | |  __ \\  ",
  " | | | | |_| | |  \\/  ",
  " | | | |  _  | |      ",
  " \\ \\_/ / | | | |____  ",
  "  \\___/\\_| |_/\\____/  "
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

// Button state indicators
const char* BUTTON_PRESS = "[X]";
const char* BUTTON_NORMAL = "[ ]";

// Arrow symbols for volume/channel
const char* ARROW_UP = "^";
const char* ARROW_DOWN = "v";
const char* ARROW_LEFT = "<";
const char* ARROW_RIGHT = ">";

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

// Decorative borders
const char* BORDER_TOP =    "================================";
const char* BORDER_BOTTOM = "================================";
const char* BORDER_SINGLE = "--------------------------------";

// Error messages with style
const char* ERROR_NO_SD = "! INSERT SD CARD !";
const char* ERROR_NO_DEVICES = "! NO DEVICES FOUND !";
const char* ERROR_READ_FAIL = "! FILE READ ERROR !";

// Menu headers
const char* HEADER_DEVICES = "DEVICES:";
const char* HEADER_VOLUME = "VOLUME CONTROL";
const char* HEADER_CHANNEL = "CHANNEL CONTROL";
const char* HEADER_SETTINGS = "SETTINGS";

// Button labels with padding for consistent sizing
const char* LABEL_POWER = "POWER";
const char* LABEL_BACK = "BACK";
const char* LABEL_NEXT = "NEXT>";
const char* LABEL_PREV = "<PREV";
const char* LABEL_VOL_UP = "VOL+";
const char* LABEL_VOL_DN = "VOL-";
const char* LABEL_CH_UP = "CH+";
const char* LABEL_CH_DN = "CH-";
const char* LABEL_INPUT = "INPUT";
const char* LABEL_MENU = "MENU";
const char* LABEL_OK = "OK";

// Fun retro computer messages for splash
const char* RETRO_MESSAGES[] = {
  "SYSTEM READY",
  "INITIALIZING IR SUBSYSTEM",
  "LOADING DEVICE CODES",
  "CALIBRATING PHOTONS",
  "ENGAGING REMOTE CONTROL"
};

// Device type icons (5x3 mini icons)
const char* ICON_TV[] = {
  "+---+",
  "| o |",
  "+---+"
};

const char* ICON_AUDIO[] = {
  " ||| ",
  "(( ))",
  " ||| "
};

const char* ICON_DISC[] = {
  " ___ ",
  "( o )",
  " --- "
};

// Progress bar elements
const char PROGRESS_EMPTY = '.';
const char PROGRESS_FULL = '=';
const char PROGRESS_START = '[';
const char PROGRESS_END = ']';

// Special characters for terminal feel
const char PROMPT = '>';
const char CURSOR_BLOCK = 219; // █
const char CURSOR_LINE = '_';

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