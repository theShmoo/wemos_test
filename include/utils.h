#include <chrono>
#include <Arduino.h>

inline void wait(std::chrono::milliseconds ms) { delay(ms.count()); }
