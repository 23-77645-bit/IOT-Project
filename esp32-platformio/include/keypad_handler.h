#ifndef KEYPAD_HANDLER_H
#define KEYPAD_HANDLER_H

#include <Arduino.h>
#include <Keypad.h>

class KeypadHandler {
private:
    Keypad* keypad;
    String inputBuffer;
    char keys[4][4];
    byte rowPins[4];
    byte colPins[4];
    unsigned long lastKeyPress;
    unsigned long keyTimeout;

public:
    KeypadHandler();
    ~KeypadHandler();
    
    bool begin();
    String getInput();
    bool hasInput();
    void clearInput();
    void setTimeout(unsigned long timeout);
    char getKey();
    
private:
    void onKeyPress(char key);
};

#endif // KEYPAD_HANDLER_H