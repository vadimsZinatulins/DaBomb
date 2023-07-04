#include "TransitionState.h"
#include "LCDManager.h"
#include "LedManager.h"
#include "Globals.h"

namespace DaBomb::Core {

void renderCurrentSection(uint8_t currentIndex) {
  auto &manager { LCDManager::getInstance() };

  manager.displayPinAt(currentIndex, 0, DisplayPin::Filled);
  manager.displayPinAt(currentIndex, 1, DisplayPin::Filled);
}

TransitionState::TransitionState(IState *nextState, long timeToTransition) : m_nextState(nextState),  m_timePerSection(timeToTransition / Globals::NumPinsPerRow) { }

void TransitionState::initialize() {
  LCDManager::getInstance().displayAll();

  LedManager::getInstance().setColor(Color { 0, 0, 0});

  m_timer.start(); 
}

void TransitionState::update() {
  if(m_timer.getMillis() > m_timePerSection) {
    if(++m_currentIndex > Globals::NumPinsPerRow) {
      StateManager::getInstance().changeState(m_nextState);
    } else {
      renderCurrentSection(m_currentIndex - 1);
      m_timer.restart();
    }
  }
}

}