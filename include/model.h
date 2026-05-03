#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"
#include "texture.h"

#include <assimp/scene.h>

using namespace std;

class Model {
public:
  Model(const std::string& path);
  void Draw(Shader& shader) const;

private:
  std::vector<Texture> textures_loaded;
  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
