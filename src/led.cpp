#include "led.h"

void my::toggle(LED &led)
{
  switch (led.state)
  {
  case ToggleState::On:
    // Turn the LED off by making the voltage HIGH
    digitalWrite(led.pin, HIGH);
    led.state = ToggleState::Off;
    break;
  case ToggleState::Off:
    // Turn the LED on by making the voltage LOW
    digitalWrite(led.pin, LOW);
    led.state = ToggleState::On;
    break;
  default:
    // error!
    break;
  }
}
