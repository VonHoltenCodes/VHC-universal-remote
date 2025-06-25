/*
 * VHC Universal Remote - Menu System
 * Handles navigation, state management, and user interaction
 */

#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "config.h"

// Menu states
enum Screen {
  SCREEN_SPLASH,
  SCREEN_MAIN,
  SCREEN_DEVICE,
  SCREEN_VOLUME,
  SCREEN_CHANNEL,
  SCREEN_ERROR
};

// Touch event types
enum TouchEvent {
  TOUCH_NONE,
  TOUCH_TAP,
  TOUCH_HOLD,
  TOUCH_RELEASE
};

// Device structure
struct IRCommand {
  char command[16];
  unsigned long code;
  char protocol[8];
};

struct Device {
  char name[32];
  IRCommand commands[MAX_COMMANDS];
  int commandCount;
};

class Menu {
private:
  Screen currentScreen;
  Screen previousScreen;
  Device devices[MAX_DEVICES];
  int deviceCount;
  int selectedDevice;
  int mainMenuPage;
  unsigned long screenTimer;
  unsigned long touchTimer;
  bool touchActive;
  int lastTouchX;
  int lastTouchY;
  
public:
  Menu();
  void begin();
  
  // Screen management
  Screen getCurrentScreen() { return currentScreen; }
  void setScreen(Screen screen);
  void returnToPrevious();
  bool isTimeToAdvance(); // For splash screen
  
  // Device management
  int loadDevices(); // Returns count, -1 on error
  Device* getDevice(int index);
  Device* getCurrentDevice();
  const char* getDeviceName(int index);
  int getDeviceCount() { return deviceCount; }
  
  // Navigation
  void nextPage();
  void previousPage();
  void selectDevice(int index);
  int getCurrentPage() { return mainMenuPage; }
  int getTotalPages();
  
  // Touch handling
  TouchEvent processTouchInput(int x, int y, bool touched);
  void handleTouch(int x, int y, TouchEvent event);
  bool isInZone(int x, int y, int zoneX, int zoneY, int zoneW, int zoneH);
  
  // Command lookup
  IRCommand* findCommand(const char* commandName);
  IRCommand* findCommand(int deviceIndex, const char* commandName);
  
  // State helpers
  bool needsRefresh();
  void resetTimer();
  const char* getErrorMessage();
  void setError(const char* message);
  
private:
  // Touch zones for different screens
  void handleMainMenuTouch(int x, int y, TouchEvent event);
  void handleDeviceMenuTouch(int x, int y, TouchEvent event);
  void handleVolumeMenuTouch(int x, int y, TouchEvent event);
  void handleChannelMenuTouch(int x, int y, TouchEvent event);
  void handlePowerButton(TouchEvent event);
  
  // CSV parsing helper
  bool parseCSVLine(char* line, Device* device);
  
  char errorMessage[64];
  bool refreshNeeded;
};

// Global menu instance
extern Menu menu;

#endif // MENU_H