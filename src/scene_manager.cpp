#include "scene_manager.h"

#include "scene.h"

SceneManager::SceneManager():
    scene() {}

SceneManager::~SceneManager() {}

void SceneManager::update(SceneManager::uint deltaTime) {
  for (Model& model : scene.models) {
    model.update(deltaTime);
  }
}
