#include "pins.h"

namespace my
{
  // the state of an led can be turned on or off
  enum class ToggleState : bool
  {
    On = true,
    Off = false
  };

  // a type for a led
  struct LED
  {
    Pin pin;
    ToggleState state;
  };

  // initialize the output of the given led
  inline void init(LED led) { pinMode(led.pin, OUTPUT); }

  // toggle the light of the led
  // this modifies the state of the led (off <--> on)
  void toggle(LED &led);
} // namespace my
