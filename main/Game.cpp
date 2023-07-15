#include "Game.h"
#include "SetupState.h"
#include "TransitionState.h"
#include "StateManager.h"
#include "PinsManager.h"
#include "LedManager.h"
#include "LCDManager.h"

#include "Color.h"
#include "SecondPhaseState.h"
#include "Globals.h"

namespace DaBomb {

void Game::init() {
  randomSeed(analogRead(0));

  Core::LCDManager::getInstance().init();
  Core::PinsManager::getInstance().init();
  Core::LedManager::getInstance().init();

  // Core::StateManager::getInstance().changeState(new Core::TransitionState(new Core::SetupState(), 1500));

  uint8_t changes[Globals::NumPinsToInitialize];
  for(uint8_t i = 0; i < Globals::NumPinsToInitialize; ++i) {
    changes[i] = random(0, 10);
  }

  Core::Color colors[] = {
    Core::Color { 255, 0, 0 },    // Red
    Core::Color { 0, 255, 0 },    // Green
    Core::Color { 0, 0, 255 },    // Blue
    Core::Color { 255, 140, 0 },  // Orage
  };

  Core::StateManager::getInstance().changeState(new Core::TransitionState(new Core::SecondPhaseState(changes, colors), 1500));
}

void Game::run() {
  auto &stateManager { Core::StateManager::getInstance() };
  
  stateManager.update();
  stateManager.getState()->update();
};

}