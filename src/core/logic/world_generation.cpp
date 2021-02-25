//
// Created by Viktor on 23.2.2021 г..
//

#include <iostream>
#include "include/world_generation.h"

WorldGeneration::WorldGeneration() {
	m_perlinNoise.SetFrequency(0.005);
}

WorldGeneration::WorldGeneration(int seed) {
	m_perlinNoise.SetSeed(seed);
	m_perlinNoise.SetFrequency(0.005);
	m_perlinNoise.SetPersistence(0.025);
}

void WorldGeneration::generateChunkContents(Chunk* chunk, int16_t x, int16_t z) {
	for (int i = 0; i < CHUNK_SIZE_X; i++) {
		for (int j = 0; j < CHUNK_SIZE_Z; j++) {
			float worldX = (float) (i + x * CHUNK_SIZE_X);
			float worldZ = (float) (j + z * CHUNK_SIZE_Z);

			int height = (int) (std::round(
					((m_perlinNoise.GetValue(worldX / 2.0f, worldZ / 2.0f, 0.8) + 1.0f) / 2) * 200));
			//std::cout << "Height: " << height << "\n";
			chunk->heightMap[i][j] = height;
			generateVerticalLevel(chunk, i, height, j);
		}
	}
	generateWaterHorizontalLevel(chunk);
	chunk->chunkState = Generated;
}

void WorldGeneration::generateVerticalLevel(Chunk* chunk, int x, int level, int z) {
	chunk->setCube(Bedrock, x, 0, z);
	for (int y = 1; y < level - 5; y++) chunk->setCube(Stone, x, y, z);
	for (int y = level - 5; y < level - 1; y++) chunk->setCube(Dirt, x, y, z);
	chunk->setCube(Grass, x, level - 1, z);


}

void WorldGeneration::generateWaterHorizontalLevel(Chunk* chunk) {
	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = &chunk->heightMap;

	for(int x = 0; x < CHUNK_SIZE_X; x++){
			for (int z = 0; z < CHUNK_SIZE_Z; z++) {
				for(int y = heightMap->at(x).at(z) - 1; y < waterMaxLevel; y++) {
					Cube* cube = &chunkData->at(x).at(y).at(z);
					if (cube->type == Air) {
						chunkData->at(x).at(y).at(z).type = Water;
						heightMap->at(x).at(z)++;
					}
					// sand under the water
					else if(!cube->isTransparent()){
						chunkData->at(x).at(y).at(z).type = Sand;
					}
				}
				// sand around the water
				for(int y = waterMaxLevel - 2; y < waterMaxLevel + 4; y++){
					Cube* cube = &chunkData->at(x).at(y).at(z);
					if (!cube->isTransparent()) {
						chunkData->at(x).at(y).at(z).type = Sand;
						heightMap->at(x).at(z)++;
					}
				}
			}

	}
}



