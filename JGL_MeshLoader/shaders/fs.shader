#version 330

struct DirLight
{
  vec3 position;
  vec3 color;
  float strength;
};

uniform mat4 model;

uniform DirLight dirLight;

in vec4 Color;

in vec3 WorldPos;

in vec3 Normal;

out vec4 fOutput;

void main ()  
{
  mat3 normalMatrix = transpose(inverse(mat3(model)));

  vec3 normal = normalize(normalMatrix * Normal);

  vec3 light_diff = dirLight.position - vec3(model * vec4(WorldPos, 1));

  float luminance = dot(normal, light_diff) / (length(light_diff) * length(normal));

  fOutput = vec4(luminance * dirLight.color, 1.0f) * dirLight.strength;
}