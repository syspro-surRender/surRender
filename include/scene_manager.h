#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "scene.h"
#include "skybox.h"

#include <memory>

struct SceneManager {
  using uint = unsigned int;
  Scene scene;
  std::unique_ptr<Skybox> skybox;

  SceneManager();
  ~SceneManager();

  void update(uint);
};

#endif
