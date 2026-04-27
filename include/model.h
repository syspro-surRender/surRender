#ifndef MODEL_H_
#define MODEL_H_

#include "mesh.h"
#include "shader.h"

#include <assimp/scene.h>

using namespace std;

class Model {
public:
  Model(const std::string& path);
  void Draw(Shader& shader) const;

private:
  std::vector<Mesh> meshes;
  std::string directory;

  void loadModel(const std::string& path);
  void processNode(aiNode* node, const aiScene* scene);
  Mesh processMesh(aiMesh* mesh, const aiScene* scene);
};

#endif
