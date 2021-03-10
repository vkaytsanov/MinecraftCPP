//
// Created by Viktor on 18.12.2020 г..
//

#include <stdexcept>
#include <iostream>
#include "include/asset_manager.h"
#include "terrain/include/cube_constants.h"


TextureCubeData::TextureCubeData(TextureRegion& region, int sides) {
	uvs = region.getUVs();
	if (sides == 3) {
		for (int i = 0; i < 6 * 4 * 2; i++) {
			uvs[i] *= CubeDatabase::uvs3side[i];
		}
	}
	else if (sides == 2) {
		for (int i = 0; i < 6 * 4 * 2; i++) {
			uvs[i] *= CubeDatabase::uvs2side[i];
		}
	}
}

AssetManager::AssetManager() {
	std::cout << "Creating assetmanager\n";
	const std::string spritePaths[] = {
			"spriteSheet.png",
	};

	int c = 0;
	for (const std::string& path : spritePaths) {
		m_mappedSprites[stripName(path)] = new Texture(ASSETS_LOCATION + path);
		c++;
	}

	std::cout << c << " sprites loaded\n";

	mapCubeTextures();
}

const Texture* AssetManager::getSprite(const std::string name) const {
	if (m_mappedSprites.find(name) == m_mappedSprites.end()) {
		std::cout << "Sprite " + name + " doesn't exists";
	}
	return m_mappedSprites.at(name);
}

AssetManager::~AssetManager() {
	for (const auto& textureData : m_mappedCubeTextures) {
		delete[] textureData.uvs;
	}

	for (const auto& it : m_mappedSprites) {
		delete it.second;
	}
}

std::string AssetManager::stripName(const std::string& name) {
	return name.substr(0, name.length() - 4);
}

AssetManager& AssetManager::getInstance() {
	//std::cout << "Creating instance\n";
	static AssetManager instance;
	return instance;
}

void AssetManager::mapCubeTextures() {
	const int spriteSize = 32;

	TextureRegion spriteSheet(getSprite("spriteSheet"));
	TextureRegion** regions = spriteSheet.split(spriteSize, spriteSize);

	m_mappedCubeTextures[Gravel] = TextureCubeData(regions[0][0]);
	m_mappedCubeTextures[Grass] = TextureCubeData(regions[1][0] + regions[2][0] + regions[3][0], 3);
	m_mappedCubeTextures[Dirt] = TextureCubeData(regions[3][0]);
	m_mappedCubeTextures[WoodPlank] = TextureCubeData(regions[4][0]);
	m_mappedCubeTextures[StoneProcessed] = TextureCubeData(regions[5][0] + regions[6][0]);
	m_mappedCubeTextures[Brick] = TextureCubeData(regions[7][0]);
	m_mappedCubeTextures[TNT] = TextureCubeData(regions[8][0] + regions[9][0] + regions[10][0], 3);
	m_mappedCubeTextures[Web] = TextureCubeData(regions[11][0]);
	m_mappedCubeTextures[FlowerBlue] = TextureCubeData(regions[12][0]);
	m_mappedCubeTextures[FlowerYellow] = TextureCubeData(regions[13][0]);
	m_mappedCubeTextures[Treelet] = TextureCubeData(regions[15][0]);

	m_mappedCubeTextures[BrokenStone] = TextureCubeData(regions[0][1]);
	m_mappedCubeTextures[Bedrock] = TextureCubeData(regions[1][1]);
	m_mappedCubeTextures[Sand] = TextureCubeData(regions[2][1]);
	m_mappedCubeTextures[NetherGravel] = TextureCubeData(regions[3][1]);
	m_mappedCubeTextures[Wood] = TextureCubeData(regions[4][1] + regions[5][1], 2);
	m_mappedCubeTextures[IronProcessed] = TextureCubeData(regions[6][1]);
	m_mappedCubeTextures[GoldProcessed] = TextureCubeData(regions[7][1]);
	m_mappedCubeTextures[DiamondProcessed] = TextureCubeData(regions[8][1]);
	m_mappedCubeTextures[ChestSingle] = TextureCubeData(regions[9][1] + regions[10][1] + regions[11][1], 3);

	m_mappedCubeTextures[Gold] = TextureCubeData(regions[0][2]);
	m_mappedCubeTextures[Iron] = TextureCubeData(regions[1][2]);
	m_mappedCubeTextures[Coal] = TextureCubeData(regions[2][2]);

	m_mappedCubeTextures[Glass] = TextureCubeData(regions[1][3]);
	m_mappedCubeTextures[Diamond] = TextureCubeData(regions[2][3]);
	m_mappedCubeTextures[Redstone] = TextureCubeData(regions[3][3]);
	m_mappedCubeTextures[Leaves] = TextureCubeData(regions[4][3]);

	m_mappedCubeTextures[Cactus] = TextureCubeData(regions[5][4] + regions[6][4], 2);
	m_mappedCubeTextures[SugarCane] = TextureCubeData(regions[9][4]);
	m_mappedCubeTextures[Bush] = TextureCubeData(regions[9][9]);


	m_mappedCubeTextures[Stone] = TextureCubeData(regions[12][12]);
	m_mappedCubeTextures[Water] = TextureCubeData(regions[13][12]);

	m_mappedCubeTextures[Sandstone] = TextureCubeData(regions[5][14] + regions[6][14], 2);
	m_mappedCubeTextures[Lava] = TextureCubeData(regions[13][14]);
	m_mappedCubeTextures[Air] = TextureCubeData();

	const int regionsSize = spriteSheet.getTexture()->getWidth() / spriteSize;
	for (int i = 0; i < regionsSize; i++) {
		delete[] regions[i];
	}
	delete[] regions;
}

const float* AssetManager::getCubeUVs(CubeType type) const {
	return m_mappedCubeTextures[type].uvs;
}

