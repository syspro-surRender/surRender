#include "engine.h"

#define STB_IMAGE_IMPLEMENTATION
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

int main() {
  std::vector<spdlog::sink_ptr> sinks;
  sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_st>());
  sinks.push_back(std::make_shared<spdlog::sinks::basic_file_sink_st>("log.txt", true));
  spdlog::set_default_logger(std::make_shared<spdlog::logger>("Base", begin(sinks), end(sinks)));
  spdlog::set_level(spdlog::level::debug);

  Engine engine = Engine();
  engine.run();

  spdlog::info("Terminating");
  glfwTerminate();
  return 0;
}
