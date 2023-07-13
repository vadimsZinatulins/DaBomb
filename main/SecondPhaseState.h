#pragma once

#include "StateManager.h"
#include "Globals.h"
#include "Color.h"

namespace DaBomb::Core {
    
#define CODE_LENGTH 6

class SecondPhaseState : public Core::IState {
public:
  SecondPhaseState(uint8_t changes[Globals::NumPinsToInitialize], Color colors[Globals::NumPinsToInitialize]);

  void initialize() override;
  void update() override;
private:
    uint8_t code[CODE_LENGTH];
}

}