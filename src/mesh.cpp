#include "mesh.h"

#include "GL/glew.h"
#include "shader.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices):
    vertices(vertices), indices(indices) {
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  glBufferData(GL_ARRAY_BUFFER, vertices.size(), &vertices[0], GL_STATIC_DRAW);

  // unbinding
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &VBO);
}

void Mesh::draw(Shader& shader) {
}
