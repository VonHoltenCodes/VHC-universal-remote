/*
 * VHC Universal Remote - Touch Input Handler
 * Manages touchscreen calibration and input processing
 */

#ifndef TOUCH_INPUT_H
#define TOUCH_INPUT_H

#include <Arduino.h>
#include <XPT2046_Touchscreen.h>
#include "config.h"

class TouchInput {
private:
  XPT2046_Touchscreen* ts;
  bool calibrated;
  
  // Calibration values
  int calMinX, calMaxX;
  int calMinY, calMaxY;
  
  // Touch state
  bool wasPressed;
  unsigned long touchStartTime;
  int lastX, lastY;
  
public:
  TouchInput();
  void begin();
  
  // Touch detection
  bool isTouched();
  bool getTouchPoint(int& x, int& y);
  
  // Calibration
  void setCalibration(int minX, int maxX, int minY, int maxY);
  void startCalibration();
  bool calibratePoint(int screenX, int screenY, int& rawX, int& rawY);
  void saveCalibration();
  void loadCalibration();
  
  // Utility
  unsigned long getTouchDuration();
  bool isLongPress();
  void update(); // Call in main loop
  
private:
  int mapTouchX(int raw);
  int mapTouchY(int raw);
};

// Global touch input instance
extern TouchInput touchInput;

#endif // TOUCH_INPUT_H