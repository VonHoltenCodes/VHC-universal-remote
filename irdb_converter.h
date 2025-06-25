/*
 * VHC Universal Remote - IRDB Format Converter
 * Converts IRDB CSV format to IR codes for Arduino
 * IRDB format: functionname,protocol,device,subdevice,function
 */

#ifndef IRDB_CONVERTER_H
#define IRDB_CONVERTER_H

#include <Arduino.h>

// IRDB Protocol mappings
enum IRDBProtocol {
  IRDB_PROTOCOL_NEC1 = 0,
  IRDB_PROTOCOL_NEC2 = 1,
  IRDB_PROTOCOL_RC5 = 2,
  IRDB_PROTOCOL_RC6 = 3,
  IRDB_PROTOCOL_SAMSUNG = 4,
  IRDB_PROTOCOL_SONY12 = 5,
  IRDB_PROTOCOL_SONY15 = 6,
  IRDB_PROTOCOL_SONY20 = 7,
  IRDB_PROTOCOL_PANASONIC = 8,
  IRDB_PROTOCOL_JVC = 9,
  IRDB_PROTOCOL_SHARP = 10,
  IRDB_PROTOCOL_DENON = 11,
  IRDB_PROTOCOL_PRONTO = 12
};

class IRDBConverter {
public:
  // Convert IRDB protocol number to string
  static const char* getProtocolName(int protocol) {
    switch(protocol) {
      case IRDB_PROTOCOL_NEC1:
      case IRDB_PROTOCOL_NEC2: return "NEC";
      case IRDB_PROTOCOL_RC5: return "RC5";
      case IRDB_PROTOCOL_RC6: return "RC6";
      case IRDB_PROTOCOL_SAMSUNG: return "SAMSUNG";
      case IRDB_PROTOCOL_SONY12: return "SONY12";
      case IRDB_PROTOCOL_SONY15: return "SONY15";
      case IRDB_PROTOCOL_SONY20: return "SONY20";
      case IRDB_PROTOCOL_PANASONIC: return "PANASONIC";
      case IRDB_PROTOCOL_JVC: return "JVC";
      case IRDB_PROTOCOL_SHARP: return "SHARP";
      case IRDB_PROTOCOL_DENON: return "DENON";
      default: return "UNKNOWN";
    }
  }
  
  // Convert IRDB values to hex code
  static unsigned long convertToHex(int protocol, int device, int subdevice, int function) {
    unsigned long code = 0;
    
    switch(protocol) {
      case IRDB_PROTOCOL_NEC1:
      case IRDB_PROTOCOL_NEC2:
        // NEC: address (device) + inverted address + command (function) + inverted command
        if (subdevice >= 0) {
          // Extended NEC with subdevice
          code = ((unsigned long)device << 24) | ((unsigned long)subdevice << 16) | 
                 ((unsigned long)function << 8) | ((unsigned long)(~function & 0xFF));
        } else {
          // Standard NEC
          code = ((unsigned long)device << 24) | ((unsigned long)(~device & 0xFF) << 16) | 
                 ((unsigned long)function << 8) | ((unsigned long)(~function & 0xFF));
        }
        break;
        
      case IRDB_PROTOCOL_SONY12:
        // Sony 12-bit: 7-bit command + 5-bit address
        code = (function & 0x7F) | ((device & 0x1F) << 7);
        break;
        
      case IRDB_PROTOCOL_SONY15:
        // Sony 15-bit: 7-bit command + 8-bit address
        code = (function & 0x7F) | ((device & 0xFF) << 7);
        break;
        
      case IRDB_PROTOCOL_SONY20:
        // Sony 20-bit: 7-bit command + 5-bit address + 8-bit extended
        code = (function & 0x7F) | ((device & 0x1F) << 7) | ((subdevice & 0xFF) << 12);
        break;
        
      case IRDB_PROTOCOL_RC5:
        // RC5: 2 start bits + toggle + 5-bit address + 6-bit command
        code = 0x1000 | ((device & 0x1F) << 6) | (function & 0x3F);
        break;
        
      case IRDB_PROTOCOL_RC6:
        // RC6: More complex, needs mode bits
        code = ((device & 0xFF) << 8) | (function & 0xFF);
        break;
        
      case IRDB_PROTOCOL_SAMSUNG:
        // Samsung uses standard NEC format
        code = ((unsigned long)device << 24) | ((unsigned long)device << 16) | 
               ((unsigned long)function << 8) | ((unsigned long)(~function & 0xFF));
        break;
        
      case IRDB_PROTOCOL_PANASONIC:
        // Panasonic: manufacturer code + device + subdevice + function
        code = 0x4004 | ((unsigned long)device << 24) | ((unsigned long)subdevice << 16) | 
               ((unsigned long)function << 8);
        break;
        
      case IRDB_PROTOCOL_JVC:
        // JVC: 8-bit address + 8-bit command
        code = ((device & 0xFF) << 8) | (function & 0xFF);
        break;
        
      default:
        // Unknown protocol, combine device and function
        code = ((unsigned long)device << 16) | function;
        break;
    }
    
    return code;
  }
  
  // Get the bit count for the protocol
  static int getProtocolBits(int protocol) {
    switch(protocol) {
      case IRDB_PROTOCOL_NEC1:
      case IRDB_PROTOCOL_NEC2:
      case IRDB_PROTOCOL_SAMSUNG: return 32;
      case IRDB_PROTOCOL_SONY12: return 12;
      case IRDB_PROTOCOL_SONY15: return 15;
      case IRDB_PROTOCOL_SONY20: return 20;
      case IRDB_PROTOCOL_RC5: return 13;
      case IRDB_PROTOCOL_RC6: return 16;
      case IRDB_PROTOCOL_PANASONIC: return 48;
      case IRDB_PROTOCOL_JVC: return 16;
      default: return 32;
    }
  }
  
  // Parse a line from IRDB CSV
  static bool parseLine(const char* line, char* functionName, int& protocol, 
                       int& device, int& subdevice, int& function) {
    // Skip comment lines
    if (line[0] == '#' || strlen(line) == 0) {
      return false;
    }
    
    // Parse CSV: functionname,protocol,device,subdevice,function
    char temp[256];
    strcpy(temp, line);
    
    char* token = strtok(temp, ",");
    if (!token) return false;
    strcpy(functionName, token);
    
    token = strtok(NULL, ",");
    if (!token) return false;
    protocol = atoi(token);
    
    token = strtok(NULL, ",");
    if (!token) return false;
    device = atoi(token);
    
    token = strtok(NULL, ",");
    if (!token) return false;
    subdevice = atoi(token);
    
    token = strtok(NULL, ",");
    if (!token) return false;
    function = atoi(token);
    
    return true;
  }
};

#endif // IRDB_CONVERTER_H