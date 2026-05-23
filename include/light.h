#ifndef LIGHTSTRUCT
#define LIGHTSTRUCT

#include <glm/glm.hpp>

struct Light {
  glm::vec3 pos;
  glm::vec3 color;
  float intensity;
};

#endif
