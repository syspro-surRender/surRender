#include "scene.h"

#include "camera.h"
#include "model.h"
#include "shader.h"

#include <glm/glm.hpp>
#include <spdlog/spdlog.h>

Scene::Scene():
    camera(glm::vec3(0.0f, 0.0f, 3.0f), 16. / 9),
    shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
    skybox({"assets/skybox/img/right.png",
            "assets/skybox/img/left.png",
            "assets/skybox/img/top.png",
            "assets/skybox/img/bottom.png",
            "assets/skybox/img/front.png",
            "assets/skybox/img/back.png"}),
    skyboxShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag") {
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
  glm::mat4 VP   = camera.getProjectionMatrix() * camera.getViewMatrix();
  glm::mat4 VPCM = camera.getProjectionMatrix() * glm::mat4(glm::mat3(camera.getViewMatrix()));

  shader.use();
  for (Model& model : models) {
    M = model.modelMatrix;

    MVP = VP * M;

    shader.setMat4("model", M);
    shader.setMat4("mvp", MVP);
    shader.setVec3("ourLightPos", glm::vec3(0.0f, 2.0f, 2.0f));

    model.draw(shader);
  }

  {
    skyboxShader.use();

    skyboxShader.setMat4("vp", VPCM);

    skybox.draw(skyboxShader);
  }
}
