#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <string>

struct Texture {
  using uint = unsigned int;

  uint id;

  Texture(std::string path);
  Texture(const Texture&)            = delete;
  Texture& operator=(const Texture&) = delete;

  ~Texture();
};

#endif
