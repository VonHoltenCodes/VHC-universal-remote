# VHC Universal Remote - IR Code Sources & Resources

## Verified Code Sources

### 1. IRDB - The Ultimate IR Database
**URL**: https://github.com/probonopd/irdb
- Crowd-sourced database with thousands of devices
- CSV format organized by manufacturer/device
- Access via: `https://cdn.jsdelivr.net/gh/probonopd/irdb@master/codes/[Manufacturer]/[Device]/`
- Contains vintage and modern devices

### 2. LIRC Database
**URL**: https://lirc.sourceforge.net/remotes/
- Linux IR Remote Control project
- Extensive collection of remote configs
- Requires conversion from LIRC to Arduino hex format

### 3. RemoteCentral
**URL**: https://www.remotecentral.com/cgi-bin/codes/
- Pronto hex format codes
- Organized by manufacturer
- Good for discrete codes

### 4. Arduino Forums & Projects
- Circuit Basics tutorials
- righto.com IR articles
- Arduino-IRremote GitHub examples

## Code Format Conversions

### IRDB CSV Format
```
functionname,protocol,device,subdevice,function
Power,12,26,48,21
```
Converts to Arduino:
- Protocol 12 = Sony (usually)
- Combine device/function into hex code

### LIRC to Arduino
LIRC shows binary patterns that need conversion:
- Read bits right-to-left
- Convert to hex
- Determine protocol from timing

### Pronto to Arduino
Pronto hex contains raw timing data:
- Use IrScrutinizer software
- Or manual conversion tools

## Common Verified Codes

### Sony SIRC (12-bit)
```
Power:     0xA90
Volume Up: 0x490
Volume Dn: 0xC90
Channel+:  0x090
Channel-:  0x890
Mute:      0x290
```

### Samsung (NEC 32-bit)
```
Power:     0xE0E040BF
Volume Up: 0xE0E0E01F
Volume Dn: 0xE0E0D02F
```

### LG/Goldstar (NEC)
```
Power:     0x20DF10EF
Volume Up: 0x20DF40BF
Volume Dn: 0x20DFC03F
```

## Protocol Notes

### NEC Protocol
- 32-bit total (address + ~address + command + ~command)
- LSB first transmission
- 38kHz carrier
- Example: 0xE0E040BF
  - E0 = address
  - E0 = ~address 
  - 40 = command
  - BF = ~command

### Sony SIRC
- 12, 15, or 20 bits
- Must send 3 times
- 40kHz carrier
- 7-bit command + 5-bit device (12-bit)

### RC5 (Philips)
- 14 bits total
- Toggle bit changes each press
- 36kHz carrier
- MSB first

## Finding Codes for Your Device

1. **Check IRDB first** - Most comprehensive
2. **Use IR receiver** - Capture from original remote
3. **Try common codes** - Many devices share codes
4. **Universal remote databases** - Often list working codes

## Contributing Back

If you capture new codes:
1. Test thoroughly
2. Note exact model numbers
3. Submit to IRDB repository
4. Share in Arduino forums

## Useful Tools

- **IrScrutinizer** - Convert between formats
- **Arduino IRrecvDump** - Capture codes
- **LIRC irsend** - Test codes on Linux
- **AnalysIR** - Commercial IR analyzer