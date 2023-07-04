#include "LedManager.h"
#include "Arduino.h"

namespace DaBomb::Core {

LedManager &LedManager::getInstance() {
  static LedManager instance;

  return instance;
} 

void LedManager::init() {
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
}

void LedManager::setColor(Color color) {
  analogWrite(RedPin, 255 - color.red);
  analogWrite(GreenPin, 255 - color.green);
  analogWrite(BluePin, 255 - color.blue);
}

}