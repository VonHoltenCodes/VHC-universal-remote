# VHC Universal Remote - Hardware Assembly Guide

## Component Checklist

### Required Components
- [ ] **Teensy 4.1** - Main microcontroller
- [ ] **2.8" ILI9341 TFT Display** - 240x320 pixels with XPT2046 touch controller
- [ ] **IR LED** - 940nm wavelength (standard TV remote LED)
- [ ] **2N2222 NPN Transistor** - For IR LED switching
- [ ] **220Ω Resistor** - Current limiting for IR LED
- [ ] **100Ω Resistor** - Base current limiting for transistor
- [ ] **10µF Capacitor** - Power supply filtering
- [ ] **MicroSD Card** - Minimum 1GB, formatted as FAT32
- [ ] **Breadboard** - For prototyping
- [ ] **Jumper Wires** - Male-to-male and male-to-female
- [ ] **USB Cable** - Micro-USB for Teensy 4.1

### Optional Components
- [ ] **Perfboard** - For permanent assembly
- [ ] **Pin Headers** - For modular connections
- [ ] **3D Printed Case** - See case_designs folder
- [ ] **Hot Glue** - For securing components

## Wiring Diagram

```
Teensy 4.1 Pin Connections
==========================

Display (ILI9341) Connections:
------------------------------
TFT Pin         Teensy Pin      Wire Color (suggested)
-------         ----------      ---------------------
VCC             3.3V            Red
GND             GND             Black
CS              10              Orange
RESET           14              Yellow
DC              9               Green
SDI (MOSI)      11              Blue
SCK             13              Purple
LED             15              White
SDO (MISO)      12              Gray

Touch Controller (XPT2046) Connections:
---------------------------------------
Touch Pin       Teensy Pin      Wire Color (suggested)
---------       ----------      ---------------------
T_CLK           13 (shared)     Purple
T_CS            8               Brown
T_DIN           11 (shared)     Blue
T_DO            12 (shared)     Gray
T_IRQ           (not connected)

IR LED Circuit:
---------------
Component       Connection
---------       ----------
IR LED Anode    → 2N2222 Collector
IR LED Cathode  → 220Ω → 5V
2N2222 Base     → 100Ω → Teensy Pin 6
2N2222 Emitter  → GND
10µF Cap        → Between 5V and GND

SD Card:
--------
Uses Teensy 4.1 built-in MicroSD slot
```

## Assembly Steps

### Step 1: Prepare the Breadboard
1. [ ] Place Teensy 4.1 on breadboard with USB port accessible
2. [ ] Create power rails: 5V, 3.3V, and GND
3. [ ] Add 10µF capacitor between 5V and GND rails

### Step 2: Connect the Display
1. [ ] Mount TFT display on breadboard or use jumper wires
2. [ ] Connect power: VCC to 3.3V, GND to GND
3. [ ] Connect SPI pins: MOSI, MISO, SCK
4. [ ] Connect control pins: CS, DC, RESET
5. [ ] Connect backlight: LED to Pin 15
6. [ ] Connect touch controller pins (shares SPI)

### Step 3: Build IR LED Circuit
1. [ ] Place 2N2222 transistor on breadboard
2. [ ] Connect IR LED anode to collector
3. [ ] Connect IR LED cathode through 220Ω to 5V
4. [ ] Connect base through 100Ω to Pin 6
5. [ ] Connect emitter to GND

### Step 4: Prepare SD Card
1. [ ] Format MicroSD card as FAT32
2. [ ] Copy ircodes.csv template to root directory
3. [ ] Customize with your device codes
4. [ ] Insert into Teensy 4.1 slot

### Step 5: Power Connections
1. [ ] Connect USB cable to Teensy
2. [ ] Verify 5V and 3.3V rails with multimeter
3. [ ] Check all ground connections

## Testing Checklist

### Initial Power-On Test
1. [ ] Connect USB power
2. [ ] Teensy LED should light up
3. [ ] Display backlight should turn on
4. [ ] No components getting hot

### Display Test
1. [ ] Upload test sketch (see examples folder)
2. [ ] Display should show splash screen
3. [ ] Colors should be correct (red on black)
4. [ ] No flickering or artifacts

### Touch Test
1. [ ] Touch corners of screen
2. [ ] Verify coordinates in serial monitor
3. [ ] Check for dead zones
4. [ ] Test touch responsiveness

### IR LED Test
1. [ ] Use phone camera to see IR LED
2. [ ] LED should glow purple when active
3. [ ] Test range (5-10 meters typical)
4. [ ] Verify with known device

### SD Card Test
1. [ ] Check card detection
2. [ ] Verify file reading
3. [ ] Test hot-swap capability
4. [ ] Check error handling

## Troubleshooting

### Display Issues
- **No display**: Check power and SPI connections
- **White screen**: Check RESET pin connection
- **Wrong colors**: Verify DC pin and initialization
- **Flickering**: Add more capacitance, check power supply

### Touch Issues
- **No response**: Check T_CS pin and SPI connections
- **Wrong coordinates**: Recalibrate touch screen
- **Intermittent**: Check for loose connections

### IR LED Issues
- **No IR output**: Check transistor orientation
- **Weak signal**: Increase LED current (lower resistor value)
- **No response**: Verify IR codes and protocol

### SD Card Issues
- **Not detected**: Check card format (must be FAT32)
- **Read errors**: Try different card, check connections
- **File not found**: Verify filename and path

## Safety Notes

1. **Static Protection**: Teensy is sensitive to static. Use anti-static precautions.
2. **Power Limits**: Do not exceed 5V on any pin except VIN
3. **Current Limits**: Each pin max 10mA, total max 100mA
4. **Heat**: IR LED and transistor may get warm during use
5. **Polarity**: Double-check LED and capacitor polarity

## Next Steps

Once hardware is assembled and tested:
1. Upload the main sketch
2. Customize IR codes for your devices
3. Consider permanent assembly on perfboard
4. Design and print a case
5. Share your build with the community!

## Pin Reference Card

Print and keep handy:
```
Teensy 4.1 - VHC Remote Pinout
==============================
Pin  | Function       | Connect To
-----|----------------|------------
6    | IR LED Control | 100Ω → 2N2222 Base
8    | Touch CS       | T_CS
9    | Display DC     | DC
10   | Display CS     | CS
11   | SPI MOSI       | SDI/T_DIN
12   | SPI MISO       | SDO/T_DO
13   | SPI Clock      | SCK/T_CLK
14   | Display Reset  | RESET
15   | Backlight PWM  | LED
GND  | Ground         | Common Ground
3.3V | Display Power  | VCC
5V   | IR LED Power   | Through 220Ω
```