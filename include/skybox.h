#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "shader.h"
#include "texture.h"

#include <vector>

struct Cube {
  using uint = unsigned int;

  Cube();
  void setup();
  void draw();

private:
  uint VAO, VBO, EBO;
};

struct Skybox: public Texture {
  Skybox(const std::vector<std::string>& faces);
  ~Skybox();

  void draw(const Shader& shader);

  // private:
  static Cube cube;
};


#endif
