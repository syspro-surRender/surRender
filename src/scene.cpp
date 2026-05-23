#include "scene.h"

#include "light.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "settings.h"

#include <glm/glm.hpp>

const std::vector<Light> LIGHTS = {
  {{2.0f, 3.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, 1.0f},
  {{-1.0f, 1.0f, 2.0f}, {0.0f, 1.0f, 0.0f}, 0.6f}
};

Scene::Scene():
    camera(glm::vec3(0.0f, 0.0f, 3.0f), ASPECT),
    shader("assets/shaders/default.vert", "assets/shaders/default.frag") {
  TransformParameters tp = {.position    = {0.f, 0.f, 0.f},
                            .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
                            .scaling     = {.5f, .5f, .5f}};

  Model model     = Model("assets/model/banana/source/Banana.glb", tp);
  model.aVelocity = {0.0f, 0.05f, 0.0f};
  models.push_back(std::move(model));
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
