
#include "include/chunk.h"

Chunk::Chunk() : m_chunkState(Empty){
	std::memset(&m_heightMap, 0, sizeof(m_heightMap));
	m_chunkContents = new std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>();
}

Chunk::~Chunk() {
	delete m_chunkContents;
}

void Chunk::setCube(CubeType type, int x, int y, int z) {
	m_chunkContents->at(x).at(y).at(z).m_type = type;
}

ChunkContentsPtr Chunk::getChunkContents() const {
	return m_chunkContents;
}

HeightMap* Chunk::getHeightMap() {
	return &m_heightMap;
}

BiomeMap* Chunk::getBiomeMap() {
	return &m_biomeMap;
}

void Chunk::setHeight(int height, int x, int z) {
	m_heightMap[x][z] = height;
}




