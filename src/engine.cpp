#include "engine.h"

#include "display_manager.h"
#include "input_manager.h"
#include "render_manager.h"
#include "scene_manager.h"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

Engine::Engine():
    displayManager(), sceneManager(), renderManager(displayManager, sceneManager), inputManager(displayManager, sceneManager) {}

Engine::~Engine() {
  spdlog::debug("Engine destructor was called");
}

void Engine::run() {
  GLFWwindow* window = displayManager.window;
  if (!window) {
    return;
  }

  bool done = false;
  // auto lastTime = std::chrono::high_resolution_clock::now();

  while (!done) {
    // auto currentTime = std::chrono::high_resolution_clock::now();
    // float deltaTime  = std::chrono::duration<float>(currentTime - lastTime).count();
    // lastTime         = currentTime;

    inputManager.processInput(done);
    sceneManager.update(1u);

    renderManager.draw();

    displayManager.swapBuffers();
  }
}
