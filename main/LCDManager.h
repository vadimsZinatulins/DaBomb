#pragma once

#include <stdint.h>
#include <LiquidCrystal_I2C.h>

namespace DaBomb::Core {

enum class DisplayPin { Rect = 0, Filled = 1 };

class LCDManager {
public:
  static LCDManager &getInstance();

  void init();
  void displayAll();
  void displayPinAt(uint8_t column, uint8_t row, DisplayPin pinState);
  void clearScreen();
  void moveCursor(uint8_t column, uint8_t row);
  void print(char c);
  void print(char str[]);
  
// private:
  LiquidCrystal_I2C m_lcd { 0x27, 20, 4 };
};

}
