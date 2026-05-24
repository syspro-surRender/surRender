#ifndef SKYBOX_H_
#define SKYBOX_H_

#include "display_manager.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"

#include <vector>

struct Skybox {
private:
  GLuint vao;
  GLuint vbo;
  GLuint cubemapTexture;

public:
  Skybox(const std::vector<std::string>& faces);
  ~Skybox();

  void Draw(const Shader& shader);
};

#endif
