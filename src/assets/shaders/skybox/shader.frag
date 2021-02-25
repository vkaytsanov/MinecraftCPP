#version 330 core

layout (location = 0) out vec4 color;

uniform samplerCube texSkybox;

in DATA {
    vec3 position;
} fragments_in;

void main() {
    color = texture(texSkybox, fragments_in.position);

}