#ifndef LCD_HANDLER_H
#define LCD_HANDLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "config.h"

class LCDHandler {
private:
  LiquidCrystal* lcd;
  int rs, en, d4, d5, d6, d7;

public:
  LCDHandler(int rs_pin, int en_pin, int d4_pin, int d5_pin, int d6_pin, int d7_pin);
  ~LCDHandler();
  
  bool begin();
  void clear();
  void print(String text, int row = 0, int col = 0);
  void printCentered(String text, int row);
  void printAccessMessage(String method, String user, bool granted);
  void printSystemStatus();
  void printWelcomeMessage();
};

#endif // LCD_HANDLER_H