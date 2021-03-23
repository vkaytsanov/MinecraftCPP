#version 330 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 position;
layout (location = 3) in vec2 size;


out DATA{
    vec2 uv;
} vertices_out;

uniform vec3 up;
uniform vec3 right;

// Projection Matrix

uniform mat4 projView;

void main(){
    gl_Position = projView * vec4(position + right * vertices.x * size.x + up * vertices.y * size.y + vec3(0, 0, vertices.z), 1);
    vertices_out.uv = uv;
}