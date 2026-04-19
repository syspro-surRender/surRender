#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <unordered_map>
#include <vector>

struct TransformParameters {
  glm::vec3 position;
  glm::quat orientation;
  glm::vec3 scaling;
};

struct Model;

struct Model {
  static std::unordered_map<std::string, Texture::uint> textureCache;

  std::vector<Mesh> meshes;
  glm::mat4 modelMatrix;

  Model(std::string, const TransformParameters&);
  Model(std::vector<Mesh>&&, const TransformParameters&);

  void update(const unsigned int); //todo: change to time type
  void draw(const Shader&) const;

// private:
  void calculateMatrix();
  TransformParameters transform;

  const float speed, aSpeed;

  glm::vec3 aVelocity;
  glm::vec3 velocity;
};

#endif