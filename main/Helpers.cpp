#include "Helpers.h"

namespace DaBomb::Helpers {

bool arrayContains(uint8_t value, uint8_t *array, uint8_t size) {
  for(int i = 0; i < size; ++i) {
    if(array[i] == value) {
      return true;
    }
  }

  return false;
}

}