//
// Created by Viktor on 1.3.2021 г..
//

#include "include/forest_biome.h"
#include "../../prefabs/include/tree_prefab.h"

ForestBiome::ForestBiome() {
	m_minHeight = 62;
	m_heightVariety = 6;

	m_cubes.emplace_back(Dirt);
	m_cubes.emplace_back(Grass);

	m_prefabs.emplace_back(TreePrefab(), 10);
}
