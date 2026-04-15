#include "mesh.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

const char* vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n\n"

    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

int main() {
  if (!glfwInit()) {
    std::cerr << "GLFW init failed\n";
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

  GLFWwindow* window;
  window = glfwCreateWindow(800, 600, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    std::cerr << "window creation failed\n";
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 600);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "glew init failed\n";
    return -1;
  }

  // glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

  unsigned int vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram;
  shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  std::vector<Vertex> vertices = {
      {{-0.5f, -0.5f, 0.0f}},
      {{0.4f, -0.5f, 0.0f}},
      {{0.5f, 0.5f, 0.0f}},
      {{-0.4f, 0.5f, 0.0f}}};

  std::vector<Mesh::uint> indices = {0, 1, 2,
                                     0, 2, 3};

  Mesh triangle = Mesh(vertices, indices);
  Shader shader = Shader(shaderProgram);

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    triangle.draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  glfwTerminate();
  return 0;
}
