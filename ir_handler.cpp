/*
 * VHC Universal Remote - IR Handler Implementation
 */

#include "ir_handler.h"

// Global IR handler instance
IRHandler irHandler;

IRHandler::IRHandler() {
  irsend = nullptr;
  lastSendTime = 0;
  initialized = false;
  lastError[0] = '\0';
}

void IRHandler::begin() {
  irsend = new IRsend(IR_LED);
  irsend->begin();
  initialized = true;
  
  #if DEBUG_SERIAL
    Serial.println(F("IR Handler initialized"));
  #endif
}

bool IRHandler::sendCommand(const char* commandName) {
  if (!initialized) {
    setError("IR not initialized");
    return false;
  }
  
  IRCommand* cmd = menu.findCommand(commandName);
  if (!cmd) {
    setError("Command not found");
    return false;
  }
  
  return sendCommand(cmd);
}

bool IRHandler::sendCommand(IRCommand* cmd) {
  if (!initialized || !cmd) {
    setError("Invalid command");
    return false;
  }
  
  #if DEBUG_IR
    Serial.print(F("Sending IR: "));
    Serial.print(cmd->command);
    Serial.print(F(" Code: 0x"));
    Serial.print(cmd->code, HEX);
    Serial.print(F(" Protocol: "));
    Serial.println(cmd->protocol);
  #endif
  
  bool success = false;
  
  // Send based on protocol
  if (strcmp(cmd->protocol, "NEC") == 0) {
    success = sendNEC(cmd->code);
  } else if (strcmp(cmd->protocol, "Sony") == 0) {
    success = sendSony(cmd->code);
  } else if (strcmp(cmd->protocol, "RC5") == 0) {
    success = sendRC5(cmd->code);
  } else {
    setError("Unknown protocol");
    return false;
  }
  
  if (success) {
    lastSendTime = millis();
  }
  
  return success;
}

bool IRHandler::sendPowerCommand() {
  return sendCommand("power");
}

bool IRHandler::sendNEC(unsigned long code, int bits) {
  if (!initialized) return false;
  
  irsend->sendNEC(code, bits);
  
  #if DEBUG_IR
    Serial.print(F("NEC sent: 0x"));
    Serial.println(code, HEX);
  #endif
  
  return true;
}

bool IRHandler::sendSony(unsigned long code, int bits) {
  if (!initialized) return false;
  
  // Sony protocol requires sending 3 times
  for (int i = 0; i < 3; i++) {
    irsend->sendSony(code, bits);
    if (i < 2) delay(40); // Small delay between repeats
  }
  
  #if DEBUG_IR
    Serial.print(F("Sony sent: 0x"));
    Serial.println(code, HEX);
  #endif
  
  return true;
}

bool IRHandler::sendRC5(unsigned long code, int bits) {
  if (!initialized) return false;
  
  irsend->sendRC5(code, bits);
  
  #if DEBUG_IR
    Serial.print(F("RC5 sent: 0x"));
    Serial.println(code, HEX);
  #endif
  
  return true;
}

bool IRHandler::canRepeat() {
  return (millis() - lastSendTime >= REPEAT_DELAY);
}

void IRHandler::resetRepeatTimer() {
  lastSendTime = millis();
}

const char* IRHandler::getLastError() {
  return lastError;
}

void IRHandler::setError(const char* message) {
  strncpy(lastError, message, 63);
  lastError[63] = '\0';
  
  #if DEBUG_SERIAL
    Serial.print(F("IR Error: "));
    Serial.println(lastError);
  #endif
}