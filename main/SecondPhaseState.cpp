#include "SecondPhaseState.h"
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
    String code = "Code: ";

    for(int i = 0; i < CODE_LENGTH; ++i) {
        code += m_code[i].value;
    }

    Serial.println(code);
}

void SecondPhaseState::update() {
    
}

}