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
private:
  LiquidCrystal_I2C m_lcd { 0x27, 20, 4 };
};

}
