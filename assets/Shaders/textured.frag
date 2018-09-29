#version 330 core
layout(location=0) out vec4 vFragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D diffuseTex;
uniform sampler2D specularTex;
uniform sampler2D normalTex;
uniform sampler2D heightTex;

void main()
{
    vFragColor = texture(diffuseTex, TexCoord);
}