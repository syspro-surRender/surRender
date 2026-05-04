#version 460 core
in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform vec3      ourLightPos;

out vec4 FragColor;

void main() {
  vec3 normal = normalize(Normal);
  vec3 lightDir = normalize(ourLightPos - FragPos);

  float brightness = max(dot(lightDir, normal), 0.0) + 0.15;
  vec4 texColor    = texture(ourTexture, TexCoord);

  FragColor     = vec4(texColor.rgb * brightness, texColor.a);
  // FragColor  = vec4(TexCoord, 0, 0);
  // FragColor  = vec4(vec3(gl_FragCoord.z), 1.0);

  // FragColor = vec4(Normal, 1.0);
};
