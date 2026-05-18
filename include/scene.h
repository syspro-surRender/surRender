#ifndef SCENE_H_
#define SCENE_H_

#include "camera.h"
#include "model.h"

#include <vector>

struct InputManager;

struct Scene {
  Scene();
  ~Scene();

  void draw();

private:
  friend struct SceneManager;
  friend struct InputManager;
  Camera camera;
  Shader shader;

  std::vector<Model> models;
};

#endif
