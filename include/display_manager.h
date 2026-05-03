#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

class DisplayManager {
public:
  DisplayManager(int width, int height, const std::string& title);
  ~DisplayManager();

  GLFWwindow* getWindow() const;
  bool shouldClose() const;
  void swapBuffers() const;
  void pollEvents() const;

private:
  GLFWwindow* window;
};

#endif
