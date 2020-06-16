#include "wifi.h"
#include "utils.h"

#include <ESP8266WiFi.h>

bool my::isConnected()
{
  return WiFi.status() == WL_CONNECTED;
}

void my::init(const WiFiData &wifi)
{
  Serial.println("Connecting to wifi...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi.ssid, wifi.password);

  while (!isConnected())
  {
    wait(std::chrono::milliseconds(500));
  }
  Serial.println("Connected!");
}
