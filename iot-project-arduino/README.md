# Smart Locker System - Arduino Compatible Version

This is an Arduino-compatible version of the ESP32-based smart locker system with fingerprint, RFID, and keypad authentication. It includes support for a 16x2 LCD display.

## Features
- Fingerprint authentication
- RFID card scanning
- Keypad entry
- Web server interface
- Servo-controlled locking mechanism
- Visual and audio feedback
- **NEW: LCD display for status updates**

## Hardware Requirements
- ESP32 development board
- Fingerprint sensor (GT-511C3 or similar)
- RFID module (MFRC522)
- 4x4 matrix keypad
- Servo motor
- LEDs (red, green, blue)
- Buzzer
- **16x2 LCD display (HD44780 compatible)**

## Pin Connections
### LCD Display
- RS: GPIO 33
- Enable: GPIO 25
- D4: GPIO 26
- D5: GPIO 27
- D6: GPIO 14
- D7: GPIO 12

### Other Components
- Servo: GPIO 15
- Red LED: GPIO 22
- Green LED: GPIO 21
- Blue LED: GPIO 2
- Buzzer: GPIO 4
- Fingerprint TX: GPIO 16
- Fingerprint RX: GPIO 17
- RFID SDA(SS): GPIO 5
- RFID RST: GPIO 21
- Keypad rows: GPIO 32, 33, 25, 26
- Keypad columns: GPIO 27, 14, 12, 13

## Libraries Required
- Adafruit Fingerprint Sensor Library
- MFRC522
- Keypad
- ArduinoJson
- ESP32Servo
- WiFi
- HTTPClient
- **LiquidCrystal (for LCD)**

## Setup Instructions
1. Install required libraries via Arduino Library Manager
2. Connect hardware components according to pin connections above
3. Update WiFi credentials in config.h
4. Upload the sketch to your ESP32
5. Access the web interface using the IP address displayed on the LCD and serial monitor

## LCD Display Information
The integrated 16x2 LCD provides real-time feedback:
- Shows welcome message on startup
- Displays access granted/denied messages with method and user ID
- Shows system status ("SYSTEM READY" when idle)
- Updates periodically during operation

## Web Interface
The system hosts a web server on port 80 with basic authentication:
- Username: admin
- Password: smartlock2025
- Control locking/unlocking remotely
- Monitor system status

## Troubleshooting
- If LCD doesn't work, check pin connections and ensure LiquidCrystal library is installed
- For authentication issues, verify all sensors are properly connected
- Check serial monitor for error messages during initialization