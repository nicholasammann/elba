#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aNorm;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoords;
out vec3 pos;
out vec3 norm;

void main(void)
{
  pos = aPos;
  norm = aNorm;
  TexCoords = aTexCoords;
  gl_Position = projection * view * model * vec4(aPos, 1.0);
}
