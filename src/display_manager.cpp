#include "display_manager.h"

#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

DisplayManager::DisplayManager(int width, int height, const std::string& title) {
  std::cout << "In display constructor" << std::endl;
  if (!glfwInit()) {
    std::cerr << "GLFW init failed\n";
    return;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);


  GLFWwindow* window;
  window = glfwCreateWindow(800, 800, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    std::cerr << "window creation failed\n";
    return;
  }
  glfwMakeContextCurrent(window);
}

DisplayManager::~DisplayManager() {
  if (window) {
    glfwDestroyWindow(window);
    glfwTerminate();
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

GLFWwindow* DisplayManager::getWindow() const {
  return window;
}
