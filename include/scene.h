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

  void draw(const Shader& skyboxShader);

  friend struct SceneManager;
  friend struct InputManager;
  Skybox skybox;
  Shader skyboxShader;
  Camera camera;
  Shader shader;

  std::vector<Model> models;
};

#endif
