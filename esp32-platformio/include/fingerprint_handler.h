#ifndef FINGERPRINT_HANDLER_H
#define FINGERPRINT_HANDLER_H

#include <Arduino.h>
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

class FingerprintHandler {
private:
    SoftwareSerial* fingerSerial;
    Adafruit_Fingerprint* finger;
    uint8_t fingerID;
    uint8_t confidence;

public:
    FingerprintHandler();
    ~FingerprintHandler();
    
    bool begin();
    bool verifyPassword();
    bool checkFingerprint();
    uint8_t getFingerID() { return fingerID; }
    uint8_t getConfidence() { return confidence; }
    String getFingerprintData();
    
private:
    bool enrollFinger(uint8_t id);
    bool deleteFinger(uint8_t id);
    uint8_t getFingerprintID();
};

#endif // FINGERPRINT_HANDLER_H