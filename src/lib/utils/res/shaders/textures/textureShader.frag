#version 330 core

#ifdef GL_ES
precision mediump float;
#endif

//in vec3 fragmentColor;
in vec2 UV;
out vec3 color;

uniform sampler2D myTextureSampler;


void main() {
//    color = vec4(fragmentColor, 1);
    color = texture(myTextureSampler, UV).rgb;
}