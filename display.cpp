/*
 * VHC Universal Remote - Display Module Implementation
 */

#include "display.h"
#include "ascii_art.h"

Display::Display() {
  tft = new Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
  currentTextSize = 1;
  currentTextColor = COLOR_TEXT;
}

void Display::begin() {
  pinMode(TFT_LED, OUTPUT);
  setBacklight(255);
  
  tft->begin();
  tft->setRotation(1); // Landscape mode
  clear();
}

void Display::clear() {
  tft->fillScreen(COLOR_BACKGROUND);
}

void Display::drawText(int x, int y, const char* text, uint16_t color, int size) {
  tft->setCursor(x, y);
  tft->setTextColor(color);
  tft->setTextSize(size);
  tft->print(text);
}

void Display::drawCenteredText(int y, const char* text, uint16_t color, int size) {
  int16_t x1, y1;
  uint16_t w, h;
  tft->setTextSize(size);
  tft->getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
  int x = (SCREEN_WIDTH - w) / 2;
  drawText(x, y, text, color, size);
}

void Display::drawButton(int x, int y, int w, int h, const char* label, bool pressed) {
  uint16_t bgColor = pressed ? COLOR_BUTTON_TEXT : COLOR_BACKGROUND;
  uint16_t fgColor = pressed ? COLOR_BUTTON : COLOR_TEXT;
  uint16_t borderColor = COLOR_TEXT;
  
  // Clear button area
  tft->fillRect(x, y, w, h, bgColor);
  
  // Draw button border with ASCII style
  drawBorder(x, y, w, h, borderColor);
  
  // Center the label in the button
  int16_t x1, y1;
  uint16_t tw, th;
  tft->setTextSize(1);
  tft->getTextBounds(label, 0, 0, &x1, &y1, &tw, &th);
  
  int textX = x + (w - tw) / 2;
  int textY = y + (h - th) / 2;
  drawText(textX, textY, label, fgColor, 1);
}

void Display::drawBorder(int x, int y, int w, int h, uint16_t color) {
  // Draw ASCII-style border
  // Top line
  tft->drawFastHLine(x + 1, y, w - 2, color);
  // Bottom line
  tft->drawFastHLine(x + 1, y + h - 1, w - 2, color);
  // Left line
  tft->drawFastVLine(x, y + 1, h - 2, color);
  // Right line
  tft->drawFastVLine(x + w - 1, y + 1, h - 2, color);
  
  // Corners
  tft->drawPixel(x, y, color);                    // Top-left
  tft->drawPixel(x + w - 1, y, color);           // Top-right
  tft->drawPixel(x, y + h - 1, color);           // Bottom-left
  tft->drawPixel(x + w - 1, y + h - 1, color);   // Bottom-right
}

void Display::drawHeader() {
  // VHC branding on left
  drawText(10, 10, "VHC", COLOR_TEXT, 2);
  drawText(10, 30, "===", COLOR_TEXT, 1);
  drawText(10, 40, "UR", COLOR_TEXT, 2);
  
  // POWER button on right
  drawPowerButton(false);
}

void Display::drawPowerButton(bool pressed) {
  int x = 240;
  int y = 10;
  int w = 70;
  int h = 30;
  
  drawButton(x, y, w, h, "POWER", pressed);
}

void Display::drawSplashScreen() {
  clear();
  
  // Draw large ASCII VHC logo centered
  const char* logo[] = {
    " _   _ _   _ _____ ",
    "| | | | | | |  __ \\",
    "| | | | |_| | |  \\/",
    "| | | |  _  | |    ",
    "\\ \\_/ / | | | |____",
    " \\___/\\_| |_/\\____/"
  };
  
  int logoY = 30;
  for (int i = 0; i < 6; i++) {
    drawCenteredText(logoY + (i * 10), logo[i], COLOR_TEXT, 1);
  }
  
  drawCenteredText(100, "UNIVERSAL REMOTE", COLOR_TEXT, 2);
  
  drawCenteredText(140, "Created by Trent Von Holten", COLOR_TEXT, 1);
  
  drawCenteredText(180, "Loading...", COLOR_TEXT, 1);
}

void Display::updateLoadingAnimation(int frame) {
  // Simple loading dots animation
  const char* loadingFrames[] = {
    "Loading   ",
    "Loading.  ",
    "Loading.. ",
    "Loading..."
  };
  
  // Clear loading area
  tft->fillRect(0, 180, SCREEN_WIDTH, 20, COLOR_BACKGROUND);
  
  // Draw current frame
  drawCenteredText(180, loadingFrames[frame % 4], COLOR_TEXT, 1);
}

