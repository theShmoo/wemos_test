#include "pins.h"

namespace my
{
  enum class Sensor
  {
    Humidity,
    Temperature
  };

  struct SensorEnv
  {
    Pin pin;
  };

  void init(const SensorEnv &env);

  float humidity();

  float temperature();

  float read(Sensor type);
} // namespace my
