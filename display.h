/*
 * VHC Universal Remote - Display Module
 * Handles all screen drawing and UI rendering
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "config.h"
#include "ascii_art.h"
#include "ui_icons.h"
#include "logo_graphics.h"

class Display {
private:
  Adafruit_ILI9341* tft;
  int currentTextSize;
  uint16_t currentTextColor;
  
public:
  Display();
  void begin();
  void clear();
  
  // Basic drawing functions
  void drawText(int x, int y, const char* text, uint16_t color = COLOR_TEXT, int size = 1);
  void drawCenteredText(int y, const char* text, uint16_t color = COLOR_TEXT, int size = 1);
  void drawButton(int x, int y, int w, int h, const char* label, bool pressed = false);
  void drawBorder(int x, int y, int w, int h, uint16_t color);
  void drawHeader();
  void drawPowerButton(bool pressed = false);
  
  // Screen-specific drawing functions
  void drawSplashScreen();
  void drawMainMenu(const char* devices[], int deviceCount, int page, int totalPages);
  void drawDeviceMenu(const char* deviceName);
  void drawVolumeMenu();
  void drawChannelMenu();
  void drawErrorScreen(const char* message);
  
  // UI element helpers
  void updateLoadingAnimation(int frame);
  void drawUpArrow(int x, int y, uint16_t color);
  void drawDownArrow(int x, int y, uint16_t color);
  
  // Utility functions
  void setBacklight(uint8_t brightness);
  void showMessage(const char* message, int duration = 2000);
  
  // Get the display object for direct drawing
  Adafruit_ILI9341* getDisplay() { return tft; }
};

#endif // DISPLAY_H