void Display::drawMainMenu(const char* devices[], int count, int currentPage, int totalPages) {
  clear();
  drawHeader();
  
  drawText(10, 70, "Devices:", COLOR_TEXT, 1);
  
  // Draw device buttons
  int buttonY = 90;
  for (int i = 0; i < count && i < DEVICES_PER_PAGE; i++) {
    drawButton(20, buttonY + (i * 35), 200, 30, devices[i], false);
  }
  
  // Navigation buttons
  if (totalPages > 1) {
    if (currentPage < totalPages - 1) {
      drawButton(20, 220, 80, 20, "Next >", false);
    }
    drawButton(240, 220, 70, 20, "Back", false);
  }
}

void Display::drawDeviceMenu(const char* deviceName) {
  clear();
  drawHeader();
  
  // Device name
  char title[40];
  snprintf(title, 40, "Device: %s", deviceName);
  drawText(10, 70, title, COLOR_TEXT, 1);
  
  // Control buttons
  drawButton(20, 100, 200, 30, "Volume", false);
  drawButton(20, 140, 200, 30, "Channel", false);
  drawButton(20, 180, 200, 30, "Input", false);
  
  // Back button
  drawButton(240, 220, 70, 20, "Back", false);
}

void Display::drawVolumeMenu() {
  clear();
  drawHeader();
  
  drawText(10, 70, "Volume Control", COLOR_TEXT, 1);
  
  // Volume up button with arrow
  tft->fillRect(20, 100, 200, 30, COLOR_BACKGROUND);
  drawBorder(20, 100, 200, 30, COLOR_TEXT);
  drawText(30, 110, "Vol Up", COLOR_TEXT, 1);
  // Draw up arrow using triangle
  drawUpArrow(185, 115, COLOR_TEXT);
  
  // Volume down button with arrow
  tft->fillRect(20, 150, 200, 30, COLOR_BACKGROUND);
  drawBorder(20, 150, 200, 30, COLOR_TEXT);
  drawText(30, 160, "Vol Down", COLOR_TEXT, 1);
  // Draw down arrow using triangle
  drawDownArrow(185, 165, COLOR_TEXT);
  
  // Back button
  drawButton(240, 220, 70, 20, "Back", false);
}

void Display::drawChannelMenu() {
  clear();
  drawHeader();
  
  drawText(10, 70, "Channel Control", COLOR_TEXT, 1);
  
  // Channel up button with arrow
  tft->fillRect(20, 100, 200, 30, COLOR_BACKGROUND);
  drawBorder(20, 100, 200, 30, COLOR_TEXT);
  drawText(30, 110, "Ch Up", COLOR_TEXT, 1);
  drawUpArrow(185, 115, COLOR_TEXT);
  
  // Channel down button with arrow
  tft->fillRect(20, 150, 200, 30, COLOR_BACKGROUND);
  drawBorder(20, 150, 200, 30, COLOR_TEXT);
  drawText(30, 160, "Ch Down", COLOR_TEXT, 1);
  drawDownArrow(185, 165, COLOR_TEXT);
  
  // Back button
  drawButton(240, 220, 70, 20, "Back", false);
}

void Display::drawErrorScreen(const char* message) {
  clear();
  
  drawCenteredText(60, "ERROR", COLOR_TEXT, 3);
  drawCenteredText(120, message, COLOR_TEXT, 1);
  drawCenteredText(180, "Please check SD card", COLOR_TEXT, 1);
}

void Display::setBacklight(uint8_t brightness) {
  analogWrite(TFT_LED, brightness);
}

void Display::showMessage(const char* message, int duration) {
  // Save current screen area where message will be displayed
  int msgY = SCREEN_HEIGHT - 30;
  
  // Draw message box
  tft->fillRect(10, msgY, SCREEN_WIDTH - 20, 25, COLOR_BUTTON);
  tft->drawRect(10, msgY, SCREEN_WIDTH - 20, 25, COLOR_TEXT);
  
  // Draw message
  drawCenteredText(msgY + 8, message, COLOR_BUTTON_TEXT, 1);
  
  // Note: Caller is responsible for restoring screen after duration
}

void Display::drawUpArrow(int x, int y, uint16_t color) {
  // Draw triangle pointing up
  tft->fillTriangle(x, y - 5, x - 5, y + 5, x + 5, y + 5, color);
}

void Display::drawDownArrow(int x, int y, uint16_t color) {
  // Draw triangle pointing down
  tft->fillTriangle(x, y + 5, x - 5, y - 5, x + 5, y - 5, color);
}