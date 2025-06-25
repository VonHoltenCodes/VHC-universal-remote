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
  void drawLogo(int x, int y, bool small = true);
  
  // Screen-specific drawing functions
  void drawSplashScreen();
  void drawMainMenu(const char* devices[], int deviceCount, int page, int totalPages);
  void drawDeviceMenu(const char* deviceName);
  void drawVolumeMenu();
  void drawChannelMenu();
  void drawErrorScreen(const char* message);
  
  // UI element helpers
  void drawPowerButton(bool pressed = false);
  void drawBackButton(bool enabled = true);
  void drawProgressBar(int x, int y, int width, int progress, int total);
  void updateLoadingAnimation(int frame);
  
  // Utility functions
  void setBacklight(uint8_t brightness);
  void flash(uint16_t color = ILI9341_WHITE, int duration = 50);
};

#endif // DISPLAY_H