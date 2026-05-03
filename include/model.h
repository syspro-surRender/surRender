#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"
#include "stb_image.h"
#include "texture.h"

#include <assimp/scene.h>
#include <memory>

using namespace std;

class Model {
public:
  Model(const std::string& path);
  void Draw(Shader& shader) const;

private:
  struct TextureCacheEntry {
    std::string path;
    uint id;
  };

  std::vector<TextureCacheEntry> textureCache;

  std::vector<std::unique_ptr<Mesh>> meshes;
  std::string directory;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  std::vector<uint> loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName);
  std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
