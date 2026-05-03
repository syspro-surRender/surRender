#ifndef MESH_H_
#define MESH_H_

#include "shader.h"
#include "texture.h"

#include <glm/glm.hpp>
#include <vector>

extern "C" struct Vertex {
  glm::vec3 position;
  glm::vec2 texCoord;
  glm::vec3 normal;
};

struct Mesh {
  using uint = unsigned int;

  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  std::vector<Texture::uint> textures;

  uint VBO, VAO, EBO;

  // We REALLY don't want Mesh to be deleted from GPU if we accidentaly copied and deleted it, so we forbid copies altogether
  // With this we're effectively assuring that Meshes passed by reference. No problems with moving, btw
  Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, const std::vector<uint>& textures);
  Mesh(const Mesh&) = delete;
  Mesh(Mesh&&);
  Mesh& operator=(const Mesh&) = delete;
  ~Mesh();

  void draw(const Shader& shader) const;
};

#endif
