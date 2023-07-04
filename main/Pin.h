#pragma once

#include <stdint.h>

namespace DaBomb {

struct Pin {
  uint8_t pin;
  bool active { false };
};

}