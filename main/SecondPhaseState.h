#pragma once

#include "StateManager.h"
#include "Globals.h"
#include "Color.h"
#include "Chrono.h"

namespace DaBomb::Core {
    
#define CODE_LENGTH 6

struct CodeElement {
  char value;
  Color color;
};

class SecondPhaseState : public Core::IState {
public:
  SecondPhaseState(uint8_t changes[Globals::NumPinsToInitialize], Color colors[Globals::NumPinsToInitialize]);

  void initialize() override;
  void update() override;
private:
    CodeElement m_code[CODE_LENGTH];
    
    Chrono m_remainingTime;

    uint8_t m_currentIndex { 0 };
};

}
