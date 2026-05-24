#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "display_manager.h"
#include "scene_manager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct RenderManager {
  RenderManager(DisplayManager&, SceneManager&);
  ~RenderManager();
  void draw();

private:
  DisplayManager& displayManager;
  SceneManager& sceneManager;
  Shader skyboxShader;
};

#endif
