//
// Created by Viktor on 16.2.2021 г..
//

#include "include/chunk.h"

Chunk::Chunk() {

}

void Chunk::generate() {
	for(int i = 0; i < CHUNK_SIZE_X; i++){
		for(int j = 0; j < CHUNK_SIZE_Y; j++){
			for(int k = 0; k < CHUNK_SIZE_Z; k++){
				cubes[i][j][k] = Grass;
			}
		}
	}
}

CubeType Chunk::getCube(int x, int y, int z) {
	return cubes[x][y][z];
}


