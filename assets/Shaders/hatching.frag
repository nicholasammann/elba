#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D lightToneTextures;
uniform sampler2D darkToneTextures;

void main(void)
{
  float col = texture(lightToneTextures, TexCoords.st).z;
  vec4 pixel = vec4(col, col, col, 1.0);
  FragColor = pixel;
}
