#include "render_manager.h"

#include "display_manager.h"
#include "scene_manager.h"

#include <spdlog/spdlog.h>

RenderManager::RenderManager(DisplayManager& displayManager, SceneManager& sceneManager):
    displayManager(displayManager), sceneManager(sceneManager),
    skyboxShader("assets/shaders/skybox.vert", "assets/shaders/skybox.frag") {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

  Skybox::cube.setup();
}

RenderManager::~RenderManager() {
  spdlog::debug("RenderManager destructor was called");
};

void RenderManager::draw() {
  glClearColor(0.07f, 0.07f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // {
  //   skyboxShader.use();

  //   skyboxShader.setMat4("projection", sceneManager.scene.camera.getProjectionMatrix());
  //   skyboxShader.setMat4("view", glm::mat4(glm::mat3(sceneManager.scene.camera.getViewMatrix())));

  //   sceneManager.scene.skybox.Draw(skyboxShader);
  // }

  sceneManager.scene.draw();
}
