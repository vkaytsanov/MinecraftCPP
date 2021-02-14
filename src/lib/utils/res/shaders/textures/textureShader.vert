#version 330 core

layout(location = 0) in vec3 vertexPosition;
//layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;


//out vec3 fragmentColor;
out vec2 UV;
// Projection Matrix
uniform mat4 proj;

void main(){
    gl_Position = proj * vec4(vertexPosition, 1);
//    fragmentColor = vertexColor;
    UV = vertexUV;
}