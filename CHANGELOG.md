# VHC Universal Remote - Changelog

All notable changes to this project will be documented in this file.

## [Unreleased]

### Phase 4 - Testing & Refinement
- Hardware testing with real devices
- Performance optimization
- Memory usage analysis
- User experience improvements

## [0.4.0] - 2024-06-25
### Changed - IRDB Only Implementation
- Removed original CSV format support entirely
- Simplified to use IRDB format exclusively
- Cleaner codebase with single format focus
- Updated all documentation for IRDB-only approach

### Removed
- Original CSV format parsing
- Dual format detection logic
- Legacy format examples

## [0.3.0] - 2024-06-24
### Added - IRDB Integration 🎉
- Full IRDB database support with thousands of device codes
- Automatic CSV format detection (Original vs IRDB)
- IRDB to hex code converter module (`irdb_converter.h`)
- Extended protocol support: RC6, Panasonic, JVC
- Comprehensive IRDB usage documentation
- Function name mapping for IRDB compatibility

### Changed
- SD Manager now supports dual CSV formats
- IR Handler extended for all IRDB protocols
- Menu system updated for new command formats

## [0.2.0] - 2024-06-24
### Added - Core Functionality
- Modular code architecture implementation
- Display module with retro red-on-black theme
- Touch input handling with zone mapping
- Menu navigation system
- IR transmission for NEC, Sony, RC5
- SD card manager with CSV parsing
- Graphical VHC logo animation
- Power button accessible from all screens
- Volume/Channel controls with repeat

### Changed
- Logo design from ASCII art to graphical blocks
- Improved error handling throughout

## [0.1.0] - 2024-06-24
### Added - Project Foundation
- Initial project structure and planning
- Hardware design and parts list
- Wiring diagrams and assembly guide
- ASCII art assets and UI mockups
- Basic Arduino sketch structure
- Documentation framework
- Attribution: VonHoltenCodes (Creator), Claude Code (Collaborator)

## Attribution
**Created by**: VonHoltenCodes  
**Development Support**: Claude Code  
**IR Database**: IRDB Project Contributors