#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D tex_id;
uniform vec3 fogColor;

in DATA {
    vec2 uv;
    float faceLightningLevel;
} fragments_in;


void main() {
    color = texture(tex_id, fragments_in.uv) * vec4(fragments_in.faceLightningLevel, fragments_in.faceLightningLevel, fragments_in.faceLightningLevel, 1.0f);
}