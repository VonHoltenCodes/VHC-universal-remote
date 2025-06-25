# VHC Universal Remote - IR Codes Guide

## Overview
This guide covers the IR code database structure and how to add your own device codes.

## Included Device Categories

### Vintage TVs (1980s-1990s)
- **Sony Trinitron** - Classic CRT TVs with Sony protocol
- **Zenith Space Command** - Revolutionary wireless remotes
- **RCA ColorTrak** - Popular American brand TVs
- **Magnavox** - Philips-owned brand common in the US
- **Toshiba** - Japanese CRTs with reliable remotes
- **Mitsubishi** - High-end CRT TVs

### Vintage VCRs
- **Sony Betamax** - The original home video format
- **Panasonic/JVC VHS** - The winning video format
- **RCA/GE VCRs** - American market leaders
- **Fisher VCRs** - High-quality Japanese VCRs

### Vintage Audio Equipment
- **Pioneer** - Elite receivers and LaserDisc players
- **Technics** - Panasonic's premium audio brand
- **Marantz** - Audiophile-grade receivers
- **Yamaha/Onkyo/Denon** - Japanese audio excellence
- **Aiwa** - Affordable quality audio

### Specialty Vintage
- **Commodore 1702 Monitor** - Classic computer monitor
- **Pioneer LaserDisc** - The videophile's choice
- **Scientific Atlanta Cable Box** - Early cable TV
- **Vintage Camcorders** - Sony, JVC, Panasonic

## File Formats

### Main File: `ircodes.csv`
The primary codes file that loads on startup. Contains the most common and verified codes.

### Format
```csv
device,command,code,protocol
Sony Trinitron,power,0xA90,Sony
```

### Supported Protocols
1. **NEC** - Most common, 32-bit codes (0xXXXXXXXX)
2. **Sony** - 12/15/20-bit codes (0xXXX)
3. **RC5** - Philips protocol, 12-bit codes

## Adding Your Own Codes

### Method 1: Edit CSV File
1. Remove SD card from Teensy
2. Edit `ircodes.csv` on computer
3. Add new device section:
```csv
# === MY DEVICE ===
My Device Name,power,0xXXXXXXXX,NEC
My Device Name,volUp,0xXXXXXXXX,NEC
```

### Method 2: Code Learning (Future Feature)
Planned feature to learn codes directly from existing remotes.

## Finding IR Codes

### Online Resources
1. **LIRC Database** - http://lirc.org/
2. **IR Remote Codes** - https://www.remotecentral.com/
3. **Arduino IR Database** - GitHub repositories

### Using an IR Receiver
1. Connect IR receiver to Arduino
2. Use IRremote library example sketch
3. Point original remote and press buttons
4. Record the protocol and hex codes

### Common Code Formats
- **Pronto Hex** - Convert to raw
- **Raw Timing** - Convert to protocol/hex
- **Decimal** - Convert to hex

## Troubleshooting Codes

### Code Not Working?
1. **Wrong Protocol** - Try NEC if unsure
2. **Bit Length** - Sony uses 12/15/20 bits
3. **Repeat Requirements** - Some devices need multiple sends
4. **Inverted Codes** - Try inverting the hex

### Testing Tips
1. Use phone camera to see IR LED flash
2. Start with power button
3. Test from 3-6 feet away
4. Point directly at device sensor

## Code Organization Tips

### Grouping by Brand
```csv
# === SONY DEVICES ===
Sony TV Model 1,power,0xA90,Sony
Sony TV Model 1,volUp,0x490,Sony
Sony TV Model 2,power,0xA91,Sony
Sony TV Model 2,volUp,0x491,Sony
```

### Grouping by Function
```csv
# === POWER CODES ===
Device 1,power,0xXXXX,NEC
Device 2,power,0xXXXX,NEC
# === VOLUME CODES ===
Device 1,volUp,0xXXXX,NEC
Device 1,volDown,0xXXXX,NEC
```

## Popular Vintage Brands Reference

### 1980s Leaders
- **Sony** - Trinitron TVs, Betamax
- **Panasonic** - VHS VCRs, TVs
- **RCA** - ColorTrak TVs
- **Zenith** - Space Command remotes
- **Pioneer** - LaserDisc, audio

### 1990s Additions
- **Toshiba** - CRT TVs
- **JVC** - VHS, TV/VCR combos
- **Mitsubishi** - Large screen TVs
- **Philips/Magnavox** - RC5 protocol

## Contributing Codes

If you have verified codes for vintage devices:
1. Test thoroughly with your device
2. Document the exact model number
3. Submit via GitHub pull request
4. Include device photo if possible

## Code Database Stats
- **Total Devices**: 50+ vintage models
- **Total Commands**: 400+ verified codes
- **Protocols**: NEC (70%), Sony (20%), RC5 (10%)
- **Era Coverage**: 1980-2000 primarily

Remember: The charm of this project is controlling vintage equipment that predates modern universal remotes!