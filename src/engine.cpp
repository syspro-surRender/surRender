#include "engine.h"

#include <GLFW/glfw3.h>

using namespace std;

Engine::Engine(int width, int height, const std::string& title,
               const std::string& modelPath, const std::string& shaderPath):
    display(width, height, title), render(modelPath, shaderPath) {
  std::cout << "In engine constructor" << endl;
  GLFWwindow* window = display.getWindow();
  if (!window) {
    std::cerr << "Engine failed to create window.\n";
    return;
  }

  glViewport(0, 0, width, height);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "glew init failed\n";
    return;
  }
}

void Engine::run() {
  GLFWwindow* window = display.getWindow();
  if (!window) {
    return;
  }

  auto lastTime = std::chrono::high_resolution_clock::now();

  while (!display.shouldClose()) {
    auto currentTime = std::chrono::high_resolution_clock::now();
    float deltaTime  = std::chrono::duration<float>(currentTime - lastTime).count();
    lastTime         = currentTime;

    glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    render.update(deltaTime);
    render.draw();

    display.swapBuffers();
    display.pollEvents();

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
  }
}
