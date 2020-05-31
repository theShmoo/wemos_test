#include "http.h"

#include <WiFiClientSecure.h>

void sendJson(const Post & post)
{
  WiFiClientSecure client;
  client.setFingerprint(post.fingerprint);
  if (client.connect(post.host, post.port))
  {
    String postMessage = "POST " + post.url + " HTTP/1.1\n";
    postMessage += "Host: " + post.host + "\n";
    for (const auto &header : post.header)
    {
      postMessage += header.name + ": " + header.value + "\n";
    }
    postMessage += "Content-Length: " + String(post.message.length(), 10) + "\n\n" + post.message + "\n";
    client.print(postMessage);
  }
}
