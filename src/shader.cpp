#include "shader.h"

#include "GL/glew.h"

#include <fstream>
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


  Shader::uint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vCode, NULL);
  glCompileShader(vertexShader);
  //todo error handling


  Shader::uint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fCode, NULL);
  glCompileShader(fragmentShader);
  //todo error handling

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
