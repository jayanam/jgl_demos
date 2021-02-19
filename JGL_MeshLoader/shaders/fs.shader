#version 330

uniform mat4 model;

in vec4 colorV;

struct DirLight
{
  vec3 position;
  vec3 color;
  float strength;
};

uniform DirLight dirLight;

in vec3 FragPos;

in vec3 FragNormal;

out vec4 FragOutput;


void main ()  
{
  mat3 normalMatrix = transpose(inverse(mat3(model)));

  vec3 normal = normalize(normalMatrix * FragNormal);

  vec3 light_diff = dirLight.position - vec3(model * vec4(FragPos, 1));

  float luminance = dot(normal, light_diff) / (length(light_diff) * length(normal));

  FragOutput = vec4(luminance * dirLight.color, 1.0f) * dirLight.strength;
}