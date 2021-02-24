//
// Created by Viktor on 23.2.2021 г..
//

#include <iostream>
#include "include/world_generation.h"

WorldGeneration::WorldGeneration() {
	perlinNoise.SetFrequency(0.005);
	perlinNoise.SetPersistence(0.025);
}

WorldGeneration::WorldGeneration(int seed) {
	perlinNoise.SetSeed(seed);
	perlinNoise.SetFrequency(0.005);
	perlinNoise.SetPersistence(0.025);
}

void WorldGeneration::generateChunkContents(Chunk* chunk, int16_t x, int16_t z) {
	for (int i = 0; i < CHUNK_SIZE_X; i++) {
		for (int j = 0; j < CHUNK_SIZE_Z; j++) {
			float worldX = (float)(i + x * CHUNK_SIZE_X);
			float worldZ = (float)(j + z * CHUNK_SIZE_Z);

			int height = (int) (std::round(((perlinNoise.GetValue(worldX / 2.0f, worldZ / 2.0f, 0.8) + 1.0f) / 2) * 200));
			//std::cout << "Height: " << height << "\n";
			chunk->heightMap[i][j] = height;
			generateVerticalLevel(chunk, i, height, j);
		}
	}
	chunk->chunkState = Generated;
}

void WorldGeneration::generateVerticalLevel(Chunk* chunk, int x, int level, int z) {
	chunk->setCube(Bedrock, x, 0, z);
	for (int y = 1; y < level - 5; y++) chunk->setCube(Stone, x, y, z);
	for (int y = level - 5; y < level - 1; y++) chunk->setCube(Dirt, x, y, z);
	chunk->setCube(Grass, x, level - 1, z);


}



