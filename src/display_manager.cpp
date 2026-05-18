#include "display_manager.h"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

using namespace std;

DisplayManager::DisplayManager() {
  if (!glfwInit()) {
    spdlog::error("GLFW init failed");
    return;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);


  window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    spdlog::error("Window creation failed");
    return;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 600);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    spdlog::error("GLEW init failed\n");
    return;
  }
}

DisplayManager::~DisplayManager() {
  spdlog::debug("DisplayManager destructor was called");
  if (window) {
    glfwDestroyWindow(window);
  }
}

bool DisplayManager::shouldClose() const {
  return glfwWindowShouldClose(window);
}

void DisplayManager::swapBuffers() const {
  glfwSwapBuffers(window);
}

void DisplayManager::pollEvents() const {
  glfwPollEvents();
}
