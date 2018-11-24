#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D lightToneTextures;
uniform sampler2D darkToneTextures;

void main(void)
{
    vec4 pixel = vec4(texture(screenTexture, TexCoords.st).xyz, 1.0);

    FragColor = pixel;
}
