#include "skybox.h"

#include "GL/glew.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"

#include <spdlog/spdlog.h>
#include <vector>

Cube::Cube() {}

void Cube::setup() {
  const static float vertices[8 * 3] = {
      +1.0f, +1.0f, +1.0f,
      +1.0f, -1.0f, +1.0f,
      -1.0f, -1.0f, +1.0f,
      -1.0f, +1.0f, +1.0f,
      +1.0f, +1.0f, -1.0f,
      +1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f, +1.0f, -1.0f};
  const static uint indices[6 * 6] = {0, 1, 2, 0, 2, 3, 0, 7, 4, 0, 3, 7, 0, 5, 1, 0, 4, 5,
                                      6, 5, 4, 6, 4, 7, 6, 1, 5, 6, 2, 1, 6, 7, 3, 6, 3, 2};

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);


  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Cube::draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

Cube Skybox::cube = Cube();

Skybox::Skybox(const std::vector<std::string>& faces):
    Texture(0) {
  int width, height, nrChannels;

  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);

  for (GLuint i = 0; i < faces.size(); i++) {
    unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
    spdlog::debug(faces[i].c_str());
    if (data) {
      spdlog::debug(faces[i].c_str());
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    }
  }

  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

Skybox::~Skybox() {}

void Skybox::draw(const Shader& shader) {
  shader.use();

  glDepthFunc(GL_LEQUAL); // GL_LESS by default
  // glDepthMask(GL_FALSE);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, id);

  cube.draw();

  // glDepthMask(GL_TRUE);
  glDepthFunc(GL_LESS);
}
