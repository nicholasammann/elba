#version 330 core
uniform sampler2D fbo_texture;
precision mediump float;
uniform float offset;
varying vec2 f_texcoord;

void main(void)
{
    vec2 texcoord = f_texcoord;
    //texcoord.x += sin(texcoord.y * 4.0 * 2.0 * 3.14159 + offset) / 100.0;
    gl_FragColor = vec4(0.0, 0.4, 0.3, 1.0);//texture2D(fbo_texture, texcoord);
}
