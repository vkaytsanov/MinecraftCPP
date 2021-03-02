//
// Created by Viktor on 1.3.2021 г..
//

#include "include/mountains_biome.h"
#include "../../prefabs/include/tree_prefab.h"

MountainsBiome::MountainsBiome() {
	m_minHeight = 60;
	m_heightVariety = 30;

	m_cubes.emplace_back(Stone);
	m_cubes.emplace_back(Dirt);
	m_cubes.emplace_back(Grass);

	m_models.emplace_back(Bush, 200);
	m_models.emplace_back(FlowerYellow, 300);

	m_prefabs.emplace_back(TreePrefab(), 800);
}
