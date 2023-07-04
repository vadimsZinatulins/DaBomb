#include "Game.h"
#include "StateManager.h"
#include "PinsManager.h"
#include "LedManager.h"
#include "LCDManager.h"
#include "Globals.h"
#include "Helpers.h"
#include "Arduino.h"
#include "HardwareSerial.h"

namespace DaBomb {

class Chrono {
public:
  void start() {
    m_initial = millis();
  }

  long readTime() {
    return millis() - m_initial;
  }
private:
  long m_initial { 0 };
};

struct Color {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
};

struct Connection {
  uint8_t outputPin;
  uint8_t inputPin;

  Color color;
};

class SetupState : public Core::IState {
public:
  SetupState() {
    auto initNum = Globals::NumPinsToInitialize;

    auto initializer = [initNum](uint8_t *array, uint8_t maxIndex){
      for(int i = 0; i < initNum; ++i) {
        uint8_t randomIndex = random(0, maxIndex) + 1;
        while(Helpers::arrayContains(randomIndex, array, initNum)) {
          randomIndex = random(0, initNum) + 1;
        }
        array[i] = randomIndex;
      }
    };

    uint8_t colorIndeces[initNum];
    initializer(colorIndeces, initNum);

    uint8_t inputPinsIndeces[initNum];
    initializer(inputPinsIndeces, Globals::NumPinsPerRow);

    uint8_t outputPinsIndeces[initNum];
    initializer(outputPinsIndeces, Globals::NumPinsPerRow);

    Color colors[] = {
      Color { 255, 0, 0 },    // Red
      Color { 0, 255, 0 },    // Green
      Color { 0, 0, 255 },    // Blue
      Color { 255, 140, 0 },  // Orage
    };

    for(int i = 0; i < initNum; ++i) {
      m_connectionsToSetup[i].outputPin = outputPinsIndeces[i] - 1;
      m_connectionsToSetup[i].inputPin = inputPinsIndeces[i] - 1;
      m_connectionsToSetup[i].color = colors[colorIndeces[i] - 1];
    }
  }

  void update() override {
    auto connection { m_connectionsToSetup[m_initIndex] };

    auto manager { Core::LCDManager::getInstance() };
    
    Core::LedManager::getInstance().setColor(connection.color.red, connection.color.green, connection.color.blue);

    manager.displayPinAt(connection.outputPin, 0, Core::DisplayPin::Filled);
    manager.displayPinAt(connection.inputPin, 1, Core::DisplayPin::Filled);

    if(Core::PinsManager::getInstance().checkIfConnected(connection.inputPin, connection.outputPin)) {
      if(!m_wasConnected) {
        m_chrono.start();
        m_wasConnected = true;
      } else if(m_chrono.readTime() > 1000) {
        manager.displayPinAt(connection.outputPin, 0, Core::DisplayPin::Rect);
        manager.displayPinAt(connection.inputPin, 1, Core::DisplayPin::Rect);

        m_initIndex++;
      }
    }
  }

private:
  uint8_t m_initIndex { 0 };
  Connection m_connectionsToSetup[Globals::NumPinsToInitialize];

  Chrono m_chrono;
  bool m_wasConnected { false };
};

void Game::init() {
  randomSeed(analogRead(0));

  Core::LCDManager::getInstance().init();
  Core::PinsManager::getInstance().init();
  Core::LedManager::getInstance().init();
  Core::StateManager::getInstance().changeState(new SetupState());

  // Core::LedManager::getInstance().setColor(32, 0, 32);
}

void Game::run() {
  auto stateManager { Core::StateManager::getInstance() };
  stateManager.update();
  stateManager.getState()->update();
};

}