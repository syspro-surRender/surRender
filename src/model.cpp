#include "model.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "GL/glew.h"
#include "model.h"
#include "shader.h"

#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <string>
#include <vector>

void Model::loadModel(const std::string& path) {
  // read file, free memory after work
  Assimp::Importer importer;

  // aiScene contains mRootNode, mMeshes[], mMaterials[], mAnimations[]
  // ReadFile takes path and flags
  const aiScene* scene = importer.ReadFile(path,
                                           aiProcess_Triangulate |    // divide all polygons in triangle
                                               aiProcess_FlipUVs |    // standart coord for opengl
                                               aiProcess_GenNormals); // if there is no normals in file, generate them

  if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    throw std::runtime_error("Assimp error: " + std::string(importer.GetErrorString()));
  }

  directory = path.substr(0, path.find_last_of('/'));

  processNode(scene->mRootNode, scene);
}

uint TextureFromFile(const char* path, const std::string& directory) {
  std::string filename = "Untitled_0.png";
  if (!path || path[0] == '\0') {
    std::cout << "Skipping empty texture path." << std::endl;
    return 0;
  }

  filename = "assets/model/banana/textures/Untitled_0.png";

  uint textureID;
  glGenTextures(1, &textureID);

  int width, height, nrComponents;
  unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
  if (data) {
    GLenum format;
    if (nrComponents == 1) {
      format = GL_RED;
    } else if (nrComponents == 3) {
      format = GL_RGB;
    } else if (nrComponents == 4) {
      format = GL_RGBA;
    }

    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
  } else {
    std::cout << "Texture failed to load at path: " << path << std::endl;
    stbi_image_free(data);
  }

  return textureID;
}

std::vector<uint> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, const std::string& typeName) {
  std::vector<uint> ids;

  for (size_t i = 0; i < mat->GetTextureCount(type); i++) {
    aiString str;
    mat->GetTexture(type, i, &str);

    bool skip = false;
    // for (const auto& loaded : textureCache) {
    //   if (std::strcmp(loaded.path.c_str(), str.C_Str()) == 0) {
    //     ids.push_back(loaded.id);
    //     skip = true;
    //     break;
    //   }
    // }

    if (!skip) {
      uint textureID = TextureFromFile(str.C_Str(), directory);
      // textureCache.push_back({std::string(str.C_Str()), textureID});
      ids.push_back(textureID);
    }
  }
  return ids;
}

void Model::processNode(aiNode* node, const aiScene* scene) {
  // aiNode contains mName, mTransformation, mMeshes[] -  INDEXES, mChildren[]
  for (size_t i = 0; i < node->mNumMeshes; i++) {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

    meshes.push_back(processMesh(mesh, scene));
  }

  for (size_t i = 0; i < node->mNumChildren; i++) {
    processNode(node->mChildren[i], scene);
  }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
  std::vector<Vertex> vertices;
  std::vector<uint> indices;
  std::vector<uint> textures;

  for (size_t i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;
    glm::vec3 vector;
    vector.x        = mesh->mVertices[i].x;
    vector.y        = mesh->mVertices[i].y;
    vector.z        = mesh->mVertices[i].z;
    vertex.position = vector;

    if (mesh->HasNormals()) {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
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

  if (mesh->mMaterialIndex >= 0) {
    aiMaterial* material         = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<uint> diffuseIDs = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseIDs.begin(), diffuseIDs.end());

    std::vector<uint> specularIDs = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularIDs.begin(), specularIDs.end());
  }

  return Mesh(vertices, indices, textures);
}

Model::Model(const std::string& path, const TransformParameters& params):
    speed(1.0f), aSpeed(1.0f), aVelocity(0.0f), velocity(0.0f) {
  loadModel(path);
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
  modelMatrix = glm::scale(modelMatrix, transform.scaling);
  modelMatrix = modelMatrix * glm::toMat4(glm::normalize(transform.orientation));
}
