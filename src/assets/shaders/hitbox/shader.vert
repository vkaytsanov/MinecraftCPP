#version 330 core

layout (location = 0) in vec3 position;

uniform vec3 worldPosition;
uniform mat4 combined;

void main(){
    gl_Position = combined * vec4(position + worldPosition, 1.0);
}