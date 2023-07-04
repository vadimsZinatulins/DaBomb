#pragma once

#include "StateManager.h"
#include "Globals.h"

namespace DaBomb::Core {

class FirstPhaseState : public Core::IState {
public:
  FirstPhaseState();
  void update() override;
private:
};

}