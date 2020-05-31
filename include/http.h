#include <WString.h>
#include <vector>

struct Header
{
  String name;
  String value;
};

struct Post
{
  String host;
  uint16_t port;
  const char * fingerprint;

  std::vector<Header> header;
  String url;
  String message;
};

inline void addHeader(Post & post, String name, String value)
{
  post.header.push_back({name, value});
}

void sendJson(const Post & post);
