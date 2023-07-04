#pragma once

#include "StateManager.h"
#include "Chrono.h"
#include "Globals.h"
#include "Connection.h"
#include "Arduino.h"

namespace DaBomb::Core {

class SetupState : public Core::IState {
public:
  SetupState();
  void update() override;
private:
  void validatePreviousConnections();
  
  uint8_t m_initIndex { 0 };
  Connection m_connectionsToSetup[Globals::NumPinsToInitialize];

  Chrono m_chrono;
};

}