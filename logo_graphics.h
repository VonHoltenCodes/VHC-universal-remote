/*
 * VHC Universal Remote - Graphical Logo
 * Block-based logo drawn with graphics primitives
 */

#ifndef LOGO_GRAPHICS_H
#define LOGO_GRAPHICS_H

#include <Adafruit_GFX.h>

class LogoGraphics {
public:
  // Draw VHC logo using filled rectangles
  static void drawBlockLogo(Adafruit_GFX* gfx, int x, int y, int scale, uint16_t color) {
    // Scale: 1 = tiny (3x5 per letter), 2 = small, 3 = medium, 4 = large
    int blockSize = scale * 2;
    int spacing = scale;
    
    // Draw V (inverted triangle shape)
    // Left diagonal
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(x + i * spacing, y + i * blockSize, blockSize, blockSize, color);
    }
    // Right diagonal
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(x + (8 - i) * spacing, y + i * blockSize, blockSize, blockSize, color);
    }
    
    // Draw H (two verticals with horizontal bar)
    int hOffset = x + 12 * spacing;
    // Left vertical
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(hOffset, y + i * blockSize, blockSize, blockSize, color);
    }
    // Right vertical
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(hOffset + 4 * spacing, y + i * blockSize, blockSize, blockSize, color);
    }
    // Horizontal bar
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(hOffset + i * spacing, y + 2 * blockSize, blockSize, blockSize, color);
    }
    
    // Draw C (curved rectangle)
    int cOffset = x + 20 * spacing;
    // Top horizontal
    for (int i = 0; i < 4; i++) {
      gfx->fillRect(cOffset + i * spacing, y, blockSize, blockSize, color);
    }
    // Left vertical
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(cOffset, y + i * blockSize, blockSize, blockSize, color);
    }
    // Bottom horizontal
    for (int i = 0; i < 4; i++) {
      gfx->fillRect(cOffset + i * spacing, y + 4 * blockSize, blockSize, blockSize, color);
    }
  }
  
  // Draw animated block logo with sliding effect
  static void drawAnimatedBlockLogo(Adafruit_GFX* gfx, int centerX, int centerY, 
                                    int frame, int totalFrames, int scale, uint16_t color) {
    float progress = (float)frame / (float)totalFrames;
    
    // Logo dimensions
    int logoWidth = 26 * scale; // Approximate width
    int logoHeight = 10 * scale;
    
    // Starting positions
    int leftStartX = -logoWidth;
    int rightStartX = 320; // Screen width
    
    // Final position
    int finalX = centerX - logoWidth / 2;
    int finalY = centerY - logoHeight / 2;
    
    // Easing
    float easeProgress = 1.0f - pow(1.0f - progress, 3);
    int vhX = leftStartX + (finalX - leftStartX) * easeProgress;
    int cX = rightStartX + (finalX + 20 * scale - rightStartX) * easeProgress;
    
    // Clear area
    gfx->fillRect(0, finalY - 10, 320, logoHeight + 20, ILI9341_BLACK);
    
    // Draw V and H sliding from left
    drawV(gfx, vhX, finalY, scale, color);
    drawH(gfx, vhX + 12 * scale, finalY, scale, color);
    
    // Draw C sliding from right
    drawC(gfx, cX, finalY, scale, color);
  }
  
  // Individual letter drawing functions
  static void drawV(Adafruit_GFX* gfx, int x, int y, int scale, uint16_t color) {
    int blockSize = scale * 2;
    int spacing = scale;
    
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(x + i * spacing, y + i * blockSize, blockSize, blockSize, color);
      gfx->fillRect(x + (8 - i) * spacing, y + i * blockSize, blockSize, blockSize, color);
    }
  }
  
  static void drawH(Adafruit_GFX* gfx, int x, int y, int scale, uint16_t color) {
    int blockSize = scale * 2;
    int spacing = scale;
    
    // Verticals
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(x, y + i * blockSize, blockSize, blockSize, color);
      gfx->fillRect(x + 4 * spacing, y + i * blockSize, blockSize, blockSize, color);
    }
    // Horizontal
    for (int i = 0; i < 5; i++) {
      gfx->fillRect(x + i * spacing, y + 2 * blockSize, blockSize, blockSize, color);
    }
  }
  
  static void drawC(Adafruit_GFX* gfx, int x, int y, int scale, uint16_t color) {
    int blockSize = scale * 2;
    int spacing = scale;
    
    // Top and bottom
    for (int i = 0; i < 4; i++) {
      gfx->fillRect(x + i * spacing, y, blockSize, blockSize, color);
      gfx->fillRect(x + i * spacing, y + 4 * blockSize, blockSize, blockSize, color);
    }
    // Left side
    for (int i = 1; i < 4; i++) {
      gfx->fillRect(x, y + i * blockSize, blockSize, blockSize, color);
    }
  }
  
  // Modern style with rounded corners (simulated)
  static void drawModernLogo(Adafruit_GFX* gfx, int x, int y, int height, uint16_t color) {
    int letterWidth = height * 0.8;
    int spacing = height * 0.3;
    int thickness = height * 0.2;
    
    // V - Two thick diagonals
    gfx->fillTriangle(x, y, x + thickness, y, x + letterWidth/2, y + height, color);
    gfx->fillTriangle(x + letterWidth - thickness, y, x + letterWidth, y, x + letterWidth/2, y + height, color);
    
    // H - Modern block style
    int hX = x + letterWidth + spacing;
    gfx->fillRect(hX, y, thickness, height, color);
    gfx->fillRect(hX + letterWidth - thickness, y, thickness, height, color);
    gfx->fillRect(hX, y + height/2 - thickness/2, letterWidth, thickness, color);
    
    // C - Curved block
    int cX = hX + letterWidth + spacing;
    gfx->fillRect(cX, y, letterWidth, thickness, color);
    gfx->fillRect(cX, y, thickness, height, color);
    gfx->fillRect(cX, y + height - thickness, letterWidth, thickness, color);
  }
};

#endif // LOGO_GRAPHICS_H