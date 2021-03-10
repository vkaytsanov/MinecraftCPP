//
// Created by Viktor on 5.3.2021 г..
//

#ifndef CHUNK_MESH_H
#define CHUNK_MESH_H

#include <array>
#include <vector>

#include "../../../lib/utils/openGL/include/vertex.h"
#include "../../../lib/utils/openGL/include/vertex_array.h"
#include "../../../lib/utils/openGL/include/index_buffer.h"
#include "../../../lib/utils/openGL/include/vertex_buffer.h"
#include "../../../lib/entityx/entityx.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 256
#define CHUNK_SIZE_Z 16

enum ChunkMeshState {
	Built,
	UnBuilt
};

class ChunkMesh : public entityx::Component<ChunkMesh>{
private:
	std::array<VertexArray, 3> m_vao;
	std::array<VertexBuffer, 3> m_vbo;
	std::array<unsigned int, 3> m_indicesCount;
public:
	ChunkMesh();
	ChunkMeshState m_chunkMeshState;
	void setMesh(std::array<std::vector<Vertex>, 3>& vertices);
	VertexArray* getVao();
	VertexArray* getTransparentVao();
	VertexArray* getModelVao();
	unsigned int getIndicesCount();
	unsigned int getTransparentIndicesCount();
	unsigned int getModelIndicesCount();
};


#endif //CHUNK_MESH_H
