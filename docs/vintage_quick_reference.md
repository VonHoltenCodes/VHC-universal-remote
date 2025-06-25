# VHC Universal Remote - Vintage Device Quick Reference

## Most Common 1980s-1990s Codes

### Sony Trinitron TV (1980s-1990s)
```
Power: 0xA90 (Sony)
Vol+:  0x490 (Sony)
Vol-:  0xC90 (Sony)
CH+:   0x090 (Sony)
CH-:   0x890 (Sony)
Mute:  0x290 (Sony)
```

### Zenith Space Command (1980s)
```
Power: 0x20DF10EF (NEC)
Vol+:  0x20DF40BF (NEC)
Vol-:  0x20DFC03F (NEC)
CH+:   0x20DF00FF (NEC)
CH-:   0x20DF807F (NEC)
```

### RCA ColorTrak (1980s-1990s)
```
Power: 0x10EF8B74 (NEC)
Vol+:  0x10EF4BB4 (NEC)
Vol-:  0x10EFCB34 (NEC)
CH+:   0x10EFEB14 (NEC)
CH-:   0x10EF1BE4 (NEC)
```

### Panasonic VHS VCR (1980s-1990s)
```
Power:  0x40040D00BCB9 (NEC)
Play:   0x40040500BCB9 (NEC)
Stop:   0x40040000BCB9 (NEC)
Pause:  0x40040600BCB9 (NEC)
Rewind: 0x40040900BCB9 (NEC)
FF:     0x40040800BCB9 (NEC)
Record: 0x40041000BCB9 (NEC)
```

### Pioneer LaserDisc (1980s-1990s)
```
Power: 0xA55A38C7 (NEC)
Play:  0xA55A28D7 (NEC)
Stop:  0xA55A08F7 (NEC)
Pause: 0xA55A48B7 (NEC)
Skip+: 0xA55AD02F (NEC)
Skip-: 0xA55A50AF (NEC)
```

### JVC Equipment (1990s)
```
Power: 0xC5E8 (NEC)
Vol+:  0x35E8 (NEC)
Vol-:  0xB5E8 (NEC)
Play:  0x05E8 (NEC)
Stop:  0x85E8 (NEC)
```

## Device Identification Tips

### Sony Devices
- Look for "Trinitron" badge on TVs
- Model numbers like KV-XXXX
- Usually use Sony protocol (12-bit)

### Zenith TVs
- "Space Command" on remote
- "System 3" models from late 80s
- Distinctive click remotes (pre-IR)

### RCA/GE
- "ColorTrak" or "XL-100" on TVs
- Often shared codes between brands
- Dimensia series (high-end)

### Panasonic/Quasar
- "Gaoo" mascot on some models
- Omnivision VCRs
- Long NEC codes (48-bit)

### Pioneer
- Elite series (high-end)
- LaserDisc players (CLD-XXXX)
- Often gold-colored remotes

## Troubleshooting Vintage Devices

### No Response?
1. Clean IR sensor window (often yellowed)
2. Check if original remote had "TV/VCR" switch
3. Some devices need longer button holds
4. Try from closer distance (sensors degrade)

### Partial Functions?
- Volume might be on TV, not VCR
- Some functions need device in specific mode
- Cable box might intercept some codes

### Common Issues by Era

**1980s Devices**
- Weaker IR sensors (get closer)
- May need exact angle
- Some use non-standard protocols

**Early 1990s**
- Transition period protocols
- Unified remotes becoming common
- Check for "system" remotes

**Late 1990s**
- More standardized codes
- Better range and sensitivity
- Multi-device remotes common

## Pro Tips

1. **Sony Betamax**: Needs repeated sends (3x)
2. **Pioneer LaserDisc**: Side A/B buttons useful
3. **Zenith**: Some models have hidden service codes
4. **RCA**: F-connector TVs often have different codes
5. **Vintage Cable Boxes**: Often override TV remote

## Test Pattern

When setting up a vintage device:
1. Test POWER first
2. Then VOLUME UP/DOWN
3. Then CHANNEL UP/DOWN
4. Finally special functions

Remember: Vintage equipment is why we built this!