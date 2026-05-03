#include "camera.h"
#include "model.h"
#include "shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <vector>

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800
#define ASPECT (float) WINDOW_WIDTH / (float) WINDOW_HEIGHT

int main() {
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
  sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("log.txt", true));
  spdlog::set_default_logger(std::make_shared<spdlog::logger>("Base", begin(sinks), end(sinks)));

  if (!glfwInit()) {
    spdlog::error("GLFW init failed\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);


  GLFWwindow* window;
  window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    spdlog::error("Window creation failed\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "glew init failed\n";
    return -1;
  }

  Model model("assets/model/banana/source/Banana.glb", {.position = {0.f, 0.f, 0.f}, .orientation = {0.f, 0.f, 0.f, 1.0f}, .scaling = {1.f, 1.f, 1.f}});

  std::string shader_folder_path = "assets/shaders/";
  Shader shader                  = Shader(shader_folder_path + "default.vert", shader_folder_path + "default.frag");

  model.aVelocity = {0.01f, 0.01f, 0.01f};


  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glFrontFace(GL_CCW);

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

    glm::mat4 view       = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix(ASPECT);
    glm::mat4 mvp        = projection * view * model.modelMatrix;

    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model.update(1);

    shader.use();

    shader.setMat4("mvp", mvp);
    shader.setMat4("model", model.modelMatrix);
    shader.setVec3("ourLightPos", glm::vec3(0.0f, 2.0f, 2.0f));

    model.draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  spdlog::info("Terminating");
  glfwTerminate();
  return 0;
}
