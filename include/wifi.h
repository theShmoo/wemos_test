#include <WString.h>

struct WiFiData
{
  String ssid;
  String password;
};

bool isConnected();

void init(const WiFiData &wifi);
