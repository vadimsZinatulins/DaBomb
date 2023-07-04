#include "StateManager.h"

namespace DaBomb::Core {

StateManager &StateManager::getInstance() {
  static StateManager instance;

  return instance;
}

IState *StateManager::getState() {
  return m_State;
}

void StateManager::changeState(IState *newState) {
  if(m_nextState) {
    delete m_nextState;
  }

  m_nextState = newState;
}

void StateManager::update() {
  if(m_nextState) {
    delete m_State;
    
    m_State = m_nextState;

    m_nextState = nullptr;
  }
}

}