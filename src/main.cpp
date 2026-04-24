#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <vector>

int main() {
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
  sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("log.txt"));
  spdlog::set_default_logger(std::make_shared<spdlog::logger>("Base", begin(sinks), end(sinks)));

  if (!glfwInit()) {
    spdlog::error("GLFW init failed\n");
    return -1;
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);

  GLFWwindow* window;
  window = glfwCreateWindow(800, 800, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    spdlog::error("Window creation failed\n");
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 800);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "glew init failed\n";
    return -1;
  }

  std::string shader_folder_path = "assets/shaders/";
  Shader shader                  = Shader(shader_folder_path + "default.vert", shader_folder_path + "default.frag");

  std::vector<Vertex> vertices1 = {
      {{1.0f / 2, -0.707f / 2, 0}, {0.0f, 0.0f}},
      {{-1.0f / 2, -0.707f / 2, 0}, {0.0f, 1.0f}},
      {{0, 0.707f / 2, 1.0f / 2}, {1.0f, 0.0f}},
      {{0, 0.707f / 2, -1.0f / 2}, {1.0f, 1.0f}}};

  std::vector<Vertex> vertices2 = {
      {{1.0f / 2, 0.707f / 2, 0}, {0.0f, 1.0f}}, //
      {{-1.0f / 2, 0.707f / 2, 0}, {0.0f, 0.0f}},
      {{0, -0.707f / 2, 1.0f / 2}, {1.0f, 1.0f}}, //
      {{0, -0.707f / 2, -1.0f / 2}, {1.0f, 0.0f}}};

  std::vector<Mesh::uint> indices1 = {0, 1, 2,
                                      0, 3, 1,
                                      0, 2, 3,
                                      1, 3, 2};

  std::vector<Mesh::uint> indices2 = {0, 2, 1,
                                      0, 1, 3,
                                      0, 3, 2,
                                      1, 2, 3};

  Texture tex1 = {"assets/textures/wall.jpg"};
  Texture tex2 = {"assets/textures/grad.png"};

  std::vector<Mesh::uint> textures1 = {tex1.id};
  std::vector<Mesh::uint> textures2 = {tex2.id};

  Mesh triangle1 = Mesh(vertices1, indices1, textures2);
  Mesh triangle2 = Mesh(vertices2, indices2, textures2);

  std::vector<Mesh> meshes = {};
  meshes.push_back(std::move(triangle1));
  meshes.push_back(std::move(triangle2));

  Model model     = Model(std::move(meshes), {.position = {0.f, 0.f, 0.f}, .orientation = {0.f, 0.f, 0.f, 1.0f}, .scaling = {1.f, 1.f, 1.f}});
  model.aVelocity = {0.01f, 0.01f, 0.01f};

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    model.update(1);
    shader.use();
    model.draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  spdlog::info("Terminating");
  glfwTerminate();
  return 0;
}
