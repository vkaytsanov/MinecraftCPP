//
// Created by Viktor on 17.2.2021 г..
//

#include "include/chunk_mesh.h"
#include "include/chunk.h"
#include "../../lib/include/lib.h"
#include "include/cube.h"


ChunkMesh::ChunkMesh() {
	const unsigned int indicesCount = CHUNK_SIZE_X * CHUNK_SIZE_Y * CHUNK_SIZE_Z * 6;
	unsigned int indicesOffset = 0;
	IndexBuffer indexBuffer;

	GLuint buffer[indicesCount * 6];

	for (int i = 0; i < indicesCount; i += 6) {
		buffer[i + 0] = 0 + indicesOffset;
		buffer[i + 1] = 1 + indicesOffset;
		buffer[i + 2] = 2 + indicesOffset;
		buffer[i + 3] = 2 + indicesOffset;
		buffer[i + 4] = 3 + indicesOffset;
		buffer[i + 5] = 0 + indicesOffset;
		indicesOffset += 4;
	}
	indexBuffer.bind();
	indexBuffer.bufferData(indicesCount * 6 * sizeof(GLuint), buffer, GL_STATIC_DRAW);
	Lib::app->log("IndicesCount", indicesCount);

	vertexArray.bind();
	vertexBuffer.bind();
	indexBuffer.bind();

	vertexBuffer.vertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                                 reinterpret_cast<void*>(offsetof(Vertex, position)));
	vertexBuffer.vertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                                 reinterpret_cast<void*>(offsetof(Vertex, normals)));
	vertexBuffer.vertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
	                                 reinterpret_cast<void*>(offsetof(Vertex, uvs)));

	vertexArray.unbind();


}

ChunkMesh::~ChunkMesh() {

}

void ChunkMesh::constructMesh(Chunk* chunk, Vector2i chunkPosition) {

	vertices.clear();
	ChunkData* chunkData = &chunk->chunkData;

	Vector3f cubePosition;

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int y = 0; y < CHUNK_SIZE_Y; y++) {
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {
				Cube* cube = &chunkData->at(x).at(y).at(z);
				if (cube->type != CubeType::Air) {
					cubePosition.set(x, y, z);

					if(z == 0) addFace(cube->type, Back, cubePosition);
					else if(z == CHUNK_SIZE_Z - 1) addFace(cube->type, Front, cubePosition);
					else if(chunkData->at(x).at(y).at(z - 1).isTransparent()) addFace(cube->type, Back, cubePosition);
					else if(chunkData->at(x).at(y).at(z + 1).isTransparent()) addFace(cube->type, Front, cubePosition);

					if(y == 0) addFace(cube->type, Bottom, cubePosition);
					else if(y == CHUNK_SIZE_Y - 1) addFace(cube->type, Top, cubePosition);
					else if(chunkData->at(x).at(y - 1).at(z).isTransparent()) addFace(cube->type, Bottom, cubePosition);
					else if(chunkData->at(x).at(y + 1).at(z).isTransparent()) addFace(cube->type, Top, cubePosition);

					if(x == 0) addFace(cube->type, Left, cubePosition);
					else if(x == CHUNK_SIZE_X - 1) addFace(cube->type, Right, cubePosition);
					else if(chunkData->at(x - 1).at(y).at(z).isTransparent()) addFace(cube->type, Left, cubePosition);
					else if(chunkData->at(x + 1).at(y).at(z).isTransparent()) addFace(cube->type, Right, cubePosition);



				}
			}
		}
	}


	if (!vertices.empty()) {
		vertexBuffer.bufferData(vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);
		verticesCount = vertices.size();
		vertices.clear();
	}
	Lib::app->log("VerticesCount", verticesCount);


}

void ChunkMesh::addFace(CubeType type, CubeFaceType face, Vector3f position) {
	Vertex currVertex;
	float* uvs = CubeDatabase::getUVs(type);

	int normalsOffset = 4 * 3 * face;
	int uvsOffset = 4 * 2 * face;
	for (int i = 0; i < 4; i++) {
		currVertex.position = position + Vector3f(planes[normalsOffset + i],
		                                          planes[normalsOffset + i + 1],
		                                          planes[normalsOffset + i + 2]);
		currVertex.normals = Vector3f(normals[normalsOffset + i],
		                              normals[normalsOffset + i + 1],
		                              normals[normalsOffset + i + 2]);
		currVertex.uvs = Vector2f(uvs[uvsOffset + i],
		                          uvs[uvsOffset + i + 1]);
		normalsOffset += 2;
		uvsOffset += 1;
		vertices.emplace_back(currVertex);
	}

}
