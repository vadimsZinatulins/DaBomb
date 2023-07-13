#include "Arduino.h"
#include "Game.h"

DaBomb::Game g_game;

void setup() {
  Serial.begin(9600);

  g_game.init();
}

void loop() {
  g_game.run();
}
