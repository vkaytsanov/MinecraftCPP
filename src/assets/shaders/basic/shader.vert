#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;



out vec3 fragmentColor;
// Projection Matrix
uniform mat4 proj;

void main(){
    gl_Position = proj * vec4(vertexPosition, 1);
    fragmentColor = vertexColor;
}