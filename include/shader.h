#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Shader {
  using uint = unsigned int;

  Shader(uint);
  Shader(const std::string vPath, const std::string fPath);

  Shader(const Shader&) = delete;
  Shader& operator=(const Shader&) = delete;

  ~Shader();

  void use() const;
  void setVec3(const std::string& name, const glm::vec3& vector) const;
  void setMat4(const std::string& name, const glm::mat4& matrix) const;

  uint program;
};

#endif