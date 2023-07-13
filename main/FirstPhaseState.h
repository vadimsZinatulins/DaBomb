#pragma once

#include "StateManager.h"
#include "Globals.h"
#include "Chrono.h"
#include "Connection.h"

#include <stdint.h>

namespace DaBomb::Core {

struct Changes {
  uint8_t numTotalChanges { 0 };
  uint8_t numTotalChangesRemain { 0 };
};

class FirstPhaseState : public Core::IState {
public:
  FirstPhaseState(Connection connections[Globals::NumPinsToInitialize]);

  void initialize() override;
  void update() override;
private:
  void pickRandomIndex();
  void pickOutputPin();
  void pickInputPin();
  bool hasPendingChanges();
  void win();

  Connection m_connections[Globals::NumPinsToInitialize];
  Changes m_changes[Globals::NumPinsToInitialize];

  uint8_t m_currentChangeIndex { 0 };

  Chrono m_connectionTime;
  Chrono m_remainingTime;
  Chrono m_ledTime;

  bool m_isLedEnabled { true };
};

}