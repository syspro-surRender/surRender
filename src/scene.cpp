#include "scene.h"

#include "camera.h"
#include "model.h"
#include "shader.h"

#include <glm/glm.hpp>

Scene::Scene():
    camera(glm::vec3(0.0f, 0.0f, 3.0f), 16. / 9),
    shader("assets/shaders/default.vert", "assets/shaders/default.frag"),
    skyboxShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag"),
    skybox({"assets/skybox/img/right.jpg",
            "assets/skybox/img/left.jpg",
            "assets/skybox/img/top.jpg",
            "assets/skybox/img/bottom.jpg",
            "assets/skybox/img/front.jpg",
            "assets/skybox/img/back.jpg"}) {
  TransformParameters tp = {.position    = {0.f, 0.f, 0.f},
                            .orientation = glm::rotate(glm::quat({0.f, 0.f, 0.f, -1.f}), -7.0f * glm::pi<float>() / 8, {0, 0, 1}),
                            .scaling     = {.5f, .5f, .5f}};


  Model model     = Model("assets/model/banana/source/Banana.glb", tp);
  model.aVelocity = {0.0f, 0.05f, 0.0f};
  models.push_back(std::move(model));
}

Scene::~Scene() {}

void Scene::draw(const Shader& skyboxShader) {
  glm::mat4 MVP(1.0);
  glm::mat4 M(1.0);
  glm::mat4 VP = camera.getProjectionMatrix() * camera.getViewMatrix();

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

    skyboxShader.setMat4("projection", camera.getProjectionMatrix());
    skyboxShader.setMat4("view", glm::mat4(glm::mat3(camera.getViewMatrix())));

    glDepthMask(GL_FALSE);
    skybox.Draw(skyboxShader);
    glDepthMask(GL_TRUE);
  }
}
