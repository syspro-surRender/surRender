#include "mesh.h"

#include "GL/glew.h"
#include "shader.h"

#include <GL/gl.h>
#include <cstddef>
#include <spdlog/spdlog.h>
#include <utility>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices, const std::vector<uint>& textures):
    vertices(vertices), indices(indices), textures(textures) {
  {
    Mesh::uint buffers[2];
    glGenBuffers(2, buffers);
    VBO = buffers[0];
    EBO = buffers[1];
  }
  glGenVertexArrays(1, &VAO);

  glBindVertexArray(VAO);

  // storing vertices to opengl
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Mesh::uint), &indices[0], GL_STATIC_DRAW);

  // setting vertex position pointer
  glVertexAttribPointer(0, decltype(Vertex::position)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
  glEnableVertexAttribArray(0);

  // setting vertex texture coordinates pointer
  glVertexAttribPointer(1, decltype(Vertex::texCoord)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, texCoord));
  glEnableVertexAttribArray(1);

  // setting vertex normal pointer
  glVertexAttribPointer(2, decltype(Vertex::normal)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));
  glEnableVertexAttribArray(2);

  // unbinding
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::Mesh(Mesh&& other) {
  std::swap(vertices, other.vertices);
  std::swap(indices, other.indices);
  std::swap(textures, other.textures);

  VAO       = other.VAO;
  VBO       = other.VBO;
  EBO       = other.EBO;
  other.VAO = other.VBO = other.EBO = 0;
}

Mesh::~Mesh() {
  spdlog::info("Destructor of mesh with VAO {}, VBO {}, EBO {} was called", VAO, VBO, EBO);
  if (VBO) {
    Mesh::uint buf[2] = {VBO, EBO};
    glDeleteBuffers(2, buf);
    glDeleteVertexArrays(1, &VAO);
  }
}

void Mesh::draw(const Shader& shader) const { //todo: draw() & draw(const Shader&)
  // shader.use();                               //todo rethink rebinding shader each draw (reuse shader across meshes?)
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textures[0]);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
