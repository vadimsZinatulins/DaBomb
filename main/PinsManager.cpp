#include "PinsManager.h"

#include "Arduino.h"

namespace DaBomb::Core {

PinsManager &PinsManager::getInstance() {
  static PinsManager instance;

  return instance;
}

void PinsManager::init() {
  // Set the pins and pin mode for input pins
  for(int i = 0; i < DaBomb::Globals::NumPinsPerRow; ++i) {
    m_inputPins[i] = 22 + i * 2;
    
    Serial.println("Pin " + String(m_inputPins[i]) + " is INPUT");
    pinMode(m_inputPins[i], INPUT_PULLUP);
  }
  
  // Set the pins, pin mode and default value for output pins
  for(int i = 0; i < DaBomb::Globals::NumPinsPerRow; ++i) {
    m_outputPins[i] = 23 + i * 2;
    
    Serial.println("Pin " + String(m_outputPins[i]) + " is OUTPUT");
    pinMode(m_outputPins[i], OUTPUT);
    digitalWrite(m_outputPins[i], HIGH);
  }
}

bool PinsManager::checkIfConnected(uint8_t inputPinIndex, uint8_t outputPinIndex) {
  // Make sure that all output pins are HIGH
  for(int i = 0; i < DaBomb::Globals::NumPinsPerRow; ++i) {
    digitalWrite(m_outputPins[i], HIGH);
  }

  // Check the pins connectivity
  digitalWrite(m_outputPins[outputPinIndex], LOW);
  bool result = digitalRead(m_inputPins[inputPinIndex]) == LOW;
  digitalWrite(m_outputPins[outputPinIndex], HIGH);  // Reset the value

  return result;
}

}