//
// Created by Viktor on 16.2.2021 г..
//

#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include "../../../lib/utils/geometry/include/vector2.h"
#include "chunk_mesh.h"
#include "cube_data_base.h"

typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkContents;
typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z>* ChunkContentsPtr;
typedef std::array<std::array<int, CHUNK_SIZE_X>, CHUNK_SIZE_Z> HeightMap;

enum ChunkState {
	Generated,
	Empty
};

class Chunk {
private:
	ChunkContents chunkContents;
	ChunkMesh chunkMesh;
public:
	HeightMap heightMap;
	ChunkState chunkState;
	ChunkMeshState chunkMeshState;
	Chunk();
	~Chunk();
	void setCube(CubeType type, int x, int y, int z);
	ChunkContentsPtr getChunkContents();
	ChunkMesh* getChunkMesh();
};


#endif //CHUNK_H
