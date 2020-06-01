#include "led.h"
#include "utils.h"
#include "wifi.h"
#include "http.h"

static LED my_led;
static WiFiData my_wifi;
static Post post;

static constexpr const char fingerprint[] = "03:D6:42:23:03:D1:0C:06:73:F7:E2:BD:29:47:13:C3:22:71:37:1B";
static constexpr const char host[] = "shomoo-wemos.firebaseio.com";
static constexpr const char url[] = "/databases/data/data.json";
static constexpr const Port port = 443;

void setup()
{
  Serial.begin(9600);

  my_led = {LED_BUILTIN, ToggleState::Off};
  init(my_led);

  my_wifi = {"Routers of Rohan", "wereresse"};
  init(my_wifi);

  post.fingerprint = fingerprint;
  post.port = port;
  post.contentType = ContentType::JSON;
  post.host = host;
  post.message = R"({"Message": "lol"})";
  post.url = url;
}

void postData()
{
  if (isConnected())
  {
    send(post);
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
