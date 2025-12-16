# Smart Locker System - Arduino Compatible Version

This is an Arduino-compatible version of the Smart Locker System originally built with PlatformIO. 

## Project Structure
- `iot-project-arduino.ino` - Main Arduino sketch file
- `include/` - Header files for various modules

## Dependencies
This project requires the following libraries to be installed in your Arduino IDE:
1. Adafruit Fingerprint Sensor Library
2. MFRC522
3. Keypad
4. ArduinoJson
5. ESP32Servo
6. WiFi
7. HTTPClient

Install these via the Arduino Library Manager (Tools > Manage Libraries).

## Configuration
Edit the values in `include/config.h` to match your setup:
- WiFi credentials
- Server IP address
- Pin configurations
- Passwords

## Usage
Open `iot-project-arduino.ino` in the Arduino IDE and upload to your ESP32 board.

Note: This project was converted from a PlatformIO project and may require additional library installations depending on your Arduino IDE setup.