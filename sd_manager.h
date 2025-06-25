/*
 * VHC Universal Remote - SD Card Manager
 * IRDB Format Only
 */

#ifndef SD_MANAGER_H
#define SD_MANAGER_H

#include <Arduino.h>
#include <SD.h>
#include "config.h"

class SDManager {
private:
  bool initialized;
  
  // Load a single IRDB file into a device
  bool loadIRDBFile(File& file, Device* device);
  
  // Map IRDB function names to our standard names
  const char* mapFunctionName(const char* irdbName);
  
public:
  SDManager();
  
  // Initialize SD card
  bool begin();
  
  // Load all CSV files from SD card as devices
  int loadDevices(Device* devices, int maxDevices);
  
  // Check if device file exists
  bool deviceExists(const char* deviceName);
  
  // Get number of CSV files on card
  int getFileCount();
};

// Global SD manager instance
extern SDManager sdManager;

#endif // SD_MANAGER_H