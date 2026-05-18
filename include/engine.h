#ifndef ENGINE_H
#define ENGINE_H

#include "display_manager.h"
#include "input_manager.h"
#include "render_manager.h"
#include "scene_manager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Engine {
  Engine();
  ~Engine();
  void run();

private:
  DisplayManager displayManager;
  SceneManager sceneManager;
  RenderManager renderManager;
  InputManager inputManager;
};

#endif
