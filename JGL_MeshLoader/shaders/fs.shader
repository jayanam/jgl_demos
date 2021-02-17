#version 330

in vec4 colorV;

out vec4 outputF;

struct DirLight
{
  vec3 color;
  float strength;
};

uniform DirLight dirLight;

void main ()  
{  
  vec4 lightColor = vec4(dirLight.color, 1.0f) * dirLight.strength;

  outputF = colorV * lightColor;
}