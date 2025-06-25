/*
 * VHC Universal Remote - Touch Input Implementation
 */

#include "touch_input.h"
#include <EEPROM.h>

// Global touch input instance
TouchInput touchInput;

// EEPROM addresses for calibration data
#define CAL_FLAG_ADDR 0
#define CAL_MINX_ADDR 1
#define CAL_MAXX_ADDR 3
#define CAL_MINY_ADDR 5
#define CAL_MAXY_ADDR 7
#define CAL_FLAG_VALUE 0xAB

TouchInput::TouchInput() {
  ts = nullptr;
  calibrated = false;
  calMinX = TS_MINX;
  calMaxX = TS_MAXX;
  calMinY = TS_MINY;
  calMaxY = TS_MAXY;
  wasPressed = false;
  touchStartTime = 0;
  lastX = 0;
  lastY = 0;
}

void TouchInput::begin() {
  ts = new XPT2046_Touchscreen(TOUCH_CS);
  ts->begin();
  ts->setRotation(1); // Match display rotation
  
  // Try to load saved calibration
  loadCalibration();
  
  #if DEBUG_SERIAL
    Serial.println(F("Touch input initialized"));
    Serial.print(F("Calibration: X("));
    Serial.print(calMinX);
    Serial.print(F("-"));
    Serial.print(calMaxX);
    Serial.print(F(") Y("));
    Serial.print(calMinY);
    Serial.print(F("-"));
    Serial.print(calMaxY);
    Serial.println(F(")"));
  #endif
}

bool TouchInput::isTouched() {
  return ts->touched();
}

bool TouchInput::getTouchPoint(int& x, int& y) {
  if (!ts->touched()) {
    return false;
  }
  
  TS_Point p = ts->getPoint();
  
  // Map to screen coordinates
  x = mapTouchX(p.x);
  y = mapTouchY(p.y);
  
  // Bounds checking
  if (x < 0) x = 0;
  if (x >= SCREEN_WIDTH) x = SCREEN_WIDTH - 1;
  if (y < 0) y = 0;
  if (y >= SCREEN_HEIGHT) y = SCREEN_HEIGHT - 1;
  
  #if DEBUG_TOUCH
    Serial.print(F("Touch: Raw("));
    Serial.print(p.x);
    Serial.print(F(","));
    Serial.print(p.y);
    Serial.print(F(") Mapped("));
    Serial.print(x);
    Serial.print(F(","));
    Serial.print(y);
    Serial.println(F(")"));
  #endif
  
  lastX = x;
  lastY = y;
  
  return true;
}

void TouchInput::setCalibration(int minX, int maxX, int minY, int maxY) {
  calMinX = minX;
  calMaxX = maxX;
  calMinY = minY;
  calMaxY = maxY;
  calibrated = true;
}

void TouchInput::startCalibration() {
  // Reset to default values for calibration
  calMinX = TS_MINX;
  calMaxX = TS_MAXX;
  calMinY = TS_MINY;
  calMaxY = TS_MAXY;
  calibrated = false;
}

bool TouchInput::calibratePoint(int screenX, int screenY, int& rawX, int& rawY) {
  if (!ts->touched()) {
    return false;
  }
  
  TS_Point p = ts->getPoint();
  rawX = p.x;
  rawY = p.y;
  
  return true;
}

void TouchInput::saveCalibration() {
  EEPROM.write(CAL_FLAG_ADDR, CAL_FLAG_VALUE);
  EEPROM.put(CAL_MINX_ADDR, calMinX);
  EEPROM.put(CAL_MAXX_ADDR, calMaxX);
  EEPROM.put(CAL_MINY_ADDR, calMinY);
  EEPROM.put(CAL_MAXY_ADDR, calMaxY);
  
  #if DEBUG_SERIAL
    Serial.println(F("Calibration saved to EEPROM"));
  #endif
}

void TouchInput::loadCalibration() {
  if (EEPROM.read(CAL_FLAG_ADDR) == CAL_FLAG_VALUE) {
    EEPROM.get(CAL_MINX_ADDR, calMinX);
    EEPROM.get(CAL_MAXX_ADDR, calMaxX);
    EEPROM.get(CAL_MINY_ADDR, calMinY);
    EEPROM.get(CAL_MAXY_ADDR, calMaxY);
    calibrated = true;
    
    #if DEBUG_SERIAL
      Serial.println(F("Calibration loaded from EEPROM"));
    #endif
  } else {
    #if DEBUG_SERIAL
      Serial.println(F("No saved calibration found"));
    #endif
  }
}

unsigned long TouchInput::getTouchDuration() {
  if (wasPressed && touchStartTime > 0) {
    return millis() - touchStartTime;
  }
  return 0;
}

bool TouchInput::isLongPress() {
  return getTouchDuration() > REPEAT_DELAY;
}

void TouchInput::update() {
  bool currentlyPressed = isTouched();
  
  if (currentlyPressed && !wasPressed) {
    // New touch
    touchStartTime = millis();
  } else if (!currentlyPressed && wasPressed) {
    // Touch released
    touchStartTime = 0;
  }
  
  wasPressed = currentlyPressed;
}

int TouchInput::mapTouchX(int raw) {
  return map(raw, calMinX, calMaxX, 0, SCREEN_WIDTH);
}

int TouchInput::mapTouchY(int raw) {
  return map(raw, calMinY, calMaxY, 0, SCREEN_HEIGHT);
}