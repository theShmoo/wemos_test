#include "wifi.h"

#include "utils.h"

#include <ESP8266WiFi.h>

bool isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

void init(const WiFiData & wifi)
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi.ssid, wifi.password);

  while (!isConnected())
  {
    wait(std::chrono::milliseconds(500));
  }
}
