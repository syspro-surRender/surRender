#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;

void main() {
  FragColor = texture(ourTexture, TexCoord);
  // FragColor = vec4(TexCoord, 0, 0);
  // FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
};
