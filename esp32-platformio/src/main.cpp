#include <Arduino.h>
#include "config.h"
#include "wifi_handler.h"
#include "fingerprint_handler.h"
#include "rfid_handler.h"
#include "keypad_handler.h"
#include "servo_handler.h"
#include "web_server.h"

// Global objects
WiFiHandler* wifiHandler;
FingerprintHandler* fingerprintHandler;
RFIDHandler* rfidHandler;
KeypadHandler* keypadHandler;
ServoHandler* servoHandler;
WebServerHandler* webServer;

// Function prototypes
void systemInit();
void handleAccessGranted(String method, String user);
void handleAccessDenied(String method, String user);
void sendLogToServer(String method, String user, bool success);
void updateSystemStatus();

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("    SMART LOCKER SYSTEM - ESP32");
  Serial.println("========================================");
  
  systemInit();
}

void loop() {
  // Maintain WiFi connection
  wifiHandler->maintainConnection();
  
  // Handle web server requests
  webServer->handleClient();
  
  // Check fingerprint sensor
  if (fingerprintHandler->checkFingerprint()) {
    String user = "FingerID:" + String(fingerprintHandler->getFingerID());
    handleAccessGranted("Fingerprint", user);
  }
  
  // Check RFID
  if (rfidHandler->checkCard()) {
    String uid = rfidHandler->getCardUID();
    // TODO: Check UID with server
    handleAccessGranted("RFID", uid);
    rfidHandler->haltCard();
  }
  
  // Check keypad
  char key = keypadHandler->getKey();
  if (key) {
    if (key == '#') {
      String input = keypadHandler->getInput();
      if (input == MASTER_PASSWORD) {
        handleAccessGranted("Keypad", "Master");
      } else {
        handleAccessDenied("Keypad", "Unknown");
      }
      keypadHandler->clearInput();
    }
  }
  
  // Update system status
  updateSystemStatus();
}

void systemInit() {
  // Initialize status LED
  pinMode(BLUE_LED_PIN, OUTPUT);
  digitalWrite(BLUE_LED_PIN, HIGH);
  
  // Initialize WiFi
  wifiHandler = new WiFiHandler(WIFI_SSID, WIFI_PASSWORD);
  if (!wifiHandler->begin()) {
    Serial.println("WiFi initialization failed!");
    while (1) {
      digitalWrite(BLUE_LED_PIN, !digitalRead(BLUE_LED_PIN));
      delay(500);
    }
  }
  
  // Initialize servo
  servoHandler = new ServoHandler(SERVO_PIN);
  if (!servoHandler->begin()) {
    Serial.println("Servo initialization failed!");
  }
  servoHandler->lock();
  
  // Initialize fingerprint sensor
  fingerprintHandler = new FingerprintHandler();
  if (!fingerprintHandler->begin()) {
    Serial.println("Fingerprint sensor initialization failed!");
  }
  
  // Initialize RFID
  rfidHandler = new RFIDHandler(RFID_SS_PIN, RFID_RST_PIN);
  if (!rfidHandler->begin()) {
    Serial.println("RFID initialization failed!");
  }
  
  // Initialize keypad
  keypadHandler = new KeypadHandler();
  if (!keypadHandler->begin()) {
    Serial.println("Keypad initialization failed!");
  }
  
  // Initialize web server
  webServer = new WebServerHandler(80, HTTP_USERNAME, HTTP_PASSWORD);
  if (!webServer->begin()) {
    Serial.println("Web server initialization failed!");
  }
  webServer->setLockCallback([](bool lock) {
    if (lock) {
      servoHandler->lock();
    } else {
      servoHandler->unlock();
    }
  });
  
  Serial.println("System initialized successfully!");
  Serial.print("IP Address: ");
  Serial.println(wifiHandler->getLocalIP());
}

void handleAccessGranted(String method, String user) {
  Serial.println("Access GRANTED - Method: " + method + ", User: " + user);
  
  // Visual feedback
  digitalWrite(GREEN_LED_PIN, HIGH);
  tone(BUZZER_PIN, 1000, 200);
  
  // Unlock door
  servoHandler->unlock();
  
  // Send log to server
  sendLogToServer(method, user, true);
  
  delay(ACCESS_GRANTED_DELAY);
  digitalWrite(GREEN_LED_PIN, LOW);
}

void handleAccessDenied(String method, String user) {
  Serial.println("Access DENIED - Method: " + method + ", User: " + user);
  
  // Visual feedback
  for (int i = 0; i < 3; i++) {
    digitalWrite(RED_LED_PIN, HIGH);
    tone(BUZZER_PIN, 500, 100);
    delay(200);
    digitalWrite(RED_LED_PIN, LOW);
    delay(100);
  }
  
  // Send log to server
  sendLogToServer(method, user, false);
}

void sendLogToServer(String method, String user, bool success) {
  if (wifiHandler->isConnected()) {
    // TODO: Implement HTTP POST to Flask server
    String data = "{\"method\":\"" + method + "\",\"user\":\"" + user + "\",\"success\":" + String(success ? "true" : "false") + "}";
    Serial.println("Sending log to server: " + data);
  }
}

void updateSystemStatus() {
  // System status indicator
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    digitalWrite(BLUE_LED_PIN, !digitalRead(BLUE_LED_PIN));
    lastBlink = millis();
  }
}