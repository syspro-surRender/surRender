#include "shader.h"

#include "GL/glew.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

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

  int success;
  char infoLog[512];

  Shader::uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vCode, NULL);
  glCompileShader(vertexShader);
  
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cerr << "Vertex shader compilation failed:\n" << infoLog << std::endl;
  }

  Shader::uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fCode, NULL);
  glCompileShader(fragmentShader);
  
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cerr << "Fragment shader compilation failed:\n" << infoLog << std::endl;
  }

  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  glLinkProgram(program);

  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, infoLog);
    std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
  }

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void Shader::use() const {
  glUseProgram(program);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}