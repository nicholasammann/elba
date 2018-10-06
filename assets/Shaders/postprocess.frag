#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform float offset;

const float offset2 = 1.0 / 300.0;  

void main(void)
{
    vec2 offsets[9] = vec2[](
        vec2(-offset2,  offset2), // top-left
        vec2( 0.0f,    offset2), // top-center
        vec2( offset2,  offset2), // top-right
        vec2(-offset2,  0.0f),   // center-left
        vec2( 0.0f,    0.0f),   // center-center
        vec2( offset2,  0.0f),   // center-right
        vec2(-offset2, -offset2), // bottom-left
        vec2( 0.0f,   -offset2), // bottom-center
        vec2( offset2, -offset2)  // bottom-right    
    );

    float sharpen[9] = float[](1, 1, 1,
                               1, -8, 1,
                               1, 1, 1);

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * sharpen[i];
    
    FragColor = vec4(col, 1.0);
    //vec2 tempTex = TexCoords;
    //tempTex.x += sin(TexCoords.y * 8 * 3.14159 + offset) / 100;
    //FragColor = vec4(vec3(1.0 - texture(screenTexture, tempTex)), 1.0);
}
