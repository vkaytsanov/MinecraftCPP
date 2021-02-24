#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out DATA{
    vec3 position;
    vec3 normal;
    vec2 uv;
} vertices_out;

// Projection Matrix
uniform mat4 proj;

uniform int CHUNK_SIZE_X;
uniform int CHUNK_SIZE_Z;
uniform int chunkX;
uniform int chunkZ;


void main(){
    vec3 world_position = vec3(position.x + chunkX * CHUNK_SIZE_X, position.y, position.z + chunkZ * CHUNK_SIZE_Z);
    gl_Position = proj * vec4(world_position, 1.0);
    vertices_out.position = vec3(proj * vec4(world_position, 1.0));
    vertices_out.normal = normal;
    vertices_out.uv = uv;
}