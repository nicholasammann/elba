#version 330 core
layout (location=0) in vec4 vertex;
out vec2 texCoords;

void main(void) 
{
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texCoords = (vertex.xy + 1.0) / 2.0;
}
