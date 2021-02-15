#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D tex_id;

in DATA {
    vec3 position;
    vec3 normal;
    vec2 uv;
} fragments_in;

void main() {
    vec3 col = vec3(texture(tex_id, fragments_in.uv));
    color = vec4(col + 0.05, 1.0);
}