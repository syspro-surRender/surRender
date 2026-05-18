#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"

#include <assimp/scene.h>
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

  // std::vector<std::unique_ptr<Mesh>> meshes;
  std::string directory;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  std::vector<uint> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);

  Model(const std::string&, const TransformParameters&);
  Model(std::vector<Mesh>&&, const TransformParameters&);

  Model(Model&&);
  ~Model();

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
