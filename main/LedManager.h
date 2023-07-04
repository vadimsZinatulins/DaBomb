#pragma once

#include <stdint.h>

namespace DaBomb::Core {

class LedManager {
public:
  static LedManager &getInstance();

  void init();

  void setColor(uint8_t r, uint8_t g, uint8_t b);
private:
  const uint8_t RedPin = 9;
  const uint8_t GreenPin = 10;
  const uint8_t BluePin = 11;
};

}