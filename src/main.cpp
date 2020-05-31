#include "led.h"
#include "utils.h"

#include <Arduino.h>
#include <chrono>

// here define each pins that we use
static LED my_led;


void setup()
{
  my_led = {LED_BUILTIN, ToggleState::Off};
  InitOutput(my_led);
}

void loop()
{
  toggle(my_led);
  wait(std::chrono::seconds(1));
  toggle(my_led);
  wait(std::chrono::seconds(2));
}
