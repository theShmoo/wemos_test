#include "led.h"
#include "utils.h"
#include "wifi.h"
#include "http.h"

// here define each pins that we use
static LED my_led;
static WiFiData my_wifi;
static Post post;

static constexpr const char fingerprint[] PROGMEM = "03:D6:42:23:03:D1:0C:06:73:F7:E2:BD:29:47:13:C3:22:71:37:1B";

    void
    setup()
{
  my_led = {LED_BUILTIN, ToggleState::Off};
  init(my_led);

  my_wifi = {"wifissid", "wifipassword"};
  init(my_wifi);

  post.fingerprint = fingerprint;
  post.port = 443;
  post.host = "shomoo-wemos.firebaseio.com";
  post.message = R"({"Message": "lol"})";
  post.url = "/data/data.json";
  addHeader(post, "Content-Type", "text/json");
}

void postData()
{
  if (isConnected())
  {
    sendJson(post);
  }
}

void loop()
{
  toggle(my_led);
  postData();
  toggle(my_led);
  // wait 2 seconds before sending another flag
  wait(std::chrono::seconds(2));
}
