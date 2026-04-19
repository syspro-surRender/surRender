#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

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
  window = glfwCreateWindow(800, 800, "Test", nullptr, nullptr);
  if (window == nullptr) {
    glfwTerminate();
    std::cerr << "window creation failed\n";
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

  std::vector<Vertex> vertices = {
      {{0.0f, 0.5f, 0.0f}, {0.0f, 0.5f}},
      {{0.433f, -0.25f, 0.0f}, {0.433f, -0.25f}},
      {{-0.433f, -0.25f, 0.0f}, {-0.433f, -0.25f}},
      {{0.0f, -0.5f, 0.0f}, {0.0f, -0.5f}},
      {{0.433f, 0.25f, 0.0f}, {0.433f, 0.25f}},
      {{-0.433f, 0.25f, 0.0f}, {-0.433f, 0.25f}},
  };

  std::vector<Mesh::uint> indices = {0, 1, 2,
                                     3, 4, 5};

  Texture tex = {"assets/textures/wall.jpg"};

  std::vector<Mesh::uint> textures = {tex.id};

  Mesh triangle = Mesh(vertices, indices, textures);

  std::vector<Mesh> meshes;
  meshes.push_back(std::move(triangle));

  Model model = Model(std::move(meshes), {.position={0.f, 0.f, 0.f}, .orientation={0.f, 0.f, 0.f, 1.0f}, .scaling={1.f, 1.f, 1.f}});
  model.aVelocity = {0, 0, 0.05f};

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  do {
    glClear(GL_COLOR_BUFFER_BIT);

    model.update(1);
    // triangle.draw(shader);
    model.draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  glfwTerminate();
  return 0;
}
