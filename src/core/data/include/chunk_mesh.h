//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H


#include <vector>
#include "../../../lib/utils/openGL/include/vertex.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/index_buffer.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "cube_data_base.h"
#include "cube.h"

class Chunk;

static float planes[6 * 4 * 3] = {
		// Front
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		// Back
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		// Top
		0.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		// Bottom
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		// Left
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 1.0f,
		// Right
		1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

};

class ChunkMesh {
private:
	VertexBuffer vertexBuffer;
	std::vector<Vertex> vertices;
	void addFace(CubeType type, CubeFaceType face, Vector3f position);

public:
	VertexArray vertexArray;
	unsigned int verticesCount = 0;
	ChunkMesh();
	~ChunkMesh();
	void constructMesh(Chunk* chunk, Vector2i chunkPosition);


};


#endif //CHUNK_MESH_H
