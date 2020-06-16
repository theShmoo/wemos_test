#include "http.h"

#include <WiFiClientSecure.h>

static constexpr const size_t MaxMessageLength = 512;

using Message = char[MaxMessageLength];

size_t requestLine(
    const my::Post &post,
    Message message,
    size_t currentLength)
{
  return currentLength + snprintf_P(message + currentLength,
                                    MaxMessageLength - currentLength,
                                    "POST %s HTTP/1.1\n", post.url);
}

size_t generalHeader(
    const my::Post &post,
    Message message,
    size_t currentLength)
{
  return currentLength + snprintf_P(message + currentLength,
                                    MaxMessageLength - currentLength,
                                    "Host: %s\n", post.host);
}

const char *contentTypeStr(my::ContentType type)
{
  switch (type)
  {
  case my::ContentType::JSON:
    return "Content-Type: application/json";
  default:
    return "";
  }
}

size_t entityHeader(
    const my::Post &post,
    Message message,
    size_t currentLength)
{
  return currentLength + snprintf_P(message + currentLength,
                                    MaxMessageLength - currentLength,
                                    "%s\nContent-Length: %d\n\n",
                                    contentTypeStr(post.contentType), strlen(post.message));
}

int buildMessage(const my::Post &post, Message message)
{
  char *msg = message;
  auto messageLength = requestLine(post, msg, 0);
  messageLength = generalHeader(post, msg, messageLength);
  messageLength = entityHeader(post, msg, messageLength);
  return messageLength + snprintf_P(msg + messageLength, MaxMessageLength - messageLength, "%s\n", post.message);
}

void my::send(const Post &post)
{
  WiFiClientSecure client;
  client.setFingerprint(post.fingerprint);
  if (client.connect(post.host, post.port))
  {
    Serial.println("sending data...");
    Message message;
    const auto messageLength = buildMessage(post, message);
    // Serial.println(message);
    // Serial.printf("Length: %d\n", messageLength);
    // send
    const auto sendBytes = client.write_P(message, messageLength);
    Serial.printf("%d data sent\n", sendBytes);
  }
  else
  {
    Serial.println("could not connect");
  }
}
