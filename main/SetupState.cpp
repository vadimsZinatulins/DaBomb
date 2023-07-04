#include "SetupState.h"
#include "Helpers.h"
#include "LCDManager.h"
#include "LedManager.h"
#include "PinsManager.h"
#include "StateManager.h"
#include "TransitionState.h"
#include "FirstPhaseState.h"
#include "Color.h"

namespace DaBomb::Core {

inline void setLedColor(Connection connection) {
  LedManager::getInstance().setColor(connection.color);
}

inline bool checkIfConnected(Connection connection) {
  return PinsManager::getInstance().checkIfConnected(connection.inputPin, connection.outputPin);
}

inline void displayPins(Connection connection, DisplayPin state) {
  auto &manager { LCDManager::getInstance() };

  manager.displayPinAt(connection.outputPin, 0, state);
  manager.displayPinAt(connection.inputPin, 1, state);
}

void SetupState::initialize() {
  LCDManager::getInstance().displayAll();

  auto initNum = Globals::NumPinsToInitialize;

  // This lambda initializes an array with random indices without repeating them
  // up to a max index value
  auto initializer = [initNum](uint8_t *array, uint8_t maxIndex){
    for(int i = 0; i < initNum; ++i) {
      uint8_t randomIndex = random(0, maxIndex) + 1;
      while(Helpers::arrayContains(randomIndex, array, initNum)) {
        randomIndex = random(0, initNum) + 1;
      }
      array[i] = randomIndex;
    }
  };

  // Random indices for colors
  uint8_t colorIndeces[initNum];
  initializer(colorIndeces, initNum);

  // Random indices for input pins
  uint8_t inputPinsIndeces[initNum];
  initializer(inputPinsIndeces, Globals::NumPinsPerRow);

  // Random indices for output pins
  uint8_t outputPinsIndeces[initNum];
  initializer(outputPinsIndeces, Globals::NumPinsPerRow);

  // List of colors that will be used
  Color colors[] = {
    Color { 255, 0, 0 },    // Red
    Color { 0, 255, 0 },    // Green
    Color { 0, 0, 255 },    // Blue
    Color { 255, 140, 0 },  // Orage
  };

  // Apply randomly generated indices to connections.
  // This will result in a random connection pin setup (input pin + 
  // output pin + color)
  for(int i = 0; i < initNum; ++i) {
    m_connectionsToSetup[i].outputPin = outputPinsIndeces[i] - 1;
    m_connectionsToSetup[i].inputPin = inputPinsIndeces[i] - 1;
    m_connectionsToSetup[i].color = colors[colorIndeces[i] - 1];
  }

  // Display the first connection
  displayPins(m_connectionsToSetup[0], DisplayPin::Filled);
  // Change the led color to represent the first connection
  setLedColor(m_connectionsToSetup[0]);
}

void SetupState::update() {
  // Make sure that the previous connections are still valid
  validatePreviousConnections();

  auto connection { m_connectionsToSetup[m_initIndex] };
  
  if(checkIfConnected(connection)) {
    if(!m_chrono.isRunning()) {
      m_chrono.start();
    } else if(m_chrono.getMillis() > 5000) {
      // Stop the timer since its internal state is being used
      m_chrono.stop();

      // Reset display to default state
      displayPins(connection, DisplayPin::Rect);

      m_initIndex++;
      displayPins(m_connectionsToSetup[m_initIndex], DisplayPin::Filled);

      setLedColor(m_connectionsToSetup[m_initIndex]);

      // If all pins where initialized then change to the next state
      if(m_initIndex >= Globals::NumPinsToInitialize) {
        StateManager::getInstance().changeState(new TransitionState(new FirstPhaseState(), 1500));
      }
    }
  } else {
      m_chrono.stop();
  }
}

void SetupState::validatePreviousConnections() {
  for(int i = 0; i < m_initIndex; ++i) {
    auto connection { m_connectionsToSetup[i] };

    // Check if connection is still active
    if(!checkIfConnected(connection)) {
      // At this point the connection is no longer active, so reset 
      // to this stage
      
      // Stop the timer since its internal state is being used
      m_chrono.stop();

      // Reset display to default state
      displayPins(m_connectionsToSetup[m_initIndex], DisplayPin::Rect);

      m_initIndex = i;

      displayPins(connection, DisplayPin::Filled);

      setLedColor(connection);

      return;
    }
  }
}

}