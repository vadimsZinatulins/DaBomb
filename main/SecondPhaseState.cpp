#include "SecondPhaseState.h"
#include "LCDManager.h"
#include "KeypadManager.h"
#include "DefusedState.h"
#include "TransitionState.h"
#include "Arduino.h"

namespace DaBomb::Core {

SecondPhaseState::SecondPhaseState(uint8_t changes[Globals::NumPinsToInitialize], Color colors[Globals::NumPinsToInitialize]) {
    for(int i = 0; i < CODE_LENGTH; ++i) {
        uint8_t index = random(0, Globals::NumPinsToInitialize);

        m_code[i] = {
            String(changes[i])[0],
            colors[i]
        };
    }
}

void SecondPhaseState::initialize() {
    auto &lcd { LCDManager::getInstance() };

    lcd.clearScreen();

    String code = "Code: ";

    for(int i = 0; i < CODE_LENGTH; ++i) {
        code += m_code[i].value;
        lcd.displayPinAt(i, 0, DisplayPin::Filled);
    }

    Serial.println(code);

    lcd.moveCursor(0, 0);
}

void SecondPhaseState::update() {
    auto &lcd { LCDManager::getInstance() };
    auto &keypad { KeypadManager::getInstance() };

    auto key { keypad.getKey() };
    if(key && key == m_code[m_currentIndex].value) {
        m_currentIndex++;

        lcd.print(key);

        if(m_currentIndex >= CODE_LENGTH) {
            StateManager::getInstance().changeState(new TransitionState(new DefusedState(), 1500));
        }
    }
}

}