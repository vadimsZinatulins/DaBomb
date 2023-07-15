#pragma once

#include "StateManager.h"

namespace DaBomb::Core {

class DefusedState : public IState {
public:
    void initialize() override;
    void update() override;
};

}