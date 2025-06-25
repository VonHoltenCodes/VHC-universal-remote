/*
 * VHC Universal Remote - Menu System Implementation
 */

#include "menu.h"
#include "sd_manager.h"

// Global menu instance
Menu menu;

Menu::Menu() {
  currentScreen = SCREEN_SPLASH;
  previousScreen = SCREEN_SPLASH;
  deviceCount = 0;
  selectedDevice = 0;
  mainMenuPage = 0;
  screenTimer = 0;
  touchTimer = 0;
  touchActive = false;
  lastTouchX = 0;
  lastTouchY = 0;
  refreshNeeded = true;
  errorMessage[0] = '\0';
}

void Menu::begin() {
  resetTimer();
}

void Menu::setScreen(Screen screen) {
  previousScreen = currentScreen;
  currentScreen = screen;
  refreshNeeded = true;
  resetTimer();
}

void Menu::returnToPrevious() {
  Screen temp = currentScreen;
  currentScreen = previousScreen;
  previousScreen = temp;
  refreshNeeded = true;
}

bool Menu::isTimeToAdvance() {
  return (currentScreen == SCREEN_SPLASH && millis() - screenTimer > SPLASH_DURATION);
}

int Menu::loadDevices() {
  // Use the SD manager to load devices
  deviceCount = sdManager.loadDevices(devices, MAX_DEVICES);
  
  if (deviceCount < 0) {
    setError(ERROR_NO_SD);
    return -1;
  }
  
  if (deviceCount == 0) {
    setError(ERROR_NO_DEVICES);
    return -1;
  }
  
  return deviceCount;
}

Device* Menu::getDevice(int index) {
  if (index >= 0 && index < deviceCount) {
    return &devices[index];
  }
  return nullptr;
}

Device* Menu::getCurrentDevice() {
  return getDevice(selectedDevice);
}

const char* Menu::getDeviceName(int index) {
  Device* dev = getDevice(index);
  return dev ? dev->name : "";
}

void Menu::nextPage() {
  int totalPages = getTotalPages();
  if (mainMenuPage < totalPages - 1) {
    mainMenuPage++;
    refreshNeeded = true;
  }
}

void Menu::previousPage() {
  if (mainMenuPage > 0) {
    mainMenuPage--;
    refreshNeeded = true;
  }
}

void Menu::selectDevice(int index) {
  if (index >= 0 && index < deviceCount) {
    selectedDevice = index;
  }
}

int Menu::getTotalPages() {
  return (deviceCount + DEVICES_PER_PAGE - 1) / DEVICES_PER_PAGE;
}

TouchEvent Menu::processTouchInput(int x, int y, bool touched) {
  TouchEvent event = TOUCH_NONE;
  
  if (touched && !touchActive) {
    // New touch
    touchActive = true;
    touchTimer = millis();
    lastTouchX = x;
    lastTouchY = y;
    event = TOUCH_TAP;
  } else if (touched && touchActive) {
    // Continuing touch
    if (millis() - touchTimer > REPEAT_DELAY) {
      event = TOUCH_HOLD;
    }
  } else if (!touched && touchActive) {
    // Touch released
    touchActive = false;
    event = TOUCH_RELEASE;
  }
  
  return event;
}

void Menu::handleTouch(int x, int y, TouchEvent event) {
  if (event == TOUCH_NONE) return;
  
  // Handle power button from any screen
  if (currentScreen != SCREEN_SPLASH && isInZone(x, y, 240, 10, 70, 30)) {
    handlePowerButton(event);
    return;
  }
  
  // Route to appropriate handler
  switch (currentScreen) {
    case SCREEN_MAIN:
      handleMainMenuTouch(x, y, event);
      break;
    case SCREEN_DEVICE:
      handleDeviceMenuTouch(x, y, event);
      break;
    case SCREEN_VOLUME:
      handleVolumeMenuTouch(x, y, event);
      break;
    case SCREEN_CHANNEL:
      handleChannelMenuTouch(x, y, event);
      break;
  }
}

