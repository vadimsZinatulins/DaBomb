#pragma once

#include "StateManager.h"
#include "Globals.h"

namespace DaBomb::Core {

class FirstPhaseState : public Core::IState {
public:
  FirstPhaseState();
  void initialize() override;
  void update() override;
private:
};

}