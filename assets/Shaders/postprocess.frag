#version 330 core
in vec2 texCoords;
out vec4 color;

uniform sampler2D fbo_texture;
uniform float offset;

void main(void)
{
    vec2 tempCoords = texCoords;
    tempCoords.x += sin(texCoords.y * 4.0 * 2.0 * 3.14159 + offset) / 100.0;
    color = texture2D(fbo_texture, tempCoords);
}
