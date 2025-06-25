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

void Display::drawIconButton(int x, int y, int w, int h, void (*drawIcon)(Adafruit_GFX*, int, int, int, uint16_t), bool pressed) {
  uint16_t bgColor = pressed ? COLOR_BUTTON_TEXT : COLOR_BUTTON;
  uint16_t iconColor = pressed ? COLOR_BUTTON : COLOR_BUTTON_TEXT;
  
  tft->fillRect(x, y, w, h, bgColor);
  tft->drawRect(x, y, w, h, COLOR_TEXT);
  
  // Calculate icon position (centered)
  int iconSize = min(w, h) * 0.6; // Icon is 60% of button size
  int iconX = x + (w - iconSize) / 2;
  int iconY = y + (h - iconSize) / 2;
  
  // Draw the icon
  drawIcon(tft, iconX, iconY, iconSize, iconColor);
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

void Display::drawAnimatedLogo(int centerX, int centerY, int frame, int totalFrames) {
  // Calculate animation progress (0.0 to 1.0)
  float progress = (float)frame / (float)totalFrames;
  
  // Select logo based on config
  const char** selectedLogo = LOGO_MEDIUM;
  int logoLines = 6;
  
  #if LOGO_STYLE == 1
    selectedLogo = LOGO_MODERN;
    logoLines = 4;
  #elif LOGO_STYLE == 2
    selectedLogo = LOGO_MINIMAL;
    logoLines = 4;
  #endif
  
  // Logo dimensions
  int logoWidth = strlen(selectedLogo[0]) * 6; // 6 pixels per character
  int logoHeight = logoLines * 10; // 10 pixels per line
  
  // Starting positions (off screen)
  int leftStartX = -logoWidth;
  int rightStartX = SCREEN_WIDTH;
  
  // Final position
  int finalX = centerX - logoWidth / 2;
  
  // Calculate current positions with easing
  float easeProgress = 1.0f - pow(1.0f - progress, 3); // Cubic ease-out
  int topHalfX = leftStartX + (finalX - leftStartX) * easeProgress;
  int bottomHalfX = rightStartX + (finalX - rightStartX) * easeProgress;
  
  // Clear the logo area
  tft->fillRect(0, centerY - logoHeight/2, SCREEN_WIDTH, logoHeight, COLOR_BACKGROUND);
  
  int halfLines = logoLines / 2;
  
  // Draw top half sliding from left
  for (int i = 0; i < halfLines; i++) {
    drawText(topHalfX, centerY - logoHeight/2 + (i * 10), selectedLogo[i], COLOR_TEXT, 1);
  }
  
  // Draw bottom half sliding from right
  for (int i = halfLines; i < logoLines; i++) {
    drawText(bottomHalfX, centerY - logoHeight/2 + (i * 10), selectedLogo[i], COLOR_TEXT, 1);
  }
}

void Display::animateSplashScreen(int durationMs) {
  clear();
  
  // Animation parameters
  int totalFrames = 30; // 30 frames for smooth animation
  int frameDelay = durationMs / totalFrames;
  int logoY = 50; // Y position for logo
  
  #if LOGO_STYLE == 3  // Use graphical block logo
    // Animate the graphical logo
    for (int frame = 0; frame <= totalFrames; frame++) {
      LogoGraphics::drawAnimatedBlockLogo(tft, SCREEN_WIDTH / 2, logoY, frame, totalFrames, 3, COLOR_TEXT);
      delay(frameDelay);
    }
  #else
    // Animate the text-based logo
    for (int frame = 0; frame <= totalFrames; frame++) {
      drawAnimatedLogo(SCREEN_WIDTH / 2, logoY, frame, totalFrames);
      delay(frameDelay);
    }
  #endif
  
  // After animation, draw the rest of the splash screen
  drawCenteredText(90, SPLASH_TITLE, COLOR_TEXT, 2);
  drawCenteredText(140, SPLASH_CREATOR, COLOR_TEXT, 1);
  drawCenteredText(180, SPLASH_LOADING, COLOR_TEXT, 1);
}

void Display::drawSplashScreen() {
  // Use the animated version
  animateSplashScreen(SPLASH_ANIMATION);
}

void Display::drawMainMenu(const char* devices[], int deviceCount, int page, int totalPages) {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button with icon
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
    drawButton(220, 60, 80, 30, "NEXT>");
  }
  
  // Draw back button (disabled)
  tft->fillRect(20, 220, 80, 20, COLOR_DISABLED);
  tft->drawRect(20, 220, 80, 20, COLOR_DISABLED);
  drawText(40, 225, "BACK", COLOR_DISABLED, 1);
}

void Display::drawDeviceMenu(const char* deviceName) {
  clear();
  
  // Draw small logo
  drawLogo(10, 10, true);
  
  // Draw power button with icon
  drawPowerButton();
  
  // Draw device name
  char header[32];
  snprintf(header, sizeof(header), "Device: %s", deviceName);
  drawText(10, 40, header, COLOR_TEXT, 2);
  
  // Draw control buttons with icons
  drawVolumeUpButton(20, 60, 120, 40);
  drawVolumeDownButton(20, 110, 120, 40);
  drawInputButton(20, 160, 120, 40);
  
  // Draw channel buttons on the right
  drawChannelUpButton(160, 60, 120, 40);
  drawChannelDownButton(160, 110, 120, 40);
  
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
  
  // Draw large volume buttons with icons
  drawVolumeUpButton(60, 70, 200, 50);
  drawVolumeDownButton(60, 130, 200, 50);
  
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
  
  // Draw large channel buttons with icons
  drawChannelUpButton(60, 70, 200, 50);
  drawChannelDownButton(60, 130, 200, 50);
  
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
  drawIconButton(240, 10, 70, 30, UIIcons::drawPowerIcon, pressed);
}

void Display::drawBackButton(bool enabled) {
  if (enabled) {
    drawIconButton(240, 200, 70, 30, UIIcons::drawBackIcon, false);
  } else {
    tft->fillRect(240, 200, 70, 30, COLOR_DISABLED);
    tft->drawRect(240, 200, 70, 30, COLOR_DISABLED);
    UIIcons::drawBackIcon(tft, 255, 205, 20, COLOR_DISABLED);
  }
}

void Display::drawVolumeUpButton(int x, int y, int w, int h, bool pressed) {
  drawIconButton(x, y, w, h, UIIcons::drawVolumeUpIcon, pressed);
}

void Display::drawVolumeDownButton(int x, int y, int w, int h, bool pressed) {
  drawIconButton(x, y, w, h, UIIcons::drawVolumeDownIcon, pressed);
}

void Display::drawChannelUpButton(int x, int y, int w, int h, bool pressed) {
  drawIconButton(x, y, w, h, UIIcons::drawChannelUpIcon, pressed);
}

void Display::drawChannelDownButton(int x, int y, int w, int h, bool pressed) {
  drawIconButton(x, y, w, h, UIIcons::drawChannelDownIcon, pressed);
}

void Display::drawInputButton(int x, int y, int w, int h, bool pressed) {
  drawIconButton(x, y, w, h, UIIcons::drawInputIcon, pressed);
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