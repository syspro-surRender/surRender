#include "scene_manager.h"

#include "scene.h"

SceneManager::SceneManager():
    scene(), skybox(nullptr) {
  std::vector<std::string> faces = {
      "assets/skybox/img/right.jpg",
      "assets/skybox/img/left.jpg",
      "assets/skybox/img/top.jpg",
      "assets/skybox/img/bottom.jpg",
      "assets/skybox/img/front.jpg",
      "assets/skybox/img/back.jpg"};

  skybox = std::make_unique<Skybox>(faces);
}

SceneManager::~SceneManager() {}

void SceneManager::update(SceneManager::uint deltaTime) {
  for (Model& model : scene.models) {
    model.update(deltaTime);
  }
}
