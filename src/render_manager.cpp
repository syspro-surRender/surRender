#include "render_manager.h"

#include <iostream>

RenderManager::RenderManager(const std::string& modelPath):
    model(modelPath),
    shader(shaderPath + "default.frag", shaderPath + "default.vert") {
  std::cout << "In render constructor" << endl;
  glEnable(GL_DEPTH_TEST);
}

void RenderManager::update(float delta) {
  rotationAngle += 50.0f * delta;
}

void RenderManager::draw() {
  // add shader.use() when shareds will be ready
  model.Draw(shader);
}
