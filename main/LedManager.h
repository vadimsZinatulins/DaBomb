#pragma once

#include "Color.h"
#include <stdint.h>

namespace DaBomb::Core {

class LedManager {
public:
  static LedManager &getInstance();

  void init();

  void setColor(Color color);
private:
  const uint8_t RedPin = 9;
  const uint8_t GreenPin = 10;
  const uint8_t BluePin = 11;
};

}