bool Menu::isInZone(int x, int y, int zoneX, int zoneY, int zoneW, int zoneH) {
  return (x >= zoneX && x < zoneX + zoneW && y >= zoneY && y < zoneY + zoneH);
}

void Menu::handleMainMenuTouch(int x, int y, TouchEvent event) {
  if (event != TOUCH_TAP) return;
  
  // Check device buttons
  int startIdx = mainMenuPage * DEVICES_PER_PAGE;
  for (int i = 0; i < DEVICES_PER_PAGE && (startIdx + i) < deviceCount; i++) {
    if (isInZone(x, y, 20, 60 + (i * 40), 200, 30)) {
      selectDevice(startIdx + i);
      setScreen(SCREEN_DEVICE);
      return;
    }
  }
  
  // Check next button
  if (isInZone(x, y, 220, 60, 80, 30) && mainMenuPage < getTotalPages() - 1) {
    nextPage();
  }
}

void Menu::handleDeviceMenuTouch(int x, int y, TouchEvent event) {
  if (event != TOUCH_TAP) return;
  
  // Volume button
  if (isInZone(x, y, 20, 60, 120, 30)) {
    setScreen(SCREEN_VOLUME);
  }
  // Channel button
  else if (isInZone(x, y, 20, 100, 120, 30)) {
    setScreen(SCREEN_CHANNEL);
  }
  // Input button
  else if (isInZone(x, y, 20, 140, 120, 30)) {
    // This will trigger IR send in main code
    refreshNeeded = true;
  }
  // Back button
  else if (isInZone(x, y, 240, 220, 70, 20)) {
    returnToPrevious();
  }
}

void Menu::handleVolumeMenuTouch(int x, int y, TouchEvent event) {
  if (event == TOUCH_TAP || event == TOUCH_HOLD) {
    // Volume up
    if (isInZone(x, y, 20, 60, 120, 30)) {
      // This will trigger IR send in main code
      refreshNeeded = true;
    }
    // Volume down
    else if (isInZone(x, y, 20, 100, 120, 30)) {
      // This will trigger IR send in main code
      refreshNeeded = true;
    }
  }
  
  // Back button (tap only)
  if (event == TOUCH_TAP && isInZone(x, y, 240, 220, 70, 20)) {
    returnToPrevious();
  }
}

void Menu::handleChannelMenuTouch(int x, int y, TouchEvent event) {
  if (event == TOUCH_TAP || event == TOUCH_HOLD) {
    // Channel up
    if (isInZone(x, y, 20, 60, 120, 30)) {
      // This will trigger IR send in main code
      refreshNeeded = true;
    }
    // Channel down
    else if (isInZone(x, y, 20, 100, 120, 30)) {
      // This will trigger IR send in main code
      refreshNeeded = true;
    }
  }
  
  // Back button (tap only)
  if (event == TOUCH_TAP && isInZone(x, y, 240, 220, 70, 20)) {
    returnToPrevious();
  }
}

void Menu::handlePowerButton(TouchEvent event) {
  if (event == TOUCH_TAP) {
    // This will trigger IR send in main code
    refreshNeeded = true;
  }
}

IRCommand* Menu::findCommand(const char* commandName) {
  return findCommand(selectedDevice, commandName);
}

IRCommand* Menu::findCommand(int deviceIndex, const char* commandName) {
  Device* dev = getDevice(deviceIndex);
  if (!dev) return nullptr;
  
  for (int i = 0; i < dev->commandCount; i++) {
    if (strcmp(dev->commands[i].command, commandName) == 0) {
      return &dev->commands[i];
    }
  }
  return nullptr;
}

bool Menu::needsRefresh() {
  bool needed = refreshNeeded;
  refreshNeeded = false;
  return needed;
}

void Menu::resetTimer() {
  screenTimer = millis();
}

const char* Menu::getErrorMessage() {
  return errorMessage;
}

void Menu::setError(const char* message) {
  strncpy(errorMessage, message, 63);
  errorMessage[63] = '\0';
  setScreen(SCREEN_ERROR);
}