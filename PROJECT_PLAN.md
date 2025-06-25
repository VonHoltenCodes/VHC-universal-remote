# VHC Universal Remote - Project Management Plan
## Created by VonHoltenCodes
### With development collaboration from Claude Code

**Project Owner**: Trent Von Holten (VonHoltenCodes)  
**Collaborator**: Claude Code (AI Development Assistant)  
**License**: Open Source (TBD)  
**Repository**: https://github.com/VonHoltenCodes/VHC-universal-remote

---

### Project Vision
Create an open-source, Arduino-based universal IR remote using Teensy 4.1 and a 2.8" touchscreen with a retro terminal aesthetic. The project will be modular, well-documented, and easily replicable by the maker community.

**Original Concept & Design**: VonHoltenCodes  
**Development Support**: Claude Code

---

## Phase 1: Foundation & Planning (Current Phase)

### 1.1 Project Structure Setup
- [ ] Create main project directory
- [ ] Set up Arduino sketch structure
- [ ] Create documentation folders
- [ ] Initialize version control
- [ ] Create README with project overview

### 1.2 Hardware Planning
- [ ] Finalize component list with sources
- [ ] Create detailed wiring diagrams
- [ ] Design breadboard layout
- [ ] Plan perfboard/PCB transition
- [ ] Document power requirements

### 1.3 Software Architecture
- [ ] Define modular code structure
- [ ] Create interface abstractions
- [ ] Plan state management system
- [ ] Design error handling approach
- [ ] Define coding standards

---

## Phase 2: Core Development Components

### 2.1 Display System
- [ ] Basic TFT initialization
- [ ] Touch calibration routine
- [ ] Screen buffer management
- [ ] Color theme implementation
- [ ] Font selection and testing

### 2.2 ASCII Art Assets
- [ ] Main logo design (VHC)
- [ ] Splash screen art
- [ ] Menu icons (if needed)
- [ ] Loading animations
- [ ] Button state indicators

### 2.3 Menu System
- [ ] Menu data structures
- [ ] Navigation logic
- [ ] Touch zone mapping
- [ ] Scroll implementation
- [ ] Back button handling

### 2.4 IR System
- [ ] IR LED testing code
- [ ] Protocol support (NEC, Sony, RC5)
- [ ] Timing accuracy verification
- [ ] Repeat functionality
- [ ] Range testing

### 2.5 SD Card Management
- [ ] File system structure
- [ ] CSV parser implementation
- [ ] Error handling for missing files
- [ ] Hot-reload capability
- [ ] Config file support

---

## Phase 3: Integration & Features

### 3.1 Core Integration
- [ ] Merge display + menu systems
- [ ] Integrate IR with menu actions
- [ ] Add SD card data loading
- [ ] Implement full navigation

### 3.2 Advanced Features
- [ ] Search functionality
- [ ] Code learning mode (stretch goal)
- [ ] Macro support (stretch goal)
- [ ] Settings menu
- [ ] About screen with credits

---

## Phase 4: Polish & Release

### 4.1 Testing & Debugging
- [ ] Component testing checklist
- [ ] Integration testing
- [ ] User experience testing
- [ ] Performance optimization
- [ ] Memory usage analysis

### 4.2 Documentation
- [ ] Complete build guide
- [ ] Video tutorial planning
- [ ] Troubleshooting guide
- [ ] Contributing guidelines
- [ ] License selection

### 4.3 Community Release
- [ ] GitHub repository setup
- [ ] Release packaging
- [ ] Community feedback integration
- [ ] Version 1.0 release

---

## Resource Checklists

### Hardware Checklist
- [ ] Teensy 4.1
- [ ] 2.8" ILI9341 TFT with touch (XPT2046)
- [ ] IR LED (940nm)
- [ ] 2N2222 NPN transistor
- [ ] 220Ω resistor (IR LED current limiting)
- [ ] 100Ω resistor (transistor base)
- [ ] 10µF capacitor (power filtering)
- [ ] MicroSD card (minimum 1GB)
- [ ] Breadboard or perfboard
- [ ] Jumper wires
- [ ] USB cable for power
- [ ] Optional: 3D printed case

### Software Requirements
- [ ] Arduino IDE (latest version)
- [ ] Teensyduino addon
- [ ] IRremote library (v4.x)
- [ ] Adafruit_GFX library
- [ ] Adafruit_ILI9341 library
- [ ] XPT2046_Touchscreen library
- [ ] SD library (built-in)

### IR Code Resources
- [ ] LIRC database (http://lirc.org/)
- [ ] IRDB Global (https://www.irdb.global/)
- [ ] Arduino-IRremote code repository
- [ ] Community contributed codes
- [ ] Manual code capture tools

---

## Development Standards

### Code Style
- Use meaningful variable names
- Comment complex logic
- Keep functions under 50 lines
- Use consistent indentation (2 spaces)
- Follow Arduino naming conventions

### Git Commit Format
```
type: brief description

- Detailed change 1
- Detailed change 2

Author: VonHoltenCodes <trentonvonholten@gmail.com>
Co-Authored-By: Claude <noreply@anthropic.com>
```

Types: feat, fix, docs, style, refactor, test, chore

### File Organization
```
VHC_Universal_Remote/
├── VHC_Universal_Remote.ino
├── config.h
├── display.h / display.cpp
├── menu.h / menu.cpp
├── ir_handler.h / ir_handler.cpp
├── sd_manager.h / sd_manager.cpp
├── ascii_art.h
├── README.md
├── docs/
│   ├── build_guide.md
│   ├── wiring_diagram.png
│   └── troubleshooting.md
├── examples/
│   ├── ircodes_template.csv
│   └── test_codes/
└── case_designs/
    └── simple_case.stl
```

---

## Timeline Estimates

- **Phase 1**: 1-2 days (Planning & Setup)
- **Phase 2**: 3-5 days (Component Development)
- **Phase 3**: 2-3 days (Integration)
- **Phase 4**: 2-3 days (Polish & Documentation)

**Total**: 8-13 days for v1.0 release

---

## Success Criteria

1. **Functionality**: Controls at least 3 different devices reliably
2. **Usability**: Intuitive navigation, responsive touch
3. **Aesthetics**: Clean retro terminal look maintained throughout
4. **Documentation**: Complete enough for beginners to build
5. **Community**: At least 5 successful builds by others

---

## Attribution & Credits

**Project Creator**: Trent Von Holten (VonHoltenCodes)
- Original concept and design
- Hardware selection and testing
- Project vision and direction

**Development Collaborator**: Claude Code
- Code architecture assistance
- Documentation support
- Testing recommendations

**Future Contributors**: 
- Community members welcome!
- All contributions will be properly attributed

---

## Notes for Collaboration

- All code stays simple and readable
- Arduino IDE compatibility is mandatory
- No external dependencies beyond listed libraries
- Comments explain the "why", not just "what"
- Test on breadboard before any permanent assembly

This plan is a living document and will be updated as the project progresses.