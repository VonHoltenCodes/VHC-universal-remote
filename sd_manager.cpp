/*
 * VHC Universal Remote - SD Card Manager Implementation
 * IRDB Format Only
 */

#include "sd_manager.h"
#include "irdb_converter.h"

// Global SD manager instance
SDManager sdManager;

// Common IRDB function name mappings
struct FunctionMap {
  const char* irdbName;
  const char* ourName;
};

const FunctionMap functionMappings[] = {
  {"POWER", "power"},
  {"Power", "power"},
  {"KEY_POWER", "power"},
  {"VOLUME+", "volUp"},
  {"VOLUME_UP", "volUp"},
  {"VOL+", "volUp"},
  {"KEY_VOLUMEUP", "volUp"},
  {"VOLUME-", "volDown"},
  {"VOLUME_DOWN", "volDown"},
  {"VOL-", "volDown"},
  {"KEY_VOLUMEDOWN", "volDown"},
  {"CHANNEL+", "chUp"},
  {"CHANNEL_UP", "chUp"},
  {"CH+", "chUp"},
  {"KEY_CHANNELUP", "chUp"},
  {"CHANNEL-", "chDown"},
  {"CHANNEL_DOWN", "chDown"},
  {"CH-", "chDown"},
  {"KEY_CHANNELDOWN", "chDown"},
  {"MUTE", "mute"},
  {"KEY_MUTE", "mute"},
  {"INPUT", "input"},
  {"SOURCE", "input"},
  {"KEY_INPUT", "input"},
  {"PLAY", "play"},
  {"KEY_PLAY", "play"},
  {"STOP", "stop"},
  {"KEY_STOP", "stop"},
  {"PAUSE", "pause"},
  {"KEY_PAUSE", "pause"},
  {"REWIND", "rewind"},
  {"REW", "rewind"},
  {"KEY_REWIND", "rewind"},
  {"FAST_FORWARD", "forward"},
  {"FF", "forward"},
  {"KEY_FORWARD", "forward"},
  {"RECORD", "record"},
  {"REC", "record"},
  {"KEY_RECORD", "record"},
  {"MENU", "menu"},
  {"KEY_MENU", "menu"},
  {"OK", "ok"},
  {"ENTER", "ok"},
  {"SELECT", "ok"},
  {"KEY_OK", "ok"},
  {NULL, NULL}
};

SDManager::SDManager() {
  initialized = false;
}

bool SDManager::begin() {
  if (!SD.begin(SD_CS)) {
    return false;
  }
  initialized = true;
  return true;
}

int SDManager::loadDevices(Device* devices, int maxDevices) {
  if (!initialized) return -1;
  
  int totalDevices = 0;
  
  // Scan for all CSV files in root directory
  File root = SD.open("/");
  if (!root) return -1;
  
  File entry;
  while ((entry = root.openNextFile()) && totalDevices < maxDevices) {
    // Skip directories and non-CSV files
    if (entry.isDirectory() || !strstr(entry.name(), ".csv")) {
      entry.close();
      continue;
    }
    
    // Load this IRDB file as a device
    if (loadIRDBFile(entry, &devices[totalDevices])) {
      totalDevices++;
    }
    
    entry.close();
  }
  
  root.close();
  return totalDevices;
}

bool SDManager::loadIRDBFile(File& file, Device* device) {
  char line[256];
  
  // Extract device name from filename
  const char* filename = file.name();
  char deviceName[32] = "Unknown";
  
  if (filename) {
    // Remove path if present
    const char* start = strrchr(filename, '/');
    if (!start) start = filename;
    else start++;
    
    // Copy name without extension
    strncpy(deviceName, start, 31);
    deviceName[31] = '\0';
    
    // Remove .csv extension
    char* ext = strstr(deviceName, ".csv");
    if (ext) *ext = '\0';
    
    // Replace underscores with spaces for display
    for (char* p = deviceName; *p; p++) {
      if (*p == '_') *p = ' ';
    }
  }
  
  // Initialize device
  strncpy(device->name, deviceName, 31);
  device->name[31] = '\0';
  device->commandCount = 0;
  
  // Read IRDB format: functionname,protocol,device,subdevice,function
  while (file.available() && device->commandCount < MAX_COMMANDS) {
    // Read line
    int i = 0;
    while (file.available() && i < 255) {
      char c = file.read();
      if (c == '\n' || c == '\r') {
        if (i > 0) break;
        continue;
      }
      line[i++] = c;
    }
    line[i] = '\0';
    
    // Skip empty lines and comments
    if (strlen(line) == 0 || line[0] == '#' || line[0] == '/') continue;
    
    // Parse IRDB CSV line
    char* functionName = strtok(line, ",");
    char* protocolStr = strtok(NULL, ",");
    char* deviceStr = strtok(NULL, ",");
    char* subdeviceStr = strtok(NULL, ",");
    char* functionStr = strtok(NULL, ",");
    
    if (functionName && protocolStr && deviceStr && functionStr) {
      // Parse numeric values
      int protocol = atoi(protocolStr);
      int deviceCode = atoi(deviceStr);
      int subdevice = atoi(subdeviceStr);
      int function = atoi(functionStr);
      
      // Map function name to our standard names
      const char* mappedName = mapFunctionName(functionName);
      
      // Only add if we recognize the function
      if (mappedName) {
        IRCommand* cmd = &device->commands[device->commandCount];
        
        // Set command name
        strncpy(cmd->command, mappedName, 15);
        cmd->command[15] = '\0';
        
        // Convert IRDB codes to hex using converter
        cmd->code = IRDBConverter::convertToHex(protocol, deviceCode, subdevice, function);
        
        // Set protocol name
        const char* protocolName = IRDBConverter::getProtocolName(protocol);
        strncpy(cmd->protocol, protocolName, 7);
        cmd->protocol[7] = '\0';
        
        device->commandCount++;
      }
    }
  }
  
  // Only return true if we found at least one command
  return (device->commandCount > 0);
}

const char* SDManager::mapFunctionName(const char* irdbName) {
  // Check against mapping table
  for (int i = 0; functionMappings[i].irdbName != NULL; i++) {
    if (strcasecmp(irdbName, functionMappings[i].irdbName) == 0) {
      return functionMappings[i].ourName;
    }
  }
  
  // Check for numeric buttons
  if (strlen(irdbName) == 1 && irdbName[0] >= '0' && irdbName[0] <= '9') {
    static char numButton[3];
    numButton[0] = irdbName[0];
    numButton[1] = '\0';
    return numButton;
  }
  
  // Unknown function - return NULL to skip it
  return NULL;
}

bool SDManager::deviceExists(const char* deviceName) {
  if (!initialized) return false;
  
  // Check if a CSV file exists for this device
  char filename[64];
  snprintf(filename, 64, "/%s.csv", deviceName);
  
  File file = SD.open(filename);
  if (file) {
    file.close();
    return true;
  }
  
  return false;
}

int SDManager::getFileCount() {
  if (!initialized) return 0;
  
  int count = 0;
  File root = SD.open("/");
  if (!root) return 0;
  
  File entry;
  while (entry = root.openNextFile()) {
    if (!entry.isDirectory() && strstr(entry.name(), ".csv")) {
      count++;
    }
    entry.close();
  }
  
  root.close();
  return count;
}