#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 color;

out vec3 WorldPos;
out vec3 Normal;
out vec4 Color;

void main()
{
  Color = color;
  WorldPos = vec3(model * vec4(aPosition, 1.0));
  Normal = aNormal;

  gl_Position = projection * view * model * vec4(aPosition, 1.0f);

}