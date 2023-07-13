#include "KeypadManager.h"

namespace DaBomb::Core {

KeypadManager &KeypadManager::getInstance() {
    static KeypadManager instance;

    return instance;
}

char KeypadManager::getKey() {
    return m_keypad.getKey();
}

}