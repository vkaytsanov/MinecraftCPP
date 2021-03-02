//
// Created by Viktor on 16.2.2021 г..
//

#include "include/chunk.h"


Chunk::Chunk(int x, int z) : m_chunkState(Empty),
                             m_chunkMeshState(UnBuilt),
                             m_chunkMesh(),
                             m_frustumAABB(Vector3f(CHUNK_SIZE_X, CHUNK_SIZE_Y, CHUNK_SIZE_Z),
                                           Vector3f(x * CHUNK_SIZE_X, 0, z * CHUNK_SIZE_Z)){
	std::memset(&m_heightMap, 0, sizeof(m_heightMap));
}

Chunk::~Chunk() {
}

void Chunk::setCube(CubeType type, int x, int y, int z) {
	m_chunkContents.at(x).at(y).at(z).m_type = type;
}


ChunkContents* Chunk::getChunkContents() {
	return &m_chunkContents;
}

ChunkMesh* Chunk::getChunkMesh() {
	return &m_chunkMesh;
}










