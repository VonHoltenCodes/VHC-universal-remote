# VHC Universal Remote - Menu Hierarchy & Navigation

## Screen Flow Diagram

```
[Splash Screen] (5 seconds)
       |
       v
[Main Menu] <--+
   |    |      |
   |    +------+
   |
   +---> [Device Menu] <--+
            |    |        |
            |    +--------+
            |
            +---> [Volume Submenu]
            |           |
            |           v
            |        [Back]
            |
            +---> [Channel Submenu]
            |           |
            |           v
            |        [Back]
            |
            +---> [Input Select]
                     (single action)
```

## Screen Layouts

### 1. Splash Screen (Auto-advance after 5s)
```
+--------------------------------+
|  _   _ _   _ _____             |
| | | | | | | |  __ \            |
| | | | | |_| | |  \/            |
| | | | |  _  | |                |
| \ \_/ / | | | |____            |
|  \___/\_| |_/\____/            |
|                                |
|    UNIVERSAL REMOTE            |
|                                |
| Created by Trent Von Holten    |
|                                |
|     Loading...                 |
+--------------------------------+
```

### 2. Main Menu
```
+--------------------------------+
| VHC                     POWER  |
| ===                    [    ]  |
| UR                             |
|                                |
| Devices:                       |
| +------------------------+     |
| | Samsung TV            |     |
| +------------------------+     |
| | Sony VCR              |     |
| +------------------------+     |
| | LG Soundbar           |     |
| +------------------------+     |
| | Generic DVD           |     |
| +------------------------+     |
|                                |
| [Next >]              [Back]   |
+--------------------------------+
```

### 3. Device Menu
```
+--------------------------------+
| VHC                     POWER  |
| ===                    [    ]  |
| UR                             |
|                                |
| Device: Samsung TV             |
|                                |
| +------------------------+     |
| | Volume                |     |
| +------------------------+     |
| | Channel               |     |
| +------------------------+     |
| | Input                 |     |
| +------------------------+     |
|                                |
|                                |
|                                |
|                       [Back]   |
+--------------------------------+
```

### 4. Volume Submenu
```
+--------------------------------+
| VHC                     POWER  |
| ===                    [    ]  |
| UR                             |
|                                |
| Volume Control                 |
|                                |
| +------------------------+     |
| | Vol Up      ▲        |     |
| +------------------------+     |
|                                |
| +------------------------+     |
| | Vol Down    ▼        |     |
| +------------------------+     |
|                                |
|                                |
|                       [Back]   |
+--------------------------------+
```

### 5. Channel Submenu
```
+--------------------------------+
| VHC                     POWER  |
| ===                    [    ]  |
| UR                             |
|                                |
| Channel Control                |
|                                |
| +------------------------+     |
| | Ch Up       ▲        |     |
| +------------------------+     |
|                                |
| +------------------------+     |
| | Ch Down     ▼        |     |
| +------------------------+     |
|                                |
|                                |
|                       [Back]   |
+--------------------------------+
```

## Touch Zones

### Common Elements (All screens except splash)
- **Logo Area**: (10,10) to (50,40) - No action
- **Power Button**: (240,10) to (310,40) - Send power command for current device

### Main Menu Specific
- **Device Buttons**: 
  - Device 1: (20,60) to (220,90)
  - Device 2: (20,100) to (220,130)
  - Device 3: (20,140) to (220,170)
  - Device 4: (20,180) to (220,210)
- **Next Button**: (220,60) to (300,90) - Next page of devices
- **Back Button**: (20,220) to (100,240) - Disabled (grayed out)

### Device Menu Specific
- **Volume Button**: (20,60) to (140,90) - Go to Volume submenu
- **Channel Button**: (20,100) to (140,130) - Go to Channel submenu
- **Input Button**: (20,140) to (140,170) - Send input command (no submenu)
- **Back Button**: (240,220) to (320,240) - Return to Main Menu

### Submenu Specific
- **Up Button**: (20,60) to (140,90) - Send up command (repeat on hold)
- **Down Button**: (20,100) to (140,130) - Send down command (repeat on hold)
- **Back Button**: (240,220) to (320,240) - Return to Device Menu

## Navigation Logic

### State Management
```c++
enum Screen {
  SCREEN_SPLASH,
  SCREEN_MAIN,
  SCREEN_DEVICE,
  SCREEN_VOLUME,
  SCREEN_CHANNEL
};

Screen currentScreen = SCREEN_SPLASH;
int selectedDevice = 0;
int mainMenuPage = 0;
```

### Touch Handling
1. Check if screen is touched
2. Get calibrated X,Y coordinates
3. Check against active touch zones for current screen
4. Perform appropriate action:
   - Change screen state
   - Send IR command
   - Update display

### Button Repeat Logic
For Volume/Channel controls:
1. On initial touch: Send command immediately
2. If held > 200ms: Send command again
3. Continue repeating every 200ms while held
4. Stop on release

## Special Behaviors

### Power Button
- Always visible (except splash screen)
- Always sends power command for currently selected device
- Visual feedback on press (invert colors briefly)

### Back Button
- On Main Menu: Disabled (grayed out)
- On other screens: Returns to previous screen
- Maintains device selection when navigating

### Menu Refresh
- When returning to Main Menu: Reload device list from SD card
- Allows hot-swapping SD card for updates

### Error States
- No SD Card: Display "Insert SD Card" message
- No devices in CSV: Display "No devices found"
- Invalid touch: Ignore (no action)

## Future Enhancements
- Search/Browse all codes
- Learning mode
- Macro support (multiple commands)
- Settings menu (backlight, touch calibration)
- Device icons instead of text