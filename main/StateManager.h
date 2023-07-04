#pragma once

namespace DaBomb::Core {

struct IState {
  virtual void update() = 0;
};

class StateManager {
public:
  static StateManager &getInstance();

  IState *getState();
  void changeState(IState *newState);

  void update();
private:
  IState *m_State { nullptr };
  IState *m_nextState { nullptr };
};

}