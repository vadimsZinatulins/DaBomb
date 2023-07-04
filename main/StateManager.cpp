#include "HardwareSerial.h"
#include "StateManager.h"

namespace DaBomb::Core {

StateManager &StateManager::getInstance() {
  static StateManager instance;

  return instance;
}

IState *StateManager::getState() {
  return m_state;
}

void StateManager::changeState(IState *newState) {
  if(m_nextState != nullptr) {
    delete m_nextState;
  }

  m_nextState = newState;
}

void StateManager::update() {
  if(m_nextState != nullptr) {
    delete m_state;
    
    m_state = m_nextState;

    m_nextState = nullptr;

    m_state->initialize();
  }
}

}