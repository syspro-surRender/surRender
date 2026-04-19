#include "model.h"
#include "shader.h"
#include "GL/glew.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/fwd.hpp>

Model::Model(std::string, const TransformParameters& params): speed(1.0f), aSpeed(1.0f) {
  transform = params;
  calculateMatrix();
}

Model::Model(std::vector<Mesh>&& meshes, const TransformParameters& params): speed(1.0f), aSpeed(1.0f) {
  this->meshes = std::move(meshes);
  transform = params;
  calculateMatrix();
}

void Model::draw(const Shader& shader) const {
  unsigned int loc = glGetUniformLocation(shader.program, "transform");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  for(auto& mesh: meshes)
    mesh.draw(shader);
}
void Model::update(const unsigned int deltaT) {
  transform.position += velocity * (speed * deltaT);
  transform.orientation = glm::quat((aSpeed * deltaT) * aVelocity) * transform.orientation;
  calculateMatrix();
}

void Model::calculateMatrix() {
  modelMatrix = glm::mat4(1.0f);
  modelMatrix = glm::translate(modelMatrix, transform.position);
  modelMatrix = modelMatrix * glm::toMat4(transform.orientation);
}