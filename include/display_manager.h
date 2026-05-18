#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Engine;
struct InputManager;

struct DisplayManager {
  DisplayManager();
  DisplayManager(const DisplayManager&) = delete;
  ~DisplayManager();

  bool shouldClose() const;
  void swapBuffers() const;
  void pollEvents() const;

private:
  friend struct Engine;
  friend struct InputManager;
  GLFWwindow* window;
};

#endif
