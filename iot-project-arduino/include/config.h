#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Server Configuration
#define SERVER_IP "YOUR_SERVER_IP"
#define SERVER_PORT 5000
#define SERVER_URL "http://" SERVER_IP ":" String(SERVER_PORT) "/api"

// Web Server Authentication
#define HTTP_USERNAME "admin"
#define HTTP_PASSWORD "smartlock2025"

// Security Configuration
#define MASTER_PASSWORD "1234"

// Pin Configuration
#define SERVO_PIN 15
#define RED_LED_PIN 22
#define GREEN_LED_PIN 21
#define BLUE_LED_PIN 2
#define BUZZER_PIN 4

// LCD Configuration (16x2 LCD with HD44780 controller)
#define LCD_RS_PIN 33
#define LCD_EN_PIN 25
#define LCD_D4_PIN 26
#define LCD_D5_PIN 27
#define LCD_D6_PIN 14
#define LCD_D7_PIN 12

// Fingerprint Sensor (Software Serial)
#define FP_RX_PIN 16
#define FP_TX_PIN 17
#define FP_BAUDRATE 57600

// RFID Module (SPI)
#define RFID_SS_PIN 5
#define RFID_RST_PIN 21

// Keypad Configuration
#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4
#define ROW_PINS {32, 33, 25, 26}
#define COL_PINS {27, 14, 12, 13}

// Timing Configuration
#define AUTO_LOCK_DELAY 5000
#define ACCESS_GRANTED_DELAY 2000
#define ACCESS_DENIED_DELAY 1000

// Debug Configuration
#ifdef DEBUG_BUILD
  #define DEBUG_PRINT(x) Serial.print(x)
  #define DEBUG_PRINTLN(x) Serial.println(x)
  #define DEBUG_PRINTF(x, ...) Serial.printf(x, __VA_ARGS__)
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTF(x, ...)
#endif

#endif // CONFIG_H