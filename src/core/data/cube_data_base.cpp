//
// Created by Viktor on 17.2.2021 г..
//

#include "include/cube_data_base.h"

namespace CubeDatabase {

	CubeDatabase::TextureCubeData::TextureCubeData(TextureRegion region, int sides) {
		uvs = region.getUVs();
		if (sides == 3) {
			for (int i = 0; i < 6 * 4 * 2; i++) {
				uvs[i] *= uvs3side[i];
			}
		}
	}

	std::vector<TextureCubeData> mappedTextures(Air + 1);

	void init(Texture* texture) {
		const int SPRITE_SIZE = 32;

		TextureRegion spriteSheet(texture);
		TextureRegion** regions = spriteSheet.split(SPRITE_SIZE, SPRITE_SIZE);

		mappedTextures[Gravel] = TextureCubeData(regions[0][0]);
		mappedTextures[Grass] = TextureCubeData(regions[1][0] + regions[2][0] + regions[3][0], 3);
		mappedTextures[Dirt] = TextureCubeData(regions[3][0]);
		mappedTextures[WoodPlank] = TextureCubeData(regions[4][0]);
		mappedTextures[StoneProcessed] = TextureCubeData(regions[5][0] + regions[6][0]);
		mappedTextures[Brick] = TextureCubeData(regions[7][0]);
		mappedTextures[TNT] = TextureCubeData(regions[8][0] + regions[9][0] + regions[10][0], 3);
		mappedTextures[Web] = TextureCubeData(regions[11][0]);
		mappedTextures[FlowerBlue] = TextureCubeData(regions[12][0]);
		mappedTextures[FlowerYellow] = TextureCubeData(regions[13][0]);
		mappedTextures[Treelet] = TextureCubeData(regions[15][0]);
		mappedTextures[BrokenStone] = TextureCubeData(regions[0][1]);
		mappedTextures[Bedrock] = TextureCubeData(regions[1][1]);
		mappedTextures[Sand] = TextureCubeData(regions[2][1]);
		mappedTextures[NetherGravel] = TextureCubeData(regions[4][1]);
		mappedTextures[Wood] = TextureCubeData(regions[5][1] + regions[6][1]);
		mappedTextures[IronProcessed] = TextureCubeData(regions[7][1]);
		mappedTextures[GoldProcessed] = TextureCubeData(regions[8][1]);
		mappedTextures[DiamondProcessed] = TextureCubeData(regions[9][1]);
		mappedTextures[ChestSingle] = TextureCubeData(regions[10][1] + regions[11][1] + regions[12][1], 3);
		mappedTextures[Gold] = TextureCubeData(regions[0][2]);
		mappedTextures[Iron] = TextureCubeData(regions[1][2]);
		mappedTextures[Coal] = TextureCubeData(regions[2][2]);
		mappedTextures[Glass] = TextureCubeData(regions[1][3]);
		mappedTextures[Diamond] = TextureCubeData(regions[2][3]);
		mappedTextures[Stone] = TextureCubeData(regions[12][12]);
		mappedTextures[Water] = TextureCubeData(regions[13][12]);
		mappedTextures[Lava] = TextureCubeData(regions[13][14]);
		mappedTextures[Air] = TextureCubeData();

		const int regionsSize = spriteSheet.getTexture()->getWidth() / SPRITE_SIZE;
		for (int i = 0; i < regionsSize; i++) {
			delete[] regions[i];
		}
		delete[] regions;
	}

	float* getUVs(CubeType type) {
		return mappedTextures[type].uvs;
	}

	void freeMemory() {
		for (auto& textureData : mappedTextures) {
			delete[] textureData.uvs;
		}
	}
}