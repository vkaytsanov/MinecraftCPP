//
// Created by Viktor on 23.2.2021 г..
//

#ifndef WORLD_GENERATION_H
#define WORLD_GENERATION_H


#include "../../../lib/utils/noise/noise.h"
#include "../../data/include/chunk.h"

class WorldGeneration {
private:
	noise::module::Perlin m_perlinNoise;
	int waterMinLevel = 2;
	int waterMaxLevel = 110;
	void generateVerticalLevel(Chunk* chunk, int x, int level, int z);
	void generateWaterHorizontalLevel(Chunk* chunk);
public:
	WorldGeneration(int seed);
	WorldGeneration();
	void generateChunkContents(Chunk* chunk, int16_t x, int16_t z);
};


#endif //WORLD_GENERATION_H
