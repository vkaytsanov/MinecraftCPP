#version 330 core

layout (location = 0) in vec3 position;

uniform int worldPositionX;
uniform int worldPositionY;
uniform int worldPositionZ;
uniform mat4 combined;

void main(){
    gl_Position = combined * vec4(position + vec3(worldPositionX, worldPositionY, worldPositionZ), 1.0);
}