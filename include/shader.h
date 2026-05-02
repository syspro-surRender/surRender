#ifndef SHADER_H_
#define SHADER_H_

#include <string>
#include <glm/glm.hpp>

struct Shader {
  using uint = unsigned int;

  Shader(uint);
  Shader(const std::string vPath, const std::string fPath);

  // we don't really want to delete shader if it's just a copy, so we forbid copies altogether
  // shader objects are effectively anyway, so we pass them by reference
  Shader(const Shader&)            = delete;
  Shader& operator=(const Shader&) = delete;

  ~Shader();

  void use() const;
  void setMat4(const std::string& name, const glm::mat4& matrix) const;

  uint program;
};

#endif
