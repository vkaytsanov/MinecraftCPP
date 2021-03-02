//
// Created by Viktor on 1.3.2021 г..
//

#ifndef BIOME_H
#define BIOME_H

#include "../../prefabs/include/prefab.h"

enum BiomeType{
	Plains,
	Desert,
	Forest,
	Mountains,
	Ocean,
};

class Biome {
public:
	int m_minHeight;
	int m_heightVariety;
	// the first and last blocks define the biome
	std::vector<CubeType> m_cubes;
	std::vector<std::pair<CubeType, int>> m_models;
	std::vector<std::pair<Prefab, int>> m_prefabs;
};

BiomeType getBiomeType(float temperature, float humidity);

#endif //BIOME_H
