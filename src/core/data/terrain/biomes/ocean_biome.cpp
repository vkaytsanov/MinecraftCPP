//
// Created by Viktor on 1.3.2021 г..
//

#include "include/ocean_biome.h"

OceanBiome::OceanBiome() {
	m_minHeight = 20;
	m_heightVariety = 0;

	m_cubes.emplace_back(Sand);
	m_cubes.emplace_back(Water);
}
