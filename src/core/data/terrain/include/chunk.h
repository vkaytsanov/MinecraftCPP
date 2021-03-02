//
// Created by Viktor on 16.2.2021 г..
//

#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include "../../../../lib/utils/geometry/include/vector2.h"
#include "../../../../lib/utils/camera/include/frustum.h"
#include "chunk_mesh.h"
#include "cube_data_base.h"
#include "biome.h"

typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;
typedef std::array<std::array<int, CHUNK_SIZE_X>, CHUNK_SIZE_Z> HeightMap;
typedef std::array<std::array<BiomeType, CHUNK_SIZE_X>, CHUNK_SIZE_Z> BiomeMap;

enum ChunkState {
	Generated,
	Empty
};

class Chunk {
private:
	ChunkContents m_chunkContents;
	ChunkMesh m_chunkMesh;
public:
	HeightMap m_heightMap;
	BiomeMap m_biomeMap;
	ChunkState m_chunkState;
	ChunkMeshState m_chunkMeshState;
	FrustumAABB m_frustumAABB;
	Chunk(int x, int z);
	~Chunk();
	void setCube(CubeType type, int x, int y, int z);
	ChunkContentsPtr getChunkContents();
	ChunkMesh* getChunkMesh();
};


#endif //CHUNK_H
