#ifndef RFID_HANDLER_H
#define RFID_HANDLER_H

#include <Arduino.h>
#include <MFRC522.h>
#include <SPI.h>

class RFIDHandler {
private:
    MFRC522* mfrc522;
    String currentUID;
    bool cardPresent;

public:
    RFIDHandler(uint8_t ssPin, uint8_t rstPin);
    ~RFIDHandler();
    
    bool begin();
    bool checkCard();
    String getCardUID();
    bool isCardPresent() { return cardPresent; }
    void haltCard();
    
private:
    String uidToString(byte* buffer, byte bufferSize);
};

#endif // RFID_HANDLER_H