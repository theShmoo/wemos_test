#include "led.h"
#include "utils.h"
#include "wifi.h"
#include "http.h"
#include "sensors.h"

static constexpr const my::WiFiData my_wifi{"", ""};
static constexpr const char fingerprint[] = "03:D6:42:23:03:D1:0C:06:73:F7:E2:BD:29:47:13:C3:22:71:37:1B";
static constexpr const char host[] = "shomoo-wemos.firebaseio.com";
static constexpr const char url[] = "/databases/data/data.json";
static constexpr const my::Port port = 443;

static constexpr const my::SensorEnv sensors{D2};

static my::Post post;
static my::LED my_led{LED_BUILTIN, my::ToggleState::Off};

void init(my::Post &post)
{
  post.fingerprint = fingerprint;
  post.port = port;
  post.contentType = my::ContentType::JSON;
  post.host = host;
  post.message = "";
  post.url = url;
}

void setup()
{
  Serial.begin(9600);

  my::init(my_led);
  my::init(my_wifi);
  my::init(sensors);
  init(post);
}

void postData()
{
  const auto humidity = my::humidity();
  const auto temperature = my::temperature();

  static constexpr const size_t MaxMessageLength = 128;
  char message[MaxMessageLength];

  snprintf_P(message, MaxMessageLength,
             R"({"Temperature": %.2f, "Humidity": %.2f})",
             temperature, humidity);

  Serial.printf("Message: %s\n", message);
  post.message = message;

  if (my::isConnected())
  {
    my::send(post);
  }
}

void loop()
{
  my::toggle(my_led);
  postData();
  my::toggle(my_led);
  // wait 2 seconds before sending another flag
  my::wait(std::chrono::seconds(10));
}
