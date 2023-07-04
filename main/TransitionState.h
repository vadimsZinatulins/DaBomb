#pragma once

#include <stdint.h>

#include "StateManager.h"
#include "Chrono.h"

namespace DaBomb::Core {


class TransitionState : public IState {
public:
  TransitionState(IState *nextState, long timeToTransition);

  void initialize() override;
  void update() override;
private:
  IState *m_nextState { nullptr };
  uint8_t m_currentIndex { 0 };

  Chrono m_timer;
  long m_timePerSection { 0 };
};

}