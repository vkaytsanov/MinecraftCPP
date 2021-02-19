//
// Created by Viktor on 16.2.2021 г..
//

#ifndef CHUNK_H
#define CHUNK_H

#include <array>
#include "../../../lib/utils/geometry/include/vector2.h"
#include "chunk_mesh.h"
#include "cube_data_base.h"

#define CHUNK_SIZE_X 16
#define CHUNK_SIZE_Y 3
#define CHUNK_SIZE_Z 16

using namespace CubeDatabase;

typedef std::array<std::array<std::array<Cube, CHUNK_SIZE_X>, CHUNK_SIZE_Y>, CHUNK_SIZE_Z> ChunkData;

class Chunk {
private:
	ChunkMesh chunkMesh;
	Vector2i position;
public:
	ChunkData chunkData;
	Chunk();
	~Chunk();
	void generate();
	ChunkData* getChunkForMeshing();
	ChunkMesh* getChunkMesh();
};


#endif //CHUNK_H
