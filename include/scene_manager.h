#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "scene.h"

struct SceneManager {
  using uint = unsigned int;
  Scene scene;

  SceneManager();
  ~SceneManager();

  void update(uint);
};

#endif
