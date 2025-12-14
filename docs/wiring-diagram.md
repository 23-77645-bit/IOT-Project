# Smart Locker System Wiring Diagram

## Components Connection

### ESP32 Pin Connections

| Component | ESP32 Pin | Notes |
|-----------|-----------|-------|
| Servo Motor | GPIO 15 | Control signal |
| Red LED | GPIO 22 | Status indicator |
| Green LED | GPIO 21 | Status indicator |
| Blue LED | GPIO 2 | Status indicator |
| Buzzer | GPIO 4 | Audio feedback |
| Fingerprint Sensor TX | GPIO 16 | Software Serial |
| Fingerprint Sensor RX | GPIO 17 | Software Serial |
| RFID SDA/SS | GPIO 5 | SPI Communication |
| RFID RST | GPIO 21 | Reset pin |
| Keypad Row 1 | GPIO 32 | 4x4 Matrix Keypad |
| Keypad Row 2 | GPIO 33 | |
| Keypad Row 3 | GPIO 25 | |
| Keypad Row 4 | GPIO 26 | |
| Keypad Col 1 | GPIO 27 | |
| Keypad Col 2 | GPIO 14 | |
| Keypad Col 3 | GPIO 12 | |
| Keypad Col 4 | GPIO 13 | |

### Power Connections

- **VCC (5V)**: Connect all components requiring 5V power
- **GND**: Common ground connection for all components

### Circuit Diagram

```
ESP32 Development Board
├── Power
│   ├── 5V ──── VCC (Servo, LEDs, Buzzer, Fingerprint, RFID, Keypad)
│   └── GND ─── GND (All components)
├── Digital I/O
│   ├── GPIO 15 ─── Servo Signal
│   ├── GPIO 22 ─── Red LED
│   ├── GPIO 21 ─── Green LED
│   ├── GPIO 2 ──── Blue LED
│   ├── GPIO 4 ──── Buzzer
│   ├── GPIO 16 ─── Fingerprint TX
│   ├── GPIO 17 ─── Fingerprint RX
│   ├── GPIO 5 ──── RFID SDA/SS
│   ├── GPIO 21 ─── RFID RST
│   ├── GPIO 32 ─── Keypad Row 1
│   ├── GPIO 33 ─── Keypad Row 2
│   ├── GPIO 25 ─── Keypad Row 3
│   ├── GPIO 26 ─── Keypad Row 4
│   ├── GPIO 27 ─── Keypad Col 1
│   ├── GPIO 14 ─── Keypad Col 2
│   ├── GPIO 12 ─── Keypad Col 3
│   └── GPIO 13 ─── Keypad Col 4
└── SPI Interface (for RFID)
    ├── SCK ─── GPIO 18 (Default)
    ├── MISO ── GPIO 19 (Default)
    └── MOSI ── GPIO 23 (Default)
```

### Power Requirements

- **ESP32**: 3.3V (can be powered via USB or external 3.3V supply)
- **Servo**: 5V (recommended 4.8V-6V, 200mA-300mA)
- **LEDs**: 3.3V-5V (current limited with resistors)
- **Buzzer**: 3.3V-5V
- **Fingerprint Sensor**: 3.3V-5V
- **RFID Module**: 3.3V-5V
- **Keypad**: 3.3V-5V

### Notes

1. Use appropriate current limiting resistors for LEDs
2. Consider using a separate power supply for servo to avoid brownouts
3. Ensure proper grounding of all components
4. Use appropriate level shifters if connecting 5V components to 3.3V ESP32
5. Connect all grounds together to establish a common reference