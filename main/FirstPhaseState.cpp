#include "FirstPhaseState.h"
#include "PinsManager.h"
#include "LCDManager.h"
#include "LedManager.h"
#include "TransitionState.h"
#include "SetupState.h"
#include "SecondPhaseState.h"
#include "Arduino.h"

#define TIME_TO_CONNECT 30000

namespace DaBomb::Core {

uint8_t maxValue(uint8_t a, uint8_t b) {
  return a > b ? a : b;
}

inline bool checkIfConnected(Connection connection) {
  return PinsManager::getInstance().checkIfConnected(connection.inputPin, connection.outputPin);
}

FirstPhaseState::FirstPhaseState(Connection connections[Globals::NumPinsToInitialize]) {
  for(uint8_t i = 0; i < Globals::NumPinsToInitialize; ++i) {
    m_connections[i] = connections[i];
  }

}

void FirstPhaseState::initialize() {
  Serial.println("FirstPhaseState::initialize");

  uint8_t maxPool { 16 };

  uint8_t index { 0 };
  while(maxPool > 0) {
    int value = random(1, maxValue(maxPool, 5));
    maxPool -= value;

    m_changes[index].numTotalChanges += value;
    m_changes[index].numTotalChangesRemain = m_changes[index].numTotalChanges;

    index = (index + 1) % Globals::NumPinsToInitialize;
  }

  pickRandomIndex();
  m_remainingTime.restart();
  m_ledTime.restart();
}

void FirstPhaseState::update() {
  auto currentConnection { m_connections[m_currentChangeIndex] };

  if(m_remainingTime.getMillis() > TIME_TO_CONNECT) {
    StateManager::getInstance().changeState(new Core::TransitionState(new Core::SetupState(), 1500));
  }

  long timeRation = static_cast<float>((TIME_TO_CONNECT - m_remainingTime.getMillis())) / static_cast<float>(TIME_TO_CONNECT) * 500;


  if(m_ledTime.getMillis() > timeRation) {
    m_isLedEnabled = !m_isLedEnabled;
    if(m_isLedEnabled) {
      LedManager::getInstance().setColor(currentConnection.color);
    } else {
      LedManager::getInstance().setColor({ 0, 0, 0 });
    }

    m_ledTime.restart();
  }


  if(checkIfConnected(currentConnection)) {
    if(m_connectionTime.isRunning()) {
      if(m_connectionTime.getMillis() > 500) {
        m_changes[m_currentChangeIndex].numTotalChangesRemain--;

        if(hasPendingChanges()) {
          pickRandomIndex();
          m_remainingTime.restart();
        } else {
          win();
        }
      }
    } else {
      m_connectionTime.restart();
    }
  }

  // botnroll
}

void FirstPhaseState::pickRandomIndex() {
  LCDManager::getInstance().displayAll();

  Serial.println("FirstPhaseState::pickRandomIndex");

  do {
    m_currentChangeIndex = random(0, Globals::NumPinsToInitialize);
  } while(m_changes[m_currentChangeIndex].numTotalChangesRemain <= 0);

  Serial.println("FirstPhaseState::pickRandomIndex (" + String(m_currentChangeIndex) + ")");

  if(random(0, 2)) {
    pickOutputPin();
  } else {
    pickInputPin();
  }

  LedManager::getInstance().setColor(m_connections[m_currentChangeIndex].color);
}

void FirstPhaseState::pickOutputPin() {
  Serial.println("FirstPhaseState::pickOutputPin");

  auto inUsedPins = [&](uint8_t pin) {
    for(int i = 0; i < Globals::NumPinsToInitialize; ++i) {
      if(pin == m_connections[i].outputPin) {
        return true;
      }
    }

    return false;
  };

  uint8_t newOutputPin = random(0, Globals::NumPinsPerRow);

  while(inUsedPins(newOutputPin)) {
    newOutputPin = random(0, Globals::NumPinsPerRow);
  }

  m_connections[m_currentChangeIndex].outputPin = newOutputPin;
  
  LCDManager::getInstance().displayPinAt(newOutputPin, 0, DisplayPin::Filled);
}

void FirstPhaseState::pickInputPin() {
  Serial.println("FirstPhaseState::pickInputPin");

  auto inUsedPins = [&](uint8_t pin) {
    for(int i = 0; i < Globals::NumPinsToInitialize; ++i) {
      if(pin == m_connections[i].inputPin) {
        return true;
      }
    }

    return false;
  };

  uint8_t newInputPin = random(0, Globals::NumPinsPerRow);

  while(inUsedPins(newInputPin)) {
    newInputPin = random(0, Globals::NumPinsPerRow);
  }

  m_connections[m_currentChangeIndex].inputPin = newInputPin;
  
  LCDManager::getInstance().displayPinAt(newInputPin, 1, DisplayPin::Filled);
}

bool FirstPhaseState::hasPendingChanges() {
  for(uint8_t i = 0; i < Globals::NumPinsToInitialize; ++i) {
    if(m_changes[i].numTotalChangesRemain > 0) {
      return true;
    }
  }

  return false;
}

void FirstPhaseState::win() {
  uint8_t changes[Globals::NumPinsToInitialize];
  Color colors[Globals::NumPinsToInitialize];

  for(uint8_t i = 0; i < Globals::NumPinsToInitialize; ++i) {
    changes[i] = m_changes[i].numTotalChanges;
    colors[i] = m_connections[i].color;
  }

  StateManager::getInstance().changeState(new Core::TransitionState(new Core::SecondPhaseState(changes, colors), 1500));
}

}