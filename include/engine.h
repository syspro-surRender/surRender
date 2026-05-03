#ifndef ENGINE_H
#define ENGINE_H


#include "display_manager.h"
#include "render_manager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class Engine {
public:
  Engine(int width, int height, const std::string& title,
         const std::string& modelPath, const std::string& shaderPath);
  void run();

private:
  RenderManager render;
  DisplayManager display;
};

#endif
