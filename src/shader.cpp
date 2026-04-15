#include "shader.h"

#include "GL/glew.h"

Shader::Shader(Shader::uint id):
    id(id){};

Shader::~Shader() {
  glDeleteProgram(id);
}
