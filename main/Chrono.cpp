#include "Chrono.h"
#include "Arduino.h"

namespace DaBomb::Core {

void Chrono::start() {
  if(!m_isRunning) {
    m_initial = m_final = millis();
    m_isRunning = true;
  }
}

void Chrono::stop() {
  if(m_isRunning) {
    m_final = millis();
    m_isRunning = false;
  }
}


bool Chrono::isRunning() {
  return m_isRunning;
}

long Chrono::getMillis() {
  if(m_isRunning) {
    return millis() - m_initial;
  }

  return m_final - m_initial;
}

}
