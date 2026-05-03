#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H


#include "mesh.h"
#include "model.h"
#include "shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class RenderManager {
public:
  RenderManager(const std::string& modelPath, const std::string& shaderPath);
  void update(float delta);
  void draw();

private:
  Model model;
  Shader shader;

  float rotationAngle;
};

#endif
