#include <stdint.h>
using Port = uint16_t;

// the type of the content of the request
enum class ContentType
{
  JSON,
  None
};

// A structure defining a post http request
struct Post
{
  const char * host;
  Port port;
  const char * fingerprint;
  const char * url;
  const char * message;
  ContentType contentType;
};

// send the given post request
void send(const Post & post);
