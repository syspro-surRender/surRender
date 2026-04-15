#include "mesh.h"

#include "GL/glew.h"
#include "shader.h"

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint>& indices):
    vertices(vertices), indices(indices) {
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
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  // unbinding
  glBindVertexArray(0);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &VBO);
  glDeleteVertexArrays(1, &VAO);
}

void Mesh::draw(Shader& shader) {
  glUseProgram(shader.id);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}
