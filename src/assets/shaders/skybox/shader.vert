#version 330 core

layout (location = 0) in vec3 position;

out DATA{
    vec3 position;
} vertices_out;

// Projection Matrix
uniform mat4 proj;

void main(){
    gl_Position = proj * vec4(position, 1.0);
    vertices_out.position = position;
}