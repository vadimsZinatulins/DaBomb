#pragma once

#include <stdint.h>
#include "Arduino.h"

namespace DaBomb::Globals {

static const uint8_t NumPinsPerRow = 8;
static const uint8_t NumPinsToInitialize = 4;

static const byte KeyRows { 4 };
static const byte KeyCols { 3 };

static const char KeysMap[KeyRows][KeyCols] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'*','0','#'}
};

static const byte KeyRowPins[KeyRows] = { 5, 4, 3, 2 };
static const byte KeyColPins[KeyCols] = { 14, 15, 16 };

}