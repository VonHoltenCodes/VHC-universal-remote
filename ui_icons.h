/*
 * VHC Universal Remote - UI Icons
 * Emoji-style drawn icons for buttons and UI elements
 * These use Adafruit GFX drawing primitives
 */

#ifndef UI_ICONS_H
#define UI_ICONS_H

#include <Adafruit_GFX.h>
#include "config.h"

class UIIcons {
public:
  // Draw a power icon (circle with line)
  static void drawPowerIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int radius = size / 2;
    // Draw circle
    gfx->drawCircle(x + radius, y + radius, radius, color);
    // Draw vertical line in center top
    gfx->drawLine(x + radius, y, x + radius, y + radius, color);
    // Make it thicker
    gfx->drawLine(x + radius - 1, y, x + radius - 1, y + radius, color);
    gfx->drawLine(x + radius + 1, y, x + radius + 1, y + radius, color);
  }

  // Draw volume up icon (speaker with + waves)
  static void drawVolumeUpIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // Speaker cone
    gfx->fillTriangle(x, y + size/3, x, y + 2*size/3, x + size/3, y + size/2, color);
    // Speaker box
    gfx->fillRect(x + size/3, y + size/3, size/6, size/3, color);
    // Sound waves
    gfx->drawLine(x + size/2, y + size/3, x + 2*size/3, y + size/4, color);
    gfx->drawLine(x + size/2, y + size/2, x + 3*size/4, y + size/2, color);
    gfx->drawLine(x + size/2, y + 2*size/3, x + 2*size/3, y + 3*size/4, color);
    // Plus sign
    gfx->drawLine(x + 3*size/4, y + size/4, x + size, y + size/4, color);
    gfx->drawLine(x + 7*size/8, y + size/8, x + 7*size/8, y + 3*size/8, color);
  }

  // Draw volume down icon (speaker with - wave)
  static void drawVolumeDownIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // Speaker cone
    gfx->fillTriangle(x, y + size/3, x, y + 2*size/3, x + size/3, y + size/2, color);
    // Speaker box
    gfx->fillRect(x + size/3, y + size/3, size/6, size/3, color);
    // Single sound wave
    gfx->drawLine(x + size/2, y + size/2, x + 2*size/3, y + size/2, color);
    // Minus sign
    gfx->drawLine(x + 3*size/4, y + size/4, x + size, y + size/4, color);
  }

  // Draw channel up icon (upward arrow)
  static void drawChannelUpIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int centerX = x + size/2;
    int tipY = y + size/4;
    // Arrow head
    gfx->fillTriangle(centerX, tipY, 
                      centerX - size/3, tipY + size/3,
                      centerX + size/3, tipY + size/3, color);
    // Arrow shaft
    gfx->fillRect(centerX - size/6, tipY + size/3, size/3, size/3, color);
  }

  // Draw channel down icon (downward arrow)
  static void drawChannelDownIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int centerX = x + size/2;
    int tipY = y + 3*size/4;
    // Arrow head
    gfx->fillTriangle(centerX, tipY, 
                      centerX - size/3, tipY - size/3,
                      centerX + size/3, tipY - size/3, color);
    // Arrow shaft
    gfx->fillRect(centerX - size/6, y + size/4, size/3, size/3, color);
  }

  // Draw input/source icon (rectangle with arrow)
  static void drawInputIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // TV/Display outline
    gfx->drawRect(x, y + size/4, 3*size/4, size/2, color);
    // Arrow pointing in
    gfx->drawLine(x + 3*size/4, y + size/2, x + size, y + size/2, color);
    gfx->drawLine(x + size, y + size/2, x + 7*size/8, y + 3*size/8, color);
    gfx->drawLine(x + size, y + size/2, x + 7*size/8, y + 5*size/8, color);
  }

  // Draw menu icon (three horizontal lines)
  static void drawMenuIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int lineHeight = size / 5;
    gfx->fillRect(x, y + lineHeight, size, lineHeight/2, color);
    gfx->fillRect(x, y + 2*lineHeight, size, lineHeight/2, color);
    gfx->fillRect(x, y + 3*lineHeight, size, lineHeight/2, color);
  }

  // Draw back arrow icon
  static void drawBackIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int centerY = y + size/2;
    // Arrow head pointing left
    gfx->fillTriangle(x + size/4, centerY,
                      x + size/2, centerY - size/4,
                      x + size/2, centerY + size/4, color);
    // Arrow shaft
    gfx->fillRect(x + size/2, centerY - size/8, size/2, size/4, color);
  }

  // Draw OK/Select icon (checkmark)
  static void drawOKIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // Draw checkmark
    gfx->drawLine(x + size/4, y + size/2, x + size/2, y + 3*size/4, color);
    gfx->drawLine(x + size/2, y + 3*size/4, x + 3*size/4, y + size/4, color);
    // Make it thicker
    gfx->drawLine(x + size/4, y + size/2 + 1, x + size/2, y + 3*size/4 + 1, color);
    gfx->drawLine(x + size/2, y + 3*size/4 + 1, x + 3*size/4, y + size/4 + 1, color);
  }

  // Draw mute icon (speaker with X)
  static void drawMuteIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // Speaker cone
    gfx->fillTriangle(x, y + size/3, x, y + 2*size/3, x + size/3, y + size/2, color);
    // Speaker box
    gfx->fillRect(x + size/3, y + size/3, size/6, size/3, color);
    // X over speaker
    gfx->drawLine(x + size/2, y + size/3, x + 3*size/4, y + 2*size/3, color);
    gfx->drawLine(x + size/2, y + 2*size/3, x + 3*size/4, y + size/3, color);
  }

  // Draw settings/gear icon
  static void drawSettingsIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int centerX = x + size/2;
    int centerY = y + size/2;
    int radius = size/3;
    
    // Draw gear teeth (simplified as lines radiating out)
    for (int i = 0; i < 8; i++) {
      float angle = i * PI / 4;
      int x1 = centerX + cos(angle) * radius;
      int y1 = centerY + sin(angle) * radius;
      int x2 = centerX + cos(angle) * (radius + size/8);
      int y2 = centerY + sin(angle) * (radius + size/8);
      gfx->drawLine(x1, y1, x2, y2, color);
    }
    
    // Draw center circle
    gfx->fillCircle(centerX, centerY, radius/2, color);
    gfx->fillCircle(centerX, centerY, radius/4, COLOR_BACKGROUND);
  }

  // Draw play icon (triangle)
  static void drawPlayIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    gfx->fillTriangle(x + size/4, y + size/4,
                      x + size/4, y + 3*size/4,
                      x + 3*size/4, y + size/2, color);
  }

  // Draw pause icon (two vertical bars)
  static void drawPauseIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    gfx->fillRect(x + size/4, y + size/4, size/6, size/2, color);
    gfx->fillRect(x + 7*size/12, y + size/4, size/6, size/2, color);
  }

  // Draw stop icon (square)
  static void drawStopIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    gfx->fillRect(x + size/4, y + size/4, size/2, size/2, color);
  }

  // Draw TV device icon
  static void drawTVIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // TV body
    gfx->drawRect(x + size/8, y + size/4, 3*size/4, size/2, color);
    // Screen
    gfx->drawRect(x + size/6, y + size/3, 2*size/3, size/3, color);
    // Stand
    gfx->drawLine(x + size/2, y + 3*size/4, x + size/3, y + 7*size/8, color);
    gfx->drawLine(x + size/2, y + 3*size/4, x + 2*size/3, y + 7*size/8, color);
  }

  // Draw audio/soundbar icon
  static void drawAudioIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    // Soundbar body
    gfx->drawRect(x + size/8, y + 3*size/8, 3*size/4, size/4, color);
    // Speaker grilles
    gfx->fillCircle(x + size/4, y + size/2, size/12, color);
    gfx->fillCircle(x + size/2, y + size/2, size/12, color);
    gfx->fillCircle(x + 3*size/4, y + size/2, size/12, color);
  }

  // Draw disc/DVD/Blu-ray icon
  static void drawDiscIcon(Adafruit_GFX* gfx, int x, int y, int size, uint16_t color) {
    int centerX = x + size/2;
    int centerY = y + size/2;
    // Outer circle
    gfx->drawCircle(centerX, centerY, size/3, color);
    // Inner circle
    gfx->fillCircle(centerX, centerY, size/8, color);
    // Center hole
    gfx->fillCircle(centerX, centerY, size/16, COLOR_BACKGROUND);
  }
};

#endif // UI_ICONS_H