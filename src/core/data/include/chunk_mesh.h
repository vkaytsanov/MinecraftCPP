//
// Created by Viktor on 17.2.2021 г..
//

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H


#include <vector>
#include <array>
#include "../../../lib/utils/openGL/include/vertex.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/index_buffer.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "cube_data_base.h"
#include "cube.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

enum ChunkMeshState {
	Built,
	UnBuilt
};

class ChunkMesh {
private:
	std::array<VertexArray, 2> vao;
	std::array<VertexBuffer, 2> vbo;
	std::array<unsigned int, 2> indicesCount;
public:
	ChunkMesh();
	~ChunkMesh();
	void setMesh(std::array<std::vector<Vertex>, 2>& vertices);
	VertexArray* getVao();
	VertexArray* getTransparentVao();
	unsigned int getIndicesCount();
	unsigned int getTransparentIndicesCount();


};


#endif //CHUNK_MESH_H
