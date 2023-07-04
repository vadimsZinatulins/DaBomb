#include "Arduino.h"
#include "Game.h"

// #include "Board.h"

// DaBomb::Board g_board;

DaBomb::Game g_game;

void setup()
{
  Serial.begin(9600);

  g_game.init();

  // g_board.init();
}

void loop()
{
  g_game.run();
  
  // g_board.printPinStates();
}
