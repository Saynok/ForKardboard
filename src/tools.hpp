#pragma once
#include <Arduino.h>

class Time
{
private:
  unsigned long _lastTime;

public:
  /// @brief Period in milliseconds
  Time()
  {
    _lastTime = millis();
  }

  bool Estimated(unsigned long period)
  {
    if (millis() - _lastTime > period)
    {
      _lastTime = millis();
      return true;
    }
    return false;
  }
};
