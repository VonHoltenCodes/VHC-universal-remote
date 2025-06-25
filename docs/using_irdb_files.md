# Using IRDB Files with VHC Universal Remote

## Overview
The VHC Universal Remote uses the IRDB (Infrared Database) format exclusively. This provides access to thousands of device codes from the community-maintained IRDB repository.

## Getting IRDB Files

### 1. Browse the IRDB Repository
Visit: https://github.com/probonopd/irdb

Navigate to: `/codes/[Manufacturer]/[Device]/`

Example paths:
- `/codes/Sony/TV/`
- `/codes/Panasonic/VCR/`
- `/codes/Pioneer/Laserdisc_Player/`

### 2. Download Device Files
Each device typically has one or more CSV files named by model or code set.

Example files:
- `1.csv` - Basic codes
- `7,7.csv` - Extended code set
- `RM-V202.csv` - Specific remote model

### 3. Direct CDN Access
You can also download directly via CDN:
```
https://cdn.jsdelivr.net/gh/probonopd/irdb@master/codes/[Manufacturer]/[Device]/[file].csv
```

## IRDB File Format

IRDB files use this format:
```csv
functionname,protocol,device,subdevice,function
POWER,5,1,-1,21
VOLUME+,5,1,-1,18
VOLUME-,5,1,-1,19
```

Fields:
- **functionname**: Button/function name (POWER, VOLUME+, etc.)
- **protocol**: Protocol number (see protocol mappings below)
- **device**: Device code
- **subdevice**: Sub-device code (-1 if not used)
- **function**: Function/command code

## Installing IRDB Files

1. Download IRDB CSV files for your devices
2. Rename files descriptively (e.g., `Sony_TV.csv`, `Pioneer_LD.csv`)
3. Copy all CSV files to the MicroSD card root directory
4. Insert SD card into VHC Remote
5. Power on - each CSV file appears as a device

**Note**: Underscores in filenames are converted to spaces for display.

## IRDB Protocol Numbers

Common protocol mappings:
- 0 = NEC1
- 1 = NEC2
- 2 = RC5 (Philips)
- 3 = RC6
- 5 = Sony 12-bit (SIRC)
- 6 = Sony 15-bit
- 7 = Sony 20-bit
- 8 = Panasonic
- 9 = JVC

## Supported Function Names

The remote recognizes these IRDB function names:
- Power: `POWER`, `KEY_POWER`
- Volume: `VOLUME+`, `VOL+`, `VOLUME-`, `VOL-`
- Channel: `CHANNEL+`, `CH+`, `CHANNEL-`, `CH-`
- Input: `INPUT`, `SOURCE`
- Mute: `MUTE`
- Menu: `MENU`
- OK/Enter: `OK`, `ENTER`, `SELECT`
- Media: `PLAY`, `STOP`, `PAUSE`, `REWIND`, `REW`, `FAST_FORWARD`, `FF`, `RECORD`, `REC`
- Numbers: `0` through `9`

## Example: Setting Up Multiple Devices

1. Visit IRDB repository
2. Download:
   - `Sony/TV/1.csv` → Save as `Sony_TV.csv`
   - `Pioneer/Laserdisc_Player/1.csv` → Save as `Pioneer_LD.csv`
   - `JVC/VCR/2.csv` → Save as `JVC_VCR.csv`
3. Copy all files to SD card
4. Power on VHC Remote
5. Main menu shows: "Sony TV", "Pioneer LD", "JVC VCR"

## Troubleshooting

### Device Not Appearing
- Ensure file has .csv extension
- Check file is in root directory (not in folders)
- Maximum 20 devices supported
- File must contain valid IRDB format

### Commands Not Working
- Try different CSV files for same device
- Some devices have multiple code sets
- Check IR LED is working (use phone camera)
- Ensure you're pointing at device's IR receiver

### Missing Functions
Only recognized function names (see list above) are loaded. The remote focuses on essential functions for simplicity.

## Popular Vintage Devices in IRDB

- **Sony**: Trinitron TVs, Betamax VCRs, early CD players
- **Panasonic**: VHS VCRs, CRT TVs, camcorders
- **Pioneer**: LaserDisc players, receivers, CD players
- **RCA**: ColorTrak TVs, VCRs, VideoDisc players
- **Zenith**: Space Command TVs, VCRs
- **JVC**: VHS VCRs, camcorders, boomboxes
- **Magnavox**: TVs, VCRs, CD players
- **Mitsubishi**: TVs, VCRs, projection systems

## Contributing Back

If you capture codes for devices not in IRDB:
1. Format them in IRDB CSV format
2. Test all functions work
3. Submit pull request to IRDB repository
4. Help preserve vintage device control!

## Resources

- IRDB Repository: https://github.com/probonopd/irdb
- IRDB Browser: http://irdb.tk/
- IR Protocol Info: https://www.sbprojects.net/knowledge/ir/