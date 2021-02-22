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

in vec3 fPos;

in vec3 fNormal;

out vec4 fOutput;


void main ()  
{
  mat3 normalMatrix = transpose(inverse(mat3(model)));

  vec3 normal = normalize(normalMatrix * fNormal);

  vec3 light_diff = dirLight.position - vec3(model * vec4(fPos, 1));

  float luminance = dot(normal, light_diff) / (length(light_diff) * length(normal));

  fOutput = vec4(luminance * dirLight.color, 1.0f) * dirLight.strength;
}