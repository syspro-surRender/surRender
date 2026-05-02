#define GLM_ENABLE_EXPERIMENTAL

#include "model.h"

#include "GL/glew.h"
#include "shader.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <spdlog/spdlog.h>

Model::Model(std::string, const TransformParameters& params):
    speed(1.0f), aSpeed(1.0f), aVelocity(0.0f), velocity(0.0f) {
  transform = params;
  calculateMatrix();
}

Model::Model(std::vector<Mesh>&& meshes, const TransformParameters& params):
    meshes(std::move(meshes)), speed(1.0f), aSpeed(1.0f), aVelocity(0.0f), velocity(0.0f) {
  transform = params;
  calculateMatrix();
}

Model::~Model() {
  spdlog::info("Destructor of model was called");
}

void Model::draw(const Shader& shader) const {
  unsigned int loc = glGetUniformLocation(shader.program, "transform");
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(modelMatrix));

  // shader.use();
  for (auto& mesh : meshes)
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
