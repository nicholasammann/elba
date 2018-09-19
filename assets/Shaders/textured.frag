#version 330 core
layout(location=0) out vec4 vFragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    vFragColor = texture(ourTexture, TexCoord);
}