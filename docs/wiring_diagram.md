# VHC Universal Remote - Wiring Diagram

## Visual ASCII Wiring Diagram

```
                              Teensy 4.1
                    +-------------------------+
                    |                         |
                    | [USB]            [SD]   |
                    |                         |
                    | 3.3V ←─────────────┐   |
                    | GND  ←───────────┐ │   |
                    | 5V   ←─────────┐ │ │   |
                    |                │ │ │   |
                    | 15 ←─────┐     │ │ │   |
                    | 14 ←───┐ │     │ │ │   |
                    | 13 ←─┐ │ │     │ │ │   |
                    | 12 ←┐│ │ │     │ │ │   |
                    | 11 ←┐││ │ │     │ │ │   |
                    | 10 ←┐│││ │ │     │ │ │   |
                    |  9 ←┐││││ │ │     │ │ │   |
                    |  8 ←┐│││││ │ │     │ │ │   |
                    |  6 ←┐│││││││ │     │ │ │   |
                    |    ││││││││ │     │ │ │   |
                    +----││││││││-│-----│-│-│---+
                         ││││││││ │     │ │ │
                         ││││││││ │     │ │ └───→ [BLACK] GND
                         ││││││││ │     │ └─────→ [RED] 3.3V
                         ││││││││ │     └───────→ [ORANGE] 5V
                         ││││││││ │
    +--------------------││││││││-│----------------+
    |  2.8" ILI9341 TFT  ││││││││ │                |
    |                    ││││││││ │                |
    | VCC    ←───────────┼┼┼┼┼┼┼┼─┘ (3.3V)        |
    | GND    ←───────────┼┼┼┼┼┼┼┼───────┐          |
    | CS     ←───────────┘│││││││       │          |
    | RESET  ←────────────┘││││││       │          |
    | DC     ←─────────────┘│││││       │          |
    | SDI    ←──────────────┘││││       │          |
    | SCK    ←───────────────┘│││       │          |
    | LED    ←────────────────┘││       │          |
    | SDO    ←─────────────────┘│       │          |
    |                           │       │          |
    | === Touch Section ===     │       │          |
    | T_CLK  ←──────────────────┘ (13)  │          |
    | T_CS   ←────────────────────────┐ │          |
    | T_DIN  ←──────────────┐ (11)    │ │          |
    | T_DO   ←───────┐ (12) │         │ │          |
    | T_IRQ  (NC)    │      │         │ │          |
    |                │      │         │ │          |
    +----------------│------│---------│-│----------+
                     │      │         │ │
                     └──────┴─────────┘ │
                                        │
                            Pin 8 ←─────┘

    IR LED Circuit:
    ===============
                    5V (Orange)
                     │
                     │
                   [220Ω]
                     │
                     ├──→ LED Cathode (-)
                   [IR LED]
                     ├──→ LED Anode (+)
                     │
                     C (Collector)
                    ╱
    Pin 6 ──[100Ω]─B  2N2222 NPN
                    ╲
                     E (Emitter)
                     │
                     │
                    GND (Black)

    Power Supply Filter:
    ===================
         5V ──┬── To circuits
              │
            [10µF]
              │
            GND
```

## Connection Color Code
- **Red**: Power (3.3V)
- **Orange**: Power (5V)
- **Black**: Ground
- **Blue**: Data signals (MOSI)
- **Purple**: Clock signals (SCK)
- **Gray**: Data return (MISO)
- **Green**: Control signals (DC)
- **Yellow**: Reset
- **White**: PWM (Backlight)
- **Brown**: Chip selects

## Breadboard Layout

```
    A B C D E     F G H I J
  +-------------------------+
1 | ○ ○ ○ ○ ○     ○ ○ ○ ○ ○ | ← 5V Rail (Orange)
2 | ○ ○ ○ ○ ○     ○ ○ ○ ○ ○ | ← 3.3V Rail (Red)
3 | ○ ○ ○ ○ ○     ○ ○ ○ ○ ○ | ← GND Rail (Black)
  |                         |
5 | T E E N S     Y 4 . 1   | ← Teensy placement
6 | ○ ○ ○ ○ ○     ○ ○ ○ ○ ○ |   spans rows 5-25
  |   ... (pins) ...        |
  |                         |
26| ○ ● ● ○ ○     ○ ○ ○ ○ ○ | ← 2N2222 (BCE)
27| ○ │ │ │ ○     ○ ○ ○ ○ ○ | ← 100Ω resistor
28| ○ │ │ └───────● ○ ○ ○ ○ | ← To Pin 6
29| ○ │ └─────────● ● ● ○ ○ | ← 220Ω + IR LED
30| ○ └───────────────● ○ ○ | ← To GND
  +-------------------------+
```

## Quick Reference Table

| Component | Pin/Connection | Notes |
|-----------|---------------|-------|
| **Display Power** | | |
| VCC | 3.3V | Use 3.3V, not 5V |
| GND | GND | Common ground |
| **Display SPI** | | |
| SDI (MOSI) | Pin 11 | SPI data to display |
| SDO (MISO) | Pin 12 | SPI data from display |
| SCK | Pin 13 | SPI clock |
| CS | Pin 10 | Display chip select |
| DC | Pin 9 | Data/Command select |
| RESET | Pin 14 | Display reset |
| LED | Pin 15 | Backlight PWM |
| **Touch SPI** | | |
| T_DIN | Pin 11 | Shared with display |
| T_DO | Pin 12 | Shared with display |
| T_CLK | Pin 13 | Shared with display |
| T_CS | Pin 8 | Touch chip select |
| T_IRQ | NC | Not connected |
| **IR Circuit** | | |
| Base | Pin 6 → 100Ω | Transistor control |
| Collector | IR LED (+) | LED anode |
| Emitter | GND | Ground |
| LED (-) | 220Ω → 5V | LED cathode |

## Important Notes

1. **SPI Bus Sharing**: The display and touch controller share the SPI bus (MOSI, MISO, SCK) but have separate chip select lines.

2. **Power Requirements**: 
   - Display uses 3.3V (check your specific module)
   - IR LED circuit uses 5V for better range
   - Total current ~150mA typical

3. **Wire Lengths**: Keep SPI wires under 6 inches for reliable operation at high speeds.

4. **Teensy Orientation**: USB port should be accessible for programming and power.

5. **Heat Dissipation**: The 2N2222 transistor may get warm during extended use - this is normal.