#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

uniform int doNegative;
uniform int doLog;
uniform int doGamma;
uniform float c;
uniform float gamma;
uniform int doSobel;

void main(void)
{
    vec4 pixel = vec4(texture(screenTexture, TexCoords.st).xyz, 1.0);

    if (doNegative != 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            pixel[i] = 1 - pixel[i];
        }
    }
    else if (doLog != 0)
    {
        for (int i = 0; i < 3; ++i)
        {
            pixel[i] = c * log(1 + pixel[i]);
        }
    }
    else if (doGamma != 0)
    {
        pixel.rgb = c * pow(pixel.rgb, vec3(1.0/gamma));
    }

    FragColor = pixel;
}
