#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "texture.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>

int main() {
  if (!glfwInit()) {
    std::cerr << "GLFW init failed\n";
    return -1;
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
    return -1;
  }
  glfwMakeContextCurrent(window);

  glViewport(0, 0, 800, 800);

  glewExperimental = GL_TRUE;
  if (glewInit() != GLEW_OK) {
    std::cerr << "glew init failed\n";
    return -1;
  }

  Model spinningBananaCat("assets/model/bananacat/source/Banana.glb");

  std::string shader_folder_path = "assets/shaders/";
  Shader shader                  = Shader(shader_folder_path + "default.vert", shader_folder_path + "default.frag");

  glEnable(GL_DEPTH_TEST);

  // std::vector<Vertex> vertices = {
  //     {{0.0f, 0.5f, 0.0f}, {0.0f, 0.5f}},
  //     {{0.433f, -0.25f, 0.0f}, {0.433f, -0.25f}},
  //     {{-0.433f, -0.25f, 0.0f}, {-0.433f, -0.25f}},
  //     {{0.0f, -0.5f, 0.0f}, {0.0f, -0.5f}},
  //     {{0.433f, 0.25f, 0.0f}, {0.433f, 0.25f}},
  //     {{-0.433f, 0.25f, 0.0f}, {-0.433f, 0.25f}},
  // };

  // std::vector<Mesh::uint> indices = {0, 1, 2,
  //                                    3, 4, 5};

  // Texture tex = {"assets/textures/wall.jpg"};

  // std::vector<Mesh::uint> textures = {tex.id};

  // Mesh triangle = Mesh(vertices, indices, textures);

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // triangle.draw(shader);
    spinningBananaCat.Draw(shader);

    glfwSwapBuffers(window);
    glfwPollEvents();
  } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           !glfwWindowShouldClose(window));

  glfwTerminate();
  return 0;
}
