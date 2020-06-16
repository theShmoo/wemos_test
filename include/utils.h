#include <chrono>
#include <Arduino.h>

namespace my
{
  inline void wait(std::chrono::milliseconds ms)
  {
    delay(ms.count());
  }
} // namespace my
