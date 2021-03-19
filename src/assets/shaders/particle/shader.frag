#version 330 core

layout (location = 0) out vec4 color;

//uniform sampler2D tex_id;

//in DATA {
//    vec2 uvs;
//} fragments_in;

in DATA{
    vec3 color;
} fragments_in;

void main() {
//    color = texture(tex_id, fragments_in.uv);
    color = vec4(fragments_in.color, 1.0f);
}