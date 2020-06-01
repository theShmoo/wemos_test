struct WiFiData
{
  const char * ssid;
  const char *password;
};

bool isConnected();

void init(const WiFiData &wifi);
