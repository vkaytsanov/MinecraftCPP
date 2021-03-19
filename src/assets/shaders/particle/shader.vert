#version 330 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 aOffset;


out DATA{
    vec3 color;
} vertices_out;

// Projection Matrix
uniform mat4 proj;

void main(){
//    gl_Position = proj * vec4(position, 1.0);
//    vertices_out.color = color;
    gl_Position = proj * vec4(position + aOffset, 1.0, 1.0);
    vertices_out.color = color;
}