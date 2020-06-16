#include "sensors.h"

#include "DHT.h"
#include <limits>

static constexpr const my::Pin pin = D2;
static constexpr const uint8_t type = 11;

DHT dht(pin, type);

void my::init(const SensorEnv &env)
{
  dht.begin();
}

float my::humidity()
{
  return dht.readHumidity();
}

float my::temperature()
{
  return dht.readTemperature();
}

float my::read(Sensor type)
{
  switch (type)
  {
  case Sensor::Humidity:
    return humidity();
  case Sensor::Temperature:
    return temperature();
  default:
    return std::numeric_limits<float>::quiet_NaN();
  }
}
