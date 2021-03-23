#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D tex_id;


in DATA{
    vec2 uv;
} fragments_in;

void main() {
    color = texture(tex_id, fragments_in.uv);
    color.a = min(color.w, 0.75f);
}