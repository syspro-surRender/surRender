#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstring>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define ASPECT WINDOW_WIDTH / WINDOW_HEIGHT

const char* vertexShaderSource =
    "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 view;"
    "uniform mat4 projection;"
    "void main()\n"
    "{\n"
    "   gl_Position = projection * view * vec4(aPos, 1.0);\n"
    "}\0";

const char* fragmentShaderSource =
    "#version 460 core\n"
    "out vec4 FragColor;\n\n"

    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
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
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    std::cerr << "window creation failed\n";
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

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

  unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
  unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");

  float vertices[] = {-0.8f, -0.8f, 0.0f,
                     0.8f, -0.8f, 0.0f,
                     0.0f,  0.8f, 0.0f,
					-1.8f, -0.8f, -10.0f,
                     1.8f, -0.8f, -10.0f,
                     1.0f,  0.8f, -10.0f};


  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
  glEnableVertexAttribArray(0);

  // non necessary
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

  do {
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

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix(ASPECT);
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    glDrawArrays(GL_TRIANGLES, 0, 6);
    // glDrawElements(GL_TRIANGLES, ));

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  glfwTerminate();
  return 0;
}
