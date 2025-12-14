#ifndef SERVO_HANDLER_H
#define SERVO_HANDLER_H

#include <Arduino.h>
#include <ESP32Servo.h>

class ServoHandler {
private:
    Servo* servo;
    int servoPin;
    int lockPosition;
    int unlockPosition;
    bool isLocked;
    unsigned long lastMovement;
    unsigned long movementDelay;

public:
    ServoHandler(int pin);
    ~ServoHandler();
    
    bool begin();
    void lock();
    void unlock();
    void toggle();
    bool getStatus() { return isLocked; }
    void setPositions(int lockPos, int unlockPos);
    bool isMoving() { return (millis() - lastMovement) < movementDelay; }
    
private:
    void moveToPosition(int position);
};

#endif // SERVO_HANDLER_H