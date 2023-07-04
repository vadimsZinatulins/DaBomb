#pragma once

namespace DaBomb::Core {
  
class Chrono {
public:
  void start();
  void stop();
  void restart();
  
  bool isRunning();
  long getMillis();
private:
  long m_initial { 0 };
  long m_final { 0 };
  bool m_isRunning { false };
};

}