#include "shader.h"

#include "GL/glew.h"

#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(Shader::uint id):
    program(id){};

Shader::~Shader() {
  glDeleteProgram(program);
}

Shader::Shader(const std::string vPath, const std::string fPath) {
  std::string fCodeString, vCodeString;
  {
    std::ifstream vShaderFile(vPath), fShaderFile(fPath);

    if (!vShaderFile.good()) {
      throw std::runtime_error("Couldn't find vertex shader file at " + vPath);
    }
    if (!fShaderFile.good()) {
      throw std::runtime_error("Couldn't find fragment shader file at " + fPath);
    }

    std::stringstream vCodeStream, fCodeStream;
    vCodeStream << vShaderFile.rdbuf();
    fCodeStream << fShaderFile.rdbuf();

    vCodeString = vCodeStream.str();
    fCodeString = fCodeStream.str();
  }

  const char* vCode = vCodeString.c_str();
  const char* fCode = fCodeString.c_str();

  int status;

  Shader::uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vCode, NULL);
  glCompileShader(vertexShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    int length;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
    char* buf = new char[length]();
    glGetShaderInfoLog(vertexShader, length, &status, buf);
    spdlog::error("Failed to compile vertex shader {}\n Shader log: {}", vPath, buf);
  }


  Shader::uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fCode, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
  if (!status) {
    int length;
    glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
    char* buf = new char[length]();
    glGetShaderInfoLog(vertexShader, length, &status, buf);
    spdlog::error("Failed to compile fragment shader {}\n Shader log: {}", vPath, buf);
  }

  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() const {
  glUseProgram(program);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}
