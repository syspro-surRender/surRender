#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <string>
#include <vector>

Model::Model(const std::string& path) {
  loadModel(path);
}

void Model::Draw(Shader& shader) {
  for (const auto& mesh : meshes) {
    mesh.draw(shader);
  }
}

void Model::loadModel(const std::string& path) {
  // read file, free memory after work
  Assimp::Importer importer;

  // aiScene contains mRootNode, mMeshes[], mMaterials[], mAnimations[]
  // ReadFile takes path and flags
  const aiScene scene = importer.ReadFile(path,
                                          aiProcess_Triangulate |    // divide all polygons in triangle
                                              aiProcess_FlipUVs |    // standart coord for opengl
                                              aiProcess_GenNormals); // if there is no normals in file, generate them

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    throw std::runtime_error("Assimp error: " + std::string(importer.GetErrorString));
  }

  directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
}

void Model::processModel(aiNode* node, const aiScene* scene) {
  // aiNode contains mName, mTransformation, mMeshes[] -  INDEXES, mChildren[]
  for (size_t i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

    meshes.push_back(processMesh(mesh, scene));
  }

  for (size_t i = 0; i < node->numChildren; i++) {
    processNode(node->mChildren[i]);
  }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  std::vector<uint> textures;

  for (size_t i = 0; i < mesh->numVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;
    vector.x        = mesh->mVertices[i].x;
    vector.y        = mesh->mVertices[i].y;
    vector.z        = mesh->mVertices[i].z;
    vertex.position = vector;

    if (mesh->HasNormals()) {
      vector.x      = mesh->mNormals[i].x;
      vector.y      = mesh->mNormals[i].y;
      vector.z      = mesh->mNormals[i].z;
      vertex.normal = vector;
    }

    if (mesh->mTextureCoords[0]) {
      glm::vec2 vec;
      vec.x           = mesh->mTextureCoords[0][i].x;
      vec.y           = mesh->mTextureCoords[0][i].y;
      vertex.texCoord = vec;
    } else {
      vertex.texCoord = glm::vec2(0.0f, 0.0f);
    }
    vertices.push_back(vertex);
  }
  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];

    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }

  return Mesh(vertices, indices);
}
