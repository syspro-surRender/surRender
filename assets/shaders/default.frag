#version 460 core

#define AMBIENT 0.03
#define MAX_LIGHTS 10

struct Light {
  vec3 pos;
  vec3 color;
  float intensity;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D ourTexture;
uniform Light ourLights[MAX_LIGHTS];
uniform int ourLightsN;

out vec4 FragColor;

void main() {
  vec3 normal = normalize(Normal);
  vec3 result = vec3(AMBIENT);
  ;

  for (int i = 0; i < ourLightsN; i++) {
    vec3 lightDir = normalize(ourLights[i].pos - FragPos);
    result += max(dot(normal, lightDir), 0.0) * ourLights[i].color * (ourLights[i].intensity / length(ourLights[i].pos - FragPos));
  }

  vec4 texColor = texture(ourTexture, TexCoord);

  FragColor = vec4(texColor.rgb * result, texColor.a);
  // FragColor = vec4(TexCoord, 0, 0);
  // FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
  // FragColor = vec4(Normal, 1.0);
}
