//
// Created by Viktor on 1.3.2021 г..
//

#include "include/desert_biome.h"
#include "../../prefabs/include/cactus_prefab.h"

DesertBiome::DesertBiome() {
	m_minHeight = 61;
	m_heightVariety = 6;
	m_cubes.emplace_back(Sandstone);
	m_cubes.emplace_back(Sand);

	m_prefabs.emplace_back(CactusPrefab(), 200);
}
