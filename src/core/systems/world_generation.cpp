//
// Created by Viktor on 23.2.2021 г..
//

#include <iostream>
#include "include/world_generation.h"
#include "../data/prefabs/include/tree_prefab.h"
#include "../data/terrain/biomes/include/plains_biome.h"
#include "../data/terrain/biomes/include/desert_biome.h"
#include "../data/terrain/biomes/include/forest_biome.h"
#include "../data/terrain/biomes/include/mountains_biome.h"
#include "../data/terrain/biomes/include/ocean_biome.h"

WorldGeneration::WorldGeneration() : WorldGeneration(1337) {
}

WorldGeneration::WorldGeneration(int seed) {
	m_biomes[Plains] = PlainsBiome();
	m_biomes[Desert] = DesertBiome();
	m_biomes[Forest] = ForestBiome();
	m_biomes[Mountains] = MountainsBiome();
	m_biomes[Ocean] = OceanBiome();

	m_heightGenerator.SetSeed(seed);
	m_heightGenerator.SetFrequency(0.005);

	m_temperatureGenerator.SetSeed(seed + 1);
	m_temperatureGenerator.SetFrequency(0.002);

	m_humidityGenerator.SetSeed(seed + 2);
	m_humidityGenerator.SetFrequency(0.002);
}

void WorldGeneration::generateChunkContents(Chunk* chunk, int16_t i, int16_t j) {
	const int chunkWorldPositionX = i * CHUNK_SIZE_X;
	const int chunkWorldPositionZ = j * CHUNK_SIZE_Z;

	generateBiomeMap(chunk, chunkWorldPositionX, chunkWorldPositionZ);

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int z = 0; z < CHUNK_SIZE_Z; z++) {
			float worldX = (float) (x + i * CHUNK_SIZE_X);
			float worldZ = (float) (z + j * CHUNK_SIZE_Z);

			Biome& biome = m_biomes[chunk->getBiomeMap()->at(x).at(z)];
			int height = (int) std::round((m_heightGenerator.GetValuePositive(worldX, worldZ, 0.8) * 64) +
					biome.m_minHeight);
//			std::cout << "Height: " << height << "\n";
			chunk->setHeight(height, x, z);
			generateVerticalLevel(chunk, &biome, x, height, z);
		}
	}
	generateWater(chunk);
	generatePrefabs(chunk);
	generateModels(chunk);
	chunk->m_chunkState = Generated;
}

void WorldGeneration::generateVerticalLevel(Chunk* chunk, Biome* biome, int x, int level, int z) {
	assert(level > 10);
	chunk->setCube(Bedrock, x, 0, z);
	for (int y = 1; y < level - 5; y++) chunk->setCube(Stone, x, y, z);
	for (int y = level - 5; y < level - 1; y++) chunk->setCube(biome->m_cubes[0], x, y, z);
	chunk->setCube(biome->m_cubes[biome->m_cubes.size() - 1], x, level - 1, z);
}

void WorldGeneration::generateWater(Chunk* chunk) const {
	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = chunk->getHeightMap();

	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int z = 0; z < CHUNK_SIZE_Z; z++) {
			int y = heightMap->at(x).at(z) - 1;

			for (; y < WATER_MAX_LEVEL; y++) {
				Cube* cube = &chunkData->at(x).at(y).at(z);
				if (cube->m_type == Air) {
					cube->m_type = Water;
					heightMap->at(x).at(z)++;
				}
//					// sand under the water
//				else if (cube->isOpaque()) {
//					cube->m_type = Sand;
//				}
			}
//			// replacing blocks for sand around the water
//			for (y = WATER_MAX_LEVEL - 2; y < WATER_MAX_LEVEL + 4; y++) {
//				Cube* cube = &chunkData->at(x).at(y).at(z);
//				if (cube->isOpaque()) {
//					cube->m_type = Sand;
//				}
//			}
		}

	}
}

void WorldGeneration::generatePrefabs(Chunk* chunk) {
	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = chunk->getHeightMap();
	BiomeMap* biomeMap = chunk->getBiomeMap();
	for (int x = 1; x < CHUNK_SIZE_X - 1; x++) {
		for (int z = 1; z < CHUNK_SIZE_Z - 1; z++) {
			int y = heightMap->at(x).at(z);

			Cube* cube = &chunkData->at(x).at(y).at(z);
			if (cube->m_type == Air) {
				if (chunkData->at(x).at(y - 1).at(z).isOpaque()) {

					for (auto& prefab : m_biomes[biomeMap->at(x).at(z)].m_prefabs) {
						int freq = m_randomGenerator.getRandom(prefab.second);
						if (freq == 0) {
							for (auto prefabCube : prefab.first.getStructure()) {
								Vector3i pos = prefabCube.unpackPositionAt(x, y, z);
								if (pos.x >= 0 && pos.x < CHUNK_SIZE_X &&
								    pos.y >= 0 && pos.y < CHUNK_SIZE_Y &&
								    pos.z >= 0 && pos.z < CHUNK_SIZE_Z) {
									chunkData->at(pos.x).at(pos.y).at(pos.z).m_type = prefabCube.m_type;
									heightMap->at(pos.x).at(pos.z) = std::max(heightMap->at(pos.x).at(pos.z),
									                                          pos.y + 1);
								}
							}
						}
					}
				}
//				m_chunk->m_heightMap.at(x).at(z)++;
			}


		}
	}
}

void WorldGeneration::generateModels(Chunk* chunk) {
	ChunkContentsPtr chunkData = chunk->getChunkContents();
	HeightMap* heightMap = chunk->getHeightMap();
	BiomeMap* biomeMap = chunk->getBiomeMap();
	for (int x = 1; x < CHUNK_SIZE_X - 1; x++) {
		for (int z = 1; z < CHUNK_SIZE_Z - 1; z++) {
			int y = heightMap->at(x).at(z);

			Cube* cube = &chunkData->at(x).at(y).at(z);
			if (cube->m_type == Air) {
				if (chunkData->at(x).at(y - 1).at(z).isOpaque()) {
					for (auto& model : m_biomes[biomeMap->at(x).at(z)].m_models) {
						int freq = m_randomGenerator.getRandom(model.second);
						if (freq == 0) {
							cube->m_type = model.first;
							heightMap->at(x).at(z)++;
							break;
						}
					}
				}
			}
		}
	}

}

void WorldGeneration::generateBiomeMap(Chunk* chunk, int16_t wPosX, int16_t wPosZ) {
	BiomeMap* biomeMap = chunk->getBiomeMap();
	for (int x = 0; x < CHUNK_SIZE_X; x++) {
		for (int z = 0; z < CHUNK_SIZE_Z; z++) {
			int globalPosX = x + wPosX;
			int globalPosY = z + wPosZ;
			const float chunkTemperature = m_temperatureGenerator.GetValue(globalPosX, globalPosY, 0.8f);
			const float chunkHumidity = m_humidityGenerator.GetValue(globalPosX, globalPosY, 0.8f);

			biomeMap->at(x).at(z) = getBiomeType(chunkTemperature, chunkHumidity);

		}
	}
}



