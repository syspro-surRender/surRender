#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 projection;
uniform mat4 view;

out vec3 TexCoord;

void main() {
  vec3 scaledPosition = aPos * 1000.0
  TexCoord    = scaledPosition;
  gl_Position = projection * mat4(mat3(view)) * vec4(scaledPosition, 1.0)
}
