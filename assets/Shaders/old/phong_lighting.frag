#version 330 core
layout(location = 0) out vec4 vFragColor;

in vec4 litFragColor;

void main()
{
  vFragColor = litFragColor;
}