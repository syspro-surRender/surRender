#include "render_manager.h"

#include "display_manager.h"
#include "scene_manager.h"

#include <spdlog/spdlog.h>

RenderManager::RenderManager(DisplayManager& displayManager, SceneManager& sceneManager):
    displayManager(displayManager), sceneManager(sceneManager) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);
}

RenderManager::~RenderManager() {
  spdlog::debug("RenderManager destructor was called");
};

void RenderManager::draw() {
  glClearColor(0.07f, 0.07f, 0.17f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  sceneManager.scene.draw();
}
