#include "scene.h"

#include "light.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "settings.h"

#include <glm/glm.hpp>

const std::vector<Light> LIGHTS = {
  {{2.0f, 3.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, 3.f},
  {{-1.0f, 1.0f, 2.0f}, {0.0f, 1.0f, 0.0f}, 2.f},
  {{1.0f, 1.0f, -4.0f}, {0.5f, 0.5f, 0.8f}, 1.f}
};

Scene::Scene():
    camera(glm::vec3(0.0f, 0.0f, 3.0f), ASPECT),
    shader("assets/shaders/default.vert", "assets/shaders/default.frag") {
  TransformParameters tp = {.position    = {0.f, -0.4f, 0.f},
                            .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
                            .scaling     = {.5f, .5f, .5f}};

  Model model     = Model("assets/model/banana/source/Banana.glb", tp);
  model.aVelocity = {0.0f, 0.05f, 0.0f};
  models.push_back(std::move(model));

  tp = {.position    = {-3.f, -0.2f, -2.f},
        .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
        .scaling     = {.5f, .5f, .5f}};

  Model model1    = Model("assets/model/banana/source/Banana.glb", tp);
  model1.aVelocity = {0.04f, 0.0f, -0.03f};
  models.push_back(std::move(model1));

  tp = {.position    = {2.2f, 0.3f, -3.f},
      .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
      .scaling     = {.5f, .5f, .5f}};

  Model model2 = Model("assets/model/banana/source/Banana.glb", tp);
  model2.aVelocity = {0.01f, -0.02f, 0.05f};
  models.push_back(std::move(model2));


  tp = {.position    = {-1.6f, 0.4f, -4.f},
      .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
      .scaling     = {.5f, .5f, .5f}};


  Model model3 = Model("assets/model/banana/source/Banana.glb", tp);
  model3.aVelocity = {0.03f, 0.05f, 0.02f};
  models.push_back(std::move(model3));

  tp = {.position    = {0.f, 1.5f, -2.f},
      .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
      .scaling     = {.01f, .01f, .01f}};

  Model discoModel = Model("assets/model/ball/source/disco_ball.glb", tp);
  discoModel.aVelocity = {0.f, -0.06f, 0.f};
  models.push_back(std::move(discoModel));

  std::vector<Vertex> floorVertices = {
      {{-5.0f, -1.0f, -5.0f}, {0.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
      {{ 5.0f, -1.0f, -5.0f}, {1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
      {{ 5.0f, -1.0f,  5.0f}, {1.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
      {{-5.0f, -1.0f,  5.0f}, {0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}}
  };
  std::vector<Mesh::uint> floorIndices = {0,1,2, 0,2,3};

  Texture floorTex("assets/textures/wall.jpg");
  std::vector<Mesh::uint> floorTextures = {floorTex.id};

  Mesh floorMesh(floorVertices, floorIndices, floorTextures);
  std::vector<Mesh> floorMeshes;
  floorMeshes.push_back(std::move(floorMesh));

  TransformParameters floorTp = {
      .position = {0.f, -2.f, -2.5f},
      .orientation = {0.f, 0.f, 0.f, 1.f},
      .scaling = {1.f, 1.f, 1.f}
  };

  Model floorModel(std::move(floorMeshes), floorTp);
  floorModel.aVelocity = {0.f, -0.01f, 0.f};
  models.push_back(std::move(floorModel));
}

Scene::~Scene() {}

void Scene::draw() {
  glm::mat4 MVP(1.0);
  glm::mat4 M(1.0);
  glm::mat4 VP = camera.getProjectionMatrix() * camera.getViewMatrix();

  shader.use();

  for (int i = 0; i < LIGHTS.size(); i++) {
    shader.setVec3("ourLights[" + std::to_string(i) + "].pos", LIGHTS[i].pos);
    shader.setVec3("ourLights[" + std::to_string(i) + "].color", LIGHTS[i].color);
    shader.setFloat("ourLights[" + std::to_string(i) + "].intensity", LIGHTS[i].intensity);
  }

  shader.setInt("ourLightsN", LIGHTS.size());

  for (Model& model : models) {
    M = model.modelMatrix;

    MVP = VP * M;

    shader.setMat4("model", M);
    shader.setMat4("mvp", MVP);

    model.draw(shader);
  }
}
