#include "../include/lcd_handler.h"

LCDHandler::LCDHandler(int rs_pin, int en_pin, int d4_pin, int d5_pin, int d6_pin, int d7_pin) {
  this->rs = rs_pin;
  this->en = en_pin;
  this->d4 = d4_pin;
  this->d5 = d5_pin;
  this->d6 = d6_pin;
  this->d7 = d7_pin;
  this->lcd = nullptr;
}

LCDHandler::~LCDHandler() {
  if (lcd != nullptr) {
    delete lcd;
  }
}

bool LCDHandler::begin() {
  try {
    lcd = new LiquidCrystal(rs, en, d4, d5, d6, d7);
    lcd->begin(16, 2);  // Standard 16x2 LCD
    
    printWelcomeMessage();
    delay(2000);
    clear();
    
    return true;
  } catch (...) {
    return false;
  }
}

void LCDHandler::clear() {
  if (lcd != nullptr) {
    lcd->clear();
  }
}

void LCDHandler::print(String text, int row, int col) {
  if (lcd != nullptr) {
    lcd->setCursor(col, row);
    lcd->print(text);
  }
}

void LCDHandler::printCentered(String text, int row) {
  if (lcd != nullptr) {
    int spaces = (16 - text.length()) / 2;  // Assuming 16 columns
    String centeredText = "";
    for (int i = 0; i < spaces; i++) {
      centeredText += " ";
    }
    centeredText += text;
    
    lcd->setCursor(0, row);
    lcd->print(centeredText);
  }
}

void LCDHandler::printAccessMessage(String method, String user, bool granted) {
  if (lcd != nullptr) {
    clear();
    
    if (granted) {
      printCentered("ACCESS GRANTED", 0);
      printCentered(method + ": " + user, 1);
    } else {
      printCentered("ACCESS DENIED", 0);
      printCentered(method + ": " + user, 1);
    }
    
    delay(2000); // Show message for 2 seconds
    clear();
  }
}

void LCDHandler::printSystemStatus() {
  if (lcd != nullptr) {
    clear();
    printCentered("SYSTEM READY", 0);
    printCentered("Waiting...", 1);
  }
}

void LCDHandler::printWelcomeMessage() {
  if (lcd != nullptr) {
    clear();
    printCentered("SMART LOCKER", 0);
    printCentered("SYSTEM", 1);
  }
}