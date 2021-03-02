//
// Created by Viktor on 1.3.2021 г..
//

#include "include/plains_biome.h"
#include "../../prefabs/include/tree_prefab.h"

PlainsBiome::PlainsBiome() {
	m_minHeight = 61;
	m_heightVariety = 6;
	m_cubes.emplace_back(Dirt);
	m_cubes.emplace_back(Grass);

	m_models.emplace_back(Bush, 10);

	m_prefabs.emplace_back(TreePrefab(), 600);
}
