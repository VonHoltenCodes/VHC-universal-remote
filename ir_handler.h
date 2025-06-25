/*
 * VHC Universal Remote - IR Handler
 * Manages IR code transmission
 */

#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include <Arduino.h>
#include <IRremote.hpp>
#include "config.h"
#include "menu.h"

class IRHandler {
private:
  IRsend* irsend;
  unsigned long lastSendTime;
  bool initialized;
  
public:
  IRHandler();
  void begin();
  
  // Send IR commands
  bool sendCommand(const char* commandName);
  bool sendCommand(IRCommand* cmd);
  bool sendPowerCommand();
  
  // Protocol-specific sending
  bool sendNEC(unsigned long code, int bits = 32);
  bool sendSony(unsigned long code, int bits = 12);
  bool sendRC5(unsigned long code, int bits = 12);
  
  // Utility functions
  bool canRepeat(); // Check if enough time has passed for repeat
  void resetRepeatTimer();
  const char* getLastError();
  
private:
  char lastError[64];
  void setError(const char* message);
};

// Global IR handler instance
extern IRHandler irHandler;

#endif // IR_HANDLER_H