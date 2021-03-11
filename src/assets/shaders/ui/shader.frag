#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D u_FontTexture;

in DATA {
    vec2 position;
} fragments_in;

void main() {
    color = texture(u_FontTexture, fragments_in.position);

}