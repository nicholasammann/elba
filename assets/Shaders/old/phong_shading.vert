#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 oObjPos;
out vec3 oObjNorm;

out vec4 oViewPos;
out vec4 oViewNorm;

void main()
{
  oObjPos = aPos;
  oObjNorm = aNormal;

  // calculate position and normal in view space
  vec4 vPos = view * model * vec4(aPos, 1);

  oViewPos = vPos;
  oViewNorm = normalize(view * model * vec4(aNormal, 0));

  // final world coordinates
  gl_Position = projection * view * model * vec4(aPos, 1);
}