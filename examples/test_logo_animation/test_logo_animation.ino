/*
 * VHC Universal Remote - Logo Animation Test
 * Tests the sliding VHC logo animation
 * 
 * Created by VonHoltenCodes
 * Development collaboration by Claude Code
 */

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Pin definitions (same as main project)
#define TFT_CS   10
#define TFT_DC   9
#define TFT_RST  14
#define TFT_LED  15

// Colors
#define COLOR_BACKGROUND ILI9341_BLACK
#define COLOR_TEXT       ILI9341_RED

// Display object
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Logo definition
const char* LOGO_MEDIUM[] = {
  "  _   _ _   _ _____   ",
  " | | | | | | |  __ \\  ",
  " | | | | |_| | |  \\/  ",
  " | | | |  _  | |      ",
  " \\ \\_/ / | | | |____  ",
  "  \\___/\\_| |_/\\____/  "
};

void setup() {
  Serial.begin(115200);
  Serial.println(F("VHC Logo Animation Test"));
  
  // Initialize display
  pinMode(TFT_LED, OUTPUT);
  analogWrite(TFT_LED, 255); // Full brightness
  
  tft.begin();
  tft.setRotation(1); // Landscape
  tft.fillScreen(COLOR_BACKGROUND);
  
  delay(1000); // Pause before animation
}

void loop() {
  // Run the animation
  animateLogo();
  
  // Wait 3 seconds
  delay(3000);
  
  // Clear screen
  tft.fillScreen(COLOR_BACKGROUND);
  
  // Wait 1 second before repeating
  delay(1000);
}

void animateLogo() {
  int totalFrames = 30;
  int frameDelay = 2000 / totalFrames; // 2 second animation
  int logoY = 120; // Center Y position
  
  for (int frame = 0; frame <= totalFrames; frame++) {
    drawAnimatedLogo(160, logoY, frame, totalFrames);
    delay(frameDelay);
  }
  
  // Draw additional text after animation
  tft.setCursor(70, 180);
  tft.setTextColor(COLOR_TEXT);
  tft.setTextSize(2);
  tft.print(F("UNIVERSAL REMOTE"));
}

void drawAnimatedLogo(int centerX, int centerY, int frame, int totalFrames) {
  // Calculate animation progress (0.0 to 1.0)
  float progress = (float)frame / (float)totalFrames;
  
  // Logo dimensions
  int logoWidth = strlen(LOGO_MEDIUM[0]) * 6; // 6 pixels per character
  int logoHeight = 60; // 6 lines * 10 pixels per line
  
  // Starting positions (off screen)
  int leftStartX = -logoWidth;
  int rightStartX = 320; // Screen width
  
  // Final position
  int finalX = centerX - logoWidth / 2;
  
  // Calculate current positions with easing
  float easeProgress = 1.0f - pow(1.0f - progress, 3); // Cubic ease-out
  int topHalfX = leftStartX + (finalX - leftStartX) * easeProgress;
  int bottomHalfX = rightStartX + (finalX - rightStartX) * easeProgress;
  
  // Clear the logo area
  tft.fillRect(0, centerY - logoHeight/2, 320, logoHeight, COLOR_BACKGROUND);
  
  // Draw top half (first 3 lines) sliding from left
  tft.setTextColor(COLOR_TEXT);
  tft.setTextSize(1);
  for (int i = 0; i < 3; i++) {
    tft.setCursor(topHalfX, centerY - logoHeight/2 + (i * 10));
    tft.print(LOGO_MEDIUM[i]);
  }
  
  // Draw bottom half (last 3 lines) sliding from right
  for (int i = 3; i < 6; i++) {
    tft.setCursor(bottomHalfX, centerY - logoHeight/2 + (i * 10));
    tft.print(LOGO_MEDIUM[i]);
  }
}