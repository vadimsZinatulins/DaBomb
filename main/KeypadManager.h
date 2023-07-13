#pragma once

#include "Globals.h"

#include <Keypad.h>

namespace DaBomb::Core {

class KeypadManager {
public:
    static KeypadManager &getInstance();

    char getKey();
private:

    Keypad m_keypad { Keypad(makeKeymap(Globals::KeysMap), Globals::KeyRowPins, Globals::KeyColPins, Globals::KeyRows, Globals::KeyCols) };
};

}