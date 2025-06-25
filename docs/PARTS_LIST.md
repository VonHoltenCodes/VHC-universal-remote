# VHC Universal Remote - Verified Parts List

## Core Components

### 1. Microcontroller
**Teensy 4.1** (with headers)
- Part Number: TEENSY41
- Supplier: PJRC, Adafruit, SparkFun
- Price: ~$30-35
- Link: https://www.pjrc.com/store/teensy41.html
- Notes: Get version WITH headers pre-soldered for easier breadboarding

### 2. Display
**2.8" TFT LCD with Touchscreen Breakout Board w/MicroSD Socket - ILI9341**
- Part Number: Adafruit #1770
- Supplier: Adafruit
- Price: ~$30
- Link: https://www.adafruit.com/product/1770
- Specifications:
  - 240x320 resolution
  - ILI9341 display controller
  - XPT2046/STMPE610 touch controller
  - Built-in MicroSD slot (not used - we use Teensy's)
  - 3.3V logic compatible

**Alternative (cheaper option):**
- Generic 2.8" ILI9341 with touch from Amazon/eBay
- Search: "2.8 inch ILI9341 TFT LCD Touch Screen 240x320"
- Price: ~$10-15
- Note: Quality varies, but most work fine

### 3. IR LED
**Super Bright IR LED - 940nm**
- Part Number: Adafruit #387
- Supplier: Adafruit
- Price: ~$1
- Link: https://www.adafruit.com/product/387
- Specifications:
  - 940nm wavelength (standard for remotes)
  - 20 degree beam angle
  - 1.2-1.5V forward voltage

**Alternative bulk option:**
- Search: "940nm IR LED 5mm"
- Get 10-pack from Amazon for ~$5

### 4. Transistor
**2N2222 NPN Transistor**
- Part Number: 2N2222A
- Supplier: Multiple (Adafruit #756, SparkFun, Mouser)
- Price: ~$0.50 each
- Specifications:
  - TO-92 package (plastic case)
  - 600mA collector current max
  - 40V max voltage

### 5. Resistors
**Resistor Kit or Individual:**
- 220Ω resistor (Red-Red-Brown) - for IR LED
- 100Ω resistor (Brown-Black-Brown) - for transistor base
- Supplier: Any electronics supplier
- Price: ~$0.10 each or $10 for assortment kit

### 6. Capacitor
**10µF Electrolytic Capacitor**
- Voltage: 16V or higher
- Part Number: Generic
- Price: ~$0.25
- Note: Observe polarity when installing

### 7. MicroSD Card
**MicroSD Card - 1GB to 32GB**
- Format: Must support FAT32
- Recommended: SanDisk or Kingston
- Price: ~$5-10
- Note: Larger cards work but aren't necessary

## Prototyping Supplies

### Breadboard
**Half-size or Full-size Breadboard**
- Recommended: 830 tie points
- Part Number: Adafruit #64 or similar
- Price: ~$5-8

### Jumper Wires
**Jumper Wire Bundle**
- Need: Male-to-Male and Male-to-Female
- Recommended: 65-piece flexible wire bundle
- Part Number: Adafruit #758
- Price: ~$6

### USB Cable
**USB Micro-B Cable**
- Length: 3-6 feet recommended
- Note: Get a quality cable for reliable power
- Price: ~$5-10

## Optional Enhancements

### For Permanent Assembly
1. **Perma-Proto Board** (Adafruit #1609) - ~$5
2. **Female Headers** for display connection - ~$2
3. **Male Pin Headers** for Teensy - ~$2
4. **22 AWG Solid Core Wire** for clean wiring - ~$5

### For Professional Finish
1. **3D Printed Case** (files in project)
2. **Panel Mount Micro USB** (Adafruit #3258) - ~$3
3. **Light Pipe** for IR LED - ~$1
4. **Anti-glare Screen Protector** (cut to size) - ~$5

## Complete Shopping Lists

### Budget Build (~$65)
- Teensy 4.1 (with headers) - $32
- Generic ILI9341 Display - $12
- IR LED (5-pack) - $5
- 2N2222 Transistor - $1
- Resistor Kit - $5
- 10µF Capacitor - $1
- Breadboard - $5
- Jumper Wires - $4
- MicroSD Card - (use existing)

### Premium Build (~$95)
- Teensy 4.1 (with headers) - $32
- Adafruit ILI9341 Display - $30
- Adafruit Super Bright IR LED - $1
- 2N2222 Transistor - $1
- Precision Resistors - $2
- 10µF Capacitor - $1
- Quality Breadboard - $8
- Premium Jumper Wires - $6
- SanDisk MicroSD 8GB - $8
- USB Cable - $6

### Permanent Installation Add-ons (~$20)
- Perma-Proto Board - $5
- Headers and Pins - $4
- Solid Core Wire - $5
- Heat Shrink Tubing - $3
- Mounting Hardware - $3

## Supplier Links

### Primary Suppliers
1. **PJRC** (https://www.pjrc.com) - Teensy boards
2. **Adafruit** (https://www.adafruit.com) - Quality components
3. **SparkFun** (https://www.sparkfun.com) - Alternative source
4. **Mouser** (https://www.mouser.com) - Wide selection
5. **DigiKey** (https://www.digikey.com) - Professional parts

### Budget Suppliers
1. **Amazon** - Fast shipping, variable quality
2. **eBay** - Cheapest prices, slow shipping
3. **AliExpress** - Bulk quantities, very slow shipping

## Buying Tips

1. **Teensy 4.1**: Always buy genuine from PJRC or authorized dealers
2. **Display**: Adafruit version is higher quality but generic works
3. **IR LED**: Get extras - they're cheap and can burn out
4. **Resistors**: Buy a kit for future projects
5. **Breadboard**: Don't go too cheap - bad connections are frustrating

## Estimated Total Cost
- **Minimum**: $60-65 (with generic parts)
- **Recommended**: $85-95 (quality parts)
- **Deluxe**: $100-120 (with case and permanent assembly)

## Notes
- All parts are commonly available and verified to work
- Prices are approximate USD as of 2024
- Many components can be salvaged from old electronics
- Check local electronics stores for immediate availability