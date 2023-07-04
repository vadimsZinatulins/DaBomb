#include "HardwareSerial.h"
#include "Arduino.h"
#include "LedManager.h"

namespace DaBomb::Core {

LedManager &LedManager::getInstance() {
  static LedManager instance;

  return instance;
} 

void LedManager::init() {
  Serial.println("Setting up leds");

  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
}

void LedManager::setColor(uint8_t r, uint8_t g, uint8_t b) {
  Serial.println("Changing color");

  analogWrite(RedPin, 255 - r);
  analogWrite(GreenPin, 255 - g);
  analogWrite(BluePin, 255 - b);
}

}