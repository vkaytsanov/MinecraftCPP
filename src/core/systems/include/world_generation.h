//
// Created by Viktor on 23.2.2021 г..
//

#ifndef WORLD_GENERATION_H
#define WORLD_GENERATION_H


#include <array>
#include "../../../lib/utils/noise/noise.h"
#include "../../data/terrain/include/biome.h"
#include "../../../lib/utils/include/random_generator.h"
#include "../../components/include/chunk.h"

class WorldGeneration {
private:
	noise::module::Perlin m_heightGenerator;
	noise::module::Perlin m_temperatureGenerator;
	noise::module::Perlin m_humidityGenerator;
	RandomGenerator m_randomGenerator;
	const int WATER_MIN_LEVEL = 2;
	const int WATER_MAX_LEVEL = 63;
	std::array<Biome, 5> m_biomes;
	void generateBiomeMap(Chunk* chunk, int16_t wPosX, int16_t wPosZ);
	static void generateVerticalLevel(Chunk* chunk, Biome* biome, int x, int level, int z);
	void generateWater(Chunk* chunk) const;
	void generateModels(Chunk* chunk);
	void generatePrefabs(Chunk* chunk);
public:
	WorldGeneration(int seed);
	WorldGeneration();
	void generateChunkContents(Chunk* chunk, int16_t i, int16_t j);
};


#endif //WORLD_GENERATION_H
