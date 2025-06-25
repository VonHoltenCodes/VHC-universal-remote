# VHC Universal Remote
## A touchscreen universal IR remote built with Teensy 4.1

Created by **VonHoltenCodes** with development collaboration from **Claude Code**

### Overview
This project creates a standalone universal IR remote control using:
- Teensy 4.1 microcontroller
- 2.8" ILI9341 touchscreen display with XPT2046 touch controller
- IR LED and driver circuit for device control
- MicroSD card for storing IR codes
- Retro red-on-black terminal aesthetic with animated graphical logo

### Features
- **Touch-based interface** with graphical VHC logo animation
- **Multiple device support** - Control up to 20 devices
- **IRDB database format** - Uses the community-maintained IRDB repository
- **Extended protocol support** - NEC, Sony SIRC, RC5, RC6, Panasonic, JVC
- **IRDB integration** - Compatible with thousands of devices from IRDB repository
- **Volume/channel controls** with repeat functionality
- **Vintage device focus** - Prioritizes 1980s+ electronics
- **Modular architecture** - Clean, maintainable code structure
- **Power button** always accessible from any screen

### Current Status
✅ **Phase 1 Complete** - Foundation, planning, and architecture  
✅ **Phase 2 Complete** - Core modules (display, touch, IR, menu)  
✅ **Phase 3 Complete** - SD integration, IRDB support, protocol extensions  
🚧 **Phase 4 In Progress** - Testing and refinement  
⏳ **Phase 5 Upcoming** - Final documentation and release

### Quick Start
1. Gather components (see [docs/PARTS_LIST.md](docs/PARTS_LIST.md))
2. Wire according to [wiring diagram](docs/wiring_diagram.md)
3. Install Arduino IDE and Teensyduino
4. Install required libraries:
   - Adafruit GFX Library
   - Adafruit ILI9341
   - XPT2046_Touchscreen
   - IRremote (v3.x or higher)
5. Open `VHC_Universal_Remote.ino` and upload to Teensy 4.1
6. Add IR code files to MicroSD card (see [Using IRDB Files](docs/using_irdb_files.md))
7. Power on and enjoy your custom remote!

### Documentation
- [Project Plan](PROJECT_PLAN.md) - Development roadmap and milestones
- [Parts List](docs/PARTS_LIST.md) - Complete bill of materials
- [Hardware Assembly](docs/hardware_assembly.md) - Step-by-step build guide
- [Wiring Diagram](docs/wiring_diagram.md) - Connection details
- [Menu Hierarchy](docs/menu_hierarchy.md) - UI structure and navigation
- [IR Codes Guide](docs/ir_codes_guide.md) - Understanding IR protocols
- [Using IRDB Files](docs/using_irdb_files.md) - How to use community IR codes
- [Vintage Quick Reference](docs/vintage_quick_reference.md) - Popular retro devices

### IR Code Source
The remote uses IRDB format exclusively:

```csv
functionname,protocol,device,subdevice,function
POWER,5,1,-1,21
VOLUME+,5,1,-1,18
```

Get thousands of device codes from: https://github.com/probonopd/irdb

### Contributing
This is an open-source project! Contributions welcome:
- Test with your vintage devices
- Submit verified IR codes
- Improve documentation
- Report bugs and issues

### License
This project is open source and available under the MIT License.

### Credits
- **Project Creator**: Trent Von Holten (VonHoltenCodes)
- **Development Support**: Claude Code
- **IR Database**: [IRDB Project](https://github.com/probonopd/irdb)
- **Community**: Future contributors and testers

### Acknowledgments
Special thanks to:
- The IRDB maintainers for the comprehensive IR code database
- Arduino and Teensy communities for libraries and support
- Vintage electronics enthusiasts keeping retro tech alive

---
*For the latest updates and releases, visit the [GitHub repository](https://github.com/VonHoltenCodes/VHC-universal-remote)*