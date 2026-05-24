#include "input_manager.h"

#include "display_manager.h"
#include "scene_manager.h"

#include <GLFW/glfw3.h>

InputManager::InputManager(const DisplayManager& displayManager, SceneManager& SceneManager):
    displayManager(displayManager),
    camera(SceneManager.scene.camera) {}

InputManager::~InputManager() {}

void InputManager::processInput(bool& done) {
  displayManager.pollEvents();
  GLFWwindow* window = displayManager.window;

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.moveForward(0.016f);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.moveBackward(0.016f);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.moveLeft(0.016f);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.moveRight(0.016f);
  if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    camera.moveUp(0.016f);
  if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    camera.moveDown(0.016f);

  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    camera.rotateYaw(-1.0f);
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    camera.rotateYaw(1.0f);

  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    camera.rotatePitch(1.0f);
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    camera.rotatePitch(-1.0f);

  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  }

  done = glfwWindowShouldClose(window);
}
