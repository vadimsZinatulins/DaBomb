#pragma once 

#include <stdint.h>

#include "Globals.h"

namespace DaBomb::Core {

class PinsManager {
public:
  static PinsManager &getInstance();

  void init();

  bool checkIfConnected(uint8_t inputPinIndex, uint8_t outputPinIndex);
private:
  uint8_t m_inputPins[DaBomb::Globals::NumPinsPerRow];
  uint8_t m_outputPins[DaBomb::Globals::NumPinsPerRow];
};

}