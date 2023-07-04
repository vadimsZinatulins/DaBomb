#pragma once

#include "Color.h";

namespace DaBomb::Core {

struct Connection {
  uint8_t outputPin;
  uint8_t inputPin;

  Color color;
};

}