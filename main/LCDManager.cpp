#include <stdint.h>
#include "Globals.h"
#include "LCDManager.h"
#include "Arduino.h"

namespace DaBomb::Core {

#define PIN_OFF_ID 0
#define PIN_ON_ID 1

uint8_t pin_off[8] = {
  B11111,
  B10001,
  B10001,
  B10001,
  B10001,
  B10001,
  B11111,
};

uint8_t pin_on[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
};

LCDManager &LCDManager::getInstance() {
  static LCDManager instance;

  return instance;
}

void LCDManager::init() {
  // Initialize LCD Display
  m_lcd.init();
  // Enable backlight
  m_lcd.backlight();

  // Create character for Pin Off
  m_lcd.createChar(0, pin_off);

  // Create character for Pin On
  m_lcd.createChar(1, pin_on);

  displayAll();
}

void LCDManager::displayAll() {
  for(int i = 0; i < 2; ++i) {
    for(int j = 0; j < DaBomb::Globals::NumPinsPerRow; ++j) {
      displayPinAt(j, i, DisplayPin::Rect);
    }
  }
}

void LCDManager::displayPinAt(uint8_t column, uint8_t row, DisplayPin pinState) {
  m_lcd.setCursor(column, row);

  m_lcd.write(static_cast<uint8_t>(pinState));
}

}
