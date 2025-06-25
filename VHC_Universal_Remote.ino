/*
 * VHC Universal Remote
 * Created by VonHoltenCodes
 * Development collaboration by Claude Code
 * 
 * A touchscreen universal IR remote using Teensy 4.1
 * Features retro red-on-black terminal aesthetic
 */

#include <SPI.h>
#include <SD.h>
#include "config.h"
#include "display.h"
#include "menu.h"
#include "ir_handler.h"
#include "touch_input.h"

// Module instances
Display display;

// State tracking
unsigned long lastTouchTime = 0;
int loadingFrame = 0;
unsigned long lastLoadingUpdate = 0;

void setup() {
  Serial.begin(115200);
  
  // Wait for serial connection (optional, remove for standalone operation)
  while (!Serial && millis() < 3000);
  
  Serial.println(F("=================================="));
  Serial.println(F("VHC Universal Remote v1.0"));
  Serial.println(F("Created by VonHoltenCodes"));
  Serial.println(F("Dev Support: Claude Code"));
  Serial.println(F("=================================="));
  Serial.println(F("Initializing..."));
  
  // Initialize display first
  Serial.print(F("Display... "));
  display.begin();
  display.drawSplashScreen();
  Serial.println(F("OK"));
  
  // Initialize SD card
  Serial.print(F("SD Card... "));
  if (!SD.begin(SD_CS)) {
    Serial.println(F("FAILED"));
    display.drawErrorScreen(ERROR_NO_SD);
    while (1) {
      delay(1000);
    }
  }
  Serial.println(F("OK"));
  
  // Initialize touch input
  Serial.print(F("Touch... "));
  touchInput.begin();
  Serial.println(F("OK"));
  
  // Initialize IR handler
  Serial.print(F("IR... "));
  irHandler.begin();
  Serial.println(F("OK"));
  
  // Initialize menu system
  Serial.print(F("Menu... "));
  menu.begin();
  Serial.println(F("OK"));
  
  Serial.println(F("Setup complete!"));
  Serial.println(F("=================================="));
}

void loop() {
  // Update modules
  touchInput.update();
  
  // Handle splash screen animation
  if (menu.getCurrentScreen() == SCREEN_SPLASH) {
    // Update loading animation
    if (millis() - lastLoadingUpdate > 500) {
      display.updateLoadingAnimation(loadingFrame++);
      lastLoadingUpdate = millis();
    }
    
    // Check if time to advance
    if (menu.isTimeToAdvance()) {
      // Load devices from SD card
      int deviceCount = menu.loadDevices();
      if (deviceCount < 0) {
        // Error loading devices, error screen already set
        updateDisplay();
      } else {
        menu.setScreen(SCREEN_MAIN);
        updateDisplay();
      }
    }
    return;
  }
  
  // Handle touch input
  int touchX, touchY;
  bool touched = touchInput.getTouchPoint(touchX, touchY);
  TouchEvent event = menu.processTouchInput(touchX, touchY, touched);
  
  if (event != TOUCH_NONE) {
    // Store the last touch position for command processing
    menu.handleTouch(touchX, touchY, event);
    
    // Process any IR commands based on current screen and touch
    processIRCommands(touchX, touchY, event);
    
    // Update display if needed
    if (menu.needsRefresh()) {
      updateDisplay();
    }
  }
  
  // Small delay to prevent overwhelming the system
  delay(10);
}

void processIRCommands(int x, int y, TouchEvent event) {
  Screen currentScreen = menu.getCurrentScreen();
  
  // Check for power button press from any screen
  if (currentScreen != SCREEN_SPLASH && menu.isInZone(x, y, 240, 10, 70, 30)) {
    if (event == TOUCH_TAP) {
      irHandler.sendPowerCommand();
      display.drawPowerButton(true);
      delay(100);
      display.drawPowerButton(false);
    }
    return;
  }
  
  // Handle screen-specific commands
  switch (currentScreen) {
    case SCREEN_DEVICE:
      if (event == TOUCH_TAP && menu.isInZone(x, y, 20, 140, 120, 30)) {
        // Input button pressed
        irHandler.sendCommand("input");
      }
      break;
      
    case SCREEN_VOLUME:
      if (event == TOUCH_TAP || (event == TOUCH_HOLD && irHandler.canRepeat())) {
        if (menu.isInZone(x, y, 20, 60, 120, 30)) {
          irHandler.sendCommand("volUp");
        } else if (menu.isInZone(x, y, 20, 100, 120, 30)) {
          irHandler.sendCommand("volDown");
        }
      }
      break;
      
    case SCREEN_CHANNEL:
      if (event == TOUCH_TAP || (event == TOUCH_HOLD && irHandler.canRepeat())) {
        if (menu.isInZone(x, y, 20, 60, 120, 30)) {
          irHandler.sendCommand("chUp");
        } else if (menu.isInZone(x, y, 20, 100, 120, 30)) {
          irHandler.sendCommand("chDown");
        }
      }
      break;
  }
}

void updateDisplay() {
  Screen currentScreen = menu.getCurrentScreen();
  
  switch (currentScreen) {
    case SCREEN_SPLASH:
      display.drawSplashScreen();
      break;
      
    case SCREEN_MAIN:
      {
        // Build device list for current page
        const char* deviceList[DEVICES_PER_PAGE];
        int startIdx = menu.getCurrentPage() * DEVICES_PER_PAGE;
        int count = 0;
        
        for (int i = 0; i < DEVICES_PER_PAGE && (startIdx + i) < menu.getDeviceCount(); i++) {
          deviceList[i] = menu.getDeviceName(startIdx + i);
          count++;
        }
        
        display.drawMainMenu(deviceList, count, menu.getCurrentPage(), menu.getTotalPages());
      }
      break;
      
    case SCREEN_DEVICE:
      {
        Device* dev = menu.getCurrentDevice();
        if (dev) {
          display.drawDeviceMenu(dev->name);
        }
      }
      break;
      
    case SCREEN_VOLUME:
      display.drawVolumeMenu();
      break;
      
    case SCREEN_CHANNEL:
      display.drawChannelMenu();
      break;
      
    case SCREEN_ERROR:
      display.drawErrorScreen(menu.getErrorMessage());
      break;
  }
}