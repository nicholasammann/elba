#version 330 core
layout(location=0) out vec4 vFragColor;

uniform struct
{
  vec4 ambient;
  vec4 diffuse;
  vec4 specular;
  vec4 emissive;
  float shininess;
} Material;

void main()
{    
    vFragColor = Material.ambient;
}