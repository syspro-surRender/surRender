#include "engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <asm-generic/errno.h>
#include <glm/ext/quaternion_geometric.hpp>
#include <glm/ext/scalar_constants.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/common.h>
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
  spdlog::set_level(spdlog::level::info);

  Engine engine = Engine();
  engine.run();

  spdlog::info("Terminating");
  glfwTerminate();
  return 0;
}
