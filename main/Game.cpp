#include "Game.h"
#include "SetupState.h"
#include "TransitionState.h"
#include "StateManager.h"
#include "PinsManager.h"
#include "LedManager.h"
#include "LCDManager.h"

namespace DaBomb {

void Game::init() {
  randomSeed(analogRead(0));

  Core::LCDManager::getInstance().init();
  Core::PinsManager::getInstance().init();
  Core::LedManager::getInstance().init();

  Core::StateManager::getInstance().changeState(new Core::TransitionState(new Core::SetupState(), 1500));
}

void Game::run() {
  auto &stateManager { Core::StateManager::getInstance() };
  
  stateManager.update();
  stateManager.getState()->update();
};

}