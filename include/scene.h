#ifndef SCENE_H_
#define SCENE_H_

#include "camera.h"
#include "model.h"
#include "skybox.h"

#include <vector>

struct InputManager;

struct Scene {
  Scene();
  ~Scene();

  void draw();

  friend struct SceneManager;
  friend struct InputManager;
  Camera camera;
  Shader shader;

  Skybox skybox;
  Shader skyboxShader;

  std::vector<Model> models;
};

#endif
