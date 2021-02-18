//
// Created by Viktor on 16.2.2021 г..
//

#include "include/chunk.h"
#include <memory>



Chunk::Chunk() : chunkMesh(){
	std::memset(&chunkData, {}, sizeof(chunkData));

	chunkMesh.constructMesh(this, {0,0});
}

void Chunk::generate() {

//	for(int i = 0; i < CHUNK_SIZE_X; i++){
//		for(int j = 0; j < CHUNK_SIZE_Y; j++){
//			for(int k = 0; k < CHUNK_SIZE_Z; k++){
//
//			}
//		}
//	}

}


ChunkData* Chunk::getChunkForMeshing() {
	return &chunkData;
}

ChunkMesh* Chunk::getChunkMesh() {
	return &chunkMesh;
}

Chunk::~Chunk() {

}


