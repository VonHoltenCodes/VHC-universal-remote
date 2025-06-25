/*
 * VHC Universal Remote - Display Module Implementation
 */

#include "display.h"

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
  uint16_t bgColor = pressed ? COLOR_BUTTON_TEXT : COLOR_BUTTON;
  uint16_t fgColor = pressed ? COLOR_BUTTON : COLOR_BUTTON_TEXT;
  
  tft->fillRect(x, y, w, h, bgColor);
  tft->drawRect(x, y, w, h, COLOR_TEXT);
  
  // Center the label in the button
  int16_t x1, y1;
  uint16_t tw, th;
  tft->setTextSize(2);
  tft->getTextBounds(label, 0, 0, &x1, &y1, &tw, &th);
  
  int textX = x + (w - tw) / 2;
  int textY = y + (h - th) / 2;
  drawText(textX, textY, label, fgColor, 2);
}

void Display::drawLogo(int x, int y, bool small) {
  if (small) {
    for (int i = 0; i < 3; i++) {
      drawText(x, y + (i * 8), LOGO_SMALL[i], COLOR_TEXT, 1);
    }
  } else {
    for (int i = 0; i < 6; i++) {
      drawText(x, y + (i * 10), LOGO_MEDIUM[i], COLOR_TEXT, 1);
    }
  }
}

void Display::drawSplashScreen() {
  clear();
  
  // Draw large logo centered
  drawLogo(getCenteredX(LOGO_MEDIUM[0], SCREEN_WIDTH), 20, false);
  
  // Draw title
  drawCenteredText(90, SPLASH_TITLE, COLOR_TEXT, 2);
  
  // Draw creator credit
  drawCenteredText(140, SPLASH_CREATOR, COLOR_TEXT, 1);
  
  // Draw loading text
  drawCenteredText(180, SPLASH_LOADING, COLOR_TEXT, 1);
}

void Display::drawMainMenu(const char* devices[], int deviceCount, int page, int totalPages) {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button
  drawPowerButton();
  
  // Draw header
  drawText(10, 40, HEADER_DEVICES, COLOR_TEXT, 2);
  
  // Draw device buttons
  int startIdx = page * DEVICES_PER_PAGE;
  for (int i = 0; i < DEVICES_PER_PAGE && (startIdx + i) < deviceCount; i++) {
    drawButton(20, 60 + (i * 40), 200, 30, devices[startIdx + i]);
  }
  
  // Draw navigation buttons
  if (page < totalPages - 1) {
    drawButton(220, 60, 80, 30, LABEL_NEXT);
  }
  
  // Draw back button (disabled)
  tft->fillRect(20, 220, 80, 20, COLOR_DISABLED);
  tft->drawRect(20, 220, 80, 20, COLOR_DISABLED);
  drawText(40, 225, LABEL_BACK, COLOR_DISABLED, 1);
}

void Display::drawDeviceMenu(const char* deviceName) {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button
  drawPowerButton();
  
  // Draw device name
  char header[32];
  snprintf(header, sizeof(header), "Device: %s", deviceName);
  drawText(10, 40, header, COLOR_TEXT, 2);
  
  // Draw control buttons
  drawButton(20, 60, 120, 30, "Volume");
  drawButton(20, 100, 120, 30, "Channel");
  drawButton(20, 140, 120, 30, LABEL_INPUT);
  
  // Draw back button
  drawBackButton(true);
}

void Display::drawVolumeMenu() {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button
  drawPowerButton();
  
  // Draw header
  drawCenteredText(40, HEADER_VOLUME, COLOR_TEXT, 2);
  
  // Draw volume buttons with arrows
  char volUp[16], volDn[16];
  snprintf(volUp, sizeof(volUp), "%s %s", LABEL_VOL_UP, ARROW_UP);
  snprintf(volDn, sizeof(volDn), "%s %s", LABEL_VOL_DN, ARROW_DOWN);
  
  drawButton(20, 60, 120, 30, volUp);
  drawButton(20, 100, 120, 30, volDn);
  
  // Draw back button
  drawBackButton(true);
}

void Display::drawChannelMenu() {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button
  drawPowerButton();
  
  // Draw header
  drawCenteredText(40, HEADER_CHANNEL, COLOR_TEXT, 2);
  
  // Draw channel buttons with arrows
  char chUp[16], chDn[16];
  snprintf(chUp, sizeof(chUp), "%s %s", LABEL_CH_UP, ARROW_UP);
  snprintf(chDn, sizeof(chDn), "%s %s", LABEL_CH_DN, ARROW_DOWN);
  
  drawButton(20, 60, 120, 30, chUp);
  drawButton(20, 100, 120, 30, chDn);
  
  // Draw back button
  drawBackButton(true);
}

void Display::drawErrorScreen(const char* message) {
  clear();
  
  // Draw error message in center of screen
  tft->drawRect(40, 80, 240, 80, COLOR_TEXT);
  drawCenteredText(110, message, COLOR_TEXT, 2);
}

void Display::drawPowerButton(bool pressed) {
  drawButton(240, 10, 70, 30, LABEL_POWER, pressed);
}

void Display::drawBackButton(bool enabled) {
  if (enabled) {
    drawButton(240, 220, 70, 20, LABEL_BACK);
  } else {
    tft->fillRect(240, 220, 70, 20, COLOR_DISABLED);
    tft->drawRect(240, 220, 70, 20, COLOR_DISABLED);
    drawText(255, 225, LABEL_BACK, COLOR_DISABLED, 1);
  }
}

void Display::drawProgressBar(int x, int y, int width, int progress, int total) {
  char bar[32];
  getProgressBar(bar, progress, total, width / 6); // Assuming 6 pixels per char
  drawText(x, y, bar, COLOR_TEXT, 1);
}

void Display::updateLoadingAnimation(int frame) {
  // Clear the loading area
  tft->fillRect(140, 180, 100, 20, COLOR_BACKGROUND);
  
  // Draw new frame
  drawCenteredText(180, LOADING_FRAMES[frame % 3], COLOR_TEXT, 1);
}

void Display::setBacklight(uint8_t brightness) {
  analogWrite(TFT_LED, brightness);
}

void Display::flash(uint16_t color, int duration) {
  tft->fillScreen(color);
  delay(duration);
  clear();
}