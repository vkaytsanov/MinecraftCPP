//
// Created by Viktor on 16.2.2021 г..
//

#include "include/chunk.h"


Chunk::Chunk() : chunkState(Empty),
                 chunkMeshState(UnBuilt),
                 chunkMesh() {

}

Chunk::~Chunk() {
}

void Chunk::setCube(CubeType type, int x, int y, int z) {
	chunkContents.at(x).at(y).at(z).type = type;
}


ChunkContents* Chunk::getChunkContents() {
	return &chunkContents;
}

ChunkMesh* Chunk::getChunkMesh() {
	return &chunkMesh;
}










