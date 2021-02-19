#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

out vec3 FragPos;
out vec3 FragNormal;
out vec4 colorV;

void main()
{
  colorV = color;
  gl_Position = projection * view * model * vec4(position, 1.0f);
  FragPos = vec3(model * vec4(position, 1.0));
  FragNormal = normal;
}