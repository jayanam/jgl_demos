#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

out vec3 fPos;
out vec3 fNormal;
out vec4 vColor;

void main()
{
  vColor = color;
  fPos = vec3(model * vec4(position, 1.0));
  fNormal = normal;

  gl_Position = projection * view * model * vec4(position, 1.0f);

}