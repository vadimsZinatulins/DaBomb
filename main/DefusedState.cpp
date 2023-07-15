#include "DefusedState.h"
#include "LCDManager.h"

namespace DaBomb::Core {

void DefusedState::initialize() {
    auto &lcd { LCDManager::getInstance() };

    lcd.clearScreen();
    lcd.print("Bomb has been");
    lcd.moveCursor(0, 1);
    lcd.print("defused!");
}

void DefusedState::update() {
    
}